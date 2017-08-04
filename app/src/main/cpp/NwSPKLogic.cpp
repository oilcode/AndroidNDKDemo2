//--------------------------------------------------------------------
//AI能够做到的事情：
//1，从自己拥有的指令中选出本次回合的三个指令。
//2，选出的指令合乎规则，例如旋风斩不能作为第二个交锋指令，也不能作为第三个交锋指令。
//3，一个回合中最多选出一个闪避。如果AI连续施放两个闪避，会很傻。
//4，闪避的后面一个指令，需要是能够造成伤害的攻击类指令。闪避成功后敌方会眩晕，趁机给敌方狠狠一击。
//5，如果敌方是眩晕状态，则AI的第一个指令是攻击类指令。
//--------------------------------------------------------------------
#include "NwSPKLogic.h"
//--------------------------------------------------------------------
NwSPKLogic::NwSPKLogic()
{

}
//--------------------------------------------------------------------
NwSPKLogic::~NwSPKLogic()
{

}
//--------------------------------------------------------------------
void NwSPKLogic::GenerateCmdForAI(const NwSPKHeroData* pAIHeroData, const NwSPKHeroData* pOtherHeroData, NwSPKSelectedCmd* pSelectedCmd)
{
    PrepareAIWaitingCmd(pAIHeroData);

    srand(time(0));
    NwSPKCmdType cmd0 = NwSPKCmd_Invalid;
    NwSPKCmdType cmd1 = NwSPKCmd_Invalid;
    NwSPKCmdType cmd2 = NwSPKCmd_Invalid;

    if (cmd0 == NwSPKCmd_Invalid)
    {
        //选出第一个指令
        //如果我是眩晕状态，选择什么指令都是浪费的，不如选择招架指令
        if (cmd0 == NwSPKCmd_Invalid)
        {
            if (pAIHeroData->kBuffList[NwSPKBuff_XuanYun].IsEnable())
            {
                cmd0 = NwSPKCmd_ZhaoJia;
            }
        }

        //如果敌人是眩晕状态，则选出攻击类指令
        if (cmd0 == NwSPKCmd_Invalid)
        {
            if (pOtherHeroData->kBuffList[NwSPKBuff_XuanYun].IsEnable())
            {
                PrepareAIWaitingCmd_Attack();
                cmd0 = PickOneFromWaitingCmd_Attack();
            }
        }

        if (cmd0 == NwSPKCmd_Invalid)
        {
            cmd0 = PickOneFromWaitingCmd();
        }

        //如果第一个指令是旋风斩或者反杀，则需要特殊处理
        if (cmd0 == NwSPKCmd_XuanFeng || cmd0 == NwSPKCmd_FanSha)
        {
            cmd1 = cmd0;
            cmd2 = cmd0;
        }
    }


    if (cmd1 == NwSPKCmd_Invalid)
    {
        //从待选指令中删除第一个指令
        RemoveFromAIWaitingCmd(cmd0);
        //选出第二个指令

        if (cmd1 == NwSPKCmd_Invalid)
        {
            //如果前面的指令是闪避，则本指令是攻击类指令
            if (cmd0 == NwSPKCmd_ShanBi)
            {
                PrepareAIWaitingCmd_Attack();
                cmd1 = PickOneFromWaitingCmd_Attack();
            }
        }

        if (cmd1 == NwSPKCmd_Invalid)
        {
            cmd1 = PickOneFromWaitingCmd();
        }
    }

    
    if (cmd2 == NwSPKCmd_Invalid)
    {
        //从待选指令中删除第二个指令
        RemoveFromAIWaitingCmd(cmd1);
        //选出第三个指令
        /*
        //如果有闪避，优先使用闪避
        if (bCmdReady_2 == false)
        {
            if (m_kAIHeroData.nCmdDodge + m_kAIHeroData.nDodgeCountInBag > 0)
            {
                m_kAICmdList[2] = NwSPKCmd_ShanBi;
                bCmdReady_2 = true;
            }
        }
         */

        //如果前面的指令是闪避，则本指令是攻击类指令
        if (cmd2 == NwSPKCmd_Invalid)
        {
            if (cmd1 == NwSPKCmd_ShanBi)
            {
                PrepareAIWaitingCmd_Attack();
                cmd2 = PickOneFromWaitingCmd_Attack();
            }
        }

        if (cmd2 == NwSPKCmd_Invalid)
        {
            cmd2 = PickOneFromWaitingCmd();
        }
    }

    pSelectedCmd->kCmdList[0] = cmd0;
    pSelectedCmd->kCmdList[1] = cmd1;
    pSelectedCmd->kCmdList[2] = cmd2;
}
//--------------------------------------------------------------------
void NwSPKLogic::PrepareAIWaitingCmd(const NwSPKHeroData* pHeroData)
{
    m_vecAIWaitingCmd.clear();
    //
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        const int nSingleCmdCount = pHeroData->kCmdCountList[i];
        for (int j = 0; j < nSingleCmdCount; ++j)
        {
            m_vecAIWaitingCmd.push_back((NwSPKCmdType)i);
        }
    }
}
//--------------------------------------------------------------------
void NwSPKLogic::PrepareAIWaitingCmd_Attack()
{
    m_vecAIWaitingCmd_Attack.clear();
    //
    for (std::vector<NwSPKCmdType>::iterator it = m_vecAIWaitingCmd.begin();
         it != m_vecAIWaitingCmd.end();
         ++it)
    {
        NwSPKCmdType _cmd_ = *it;
        switch (_cmd_)
        {
            case NwSPKCmd_Up:
            case NwSPKCmd_Middle:
            case NwSPKCmd_Down:
            case NwSPKCmd_XuanFeng:
            case NwSPKCmd_FanSha:
            {
                m_vecAIWaitingCmd_Attack.push_back(_cmd_);
                break;
            }
            default:
                break;
        }
    }
}
//--------------------------------------------------------------------
void NwSPKLogic::RemoveFromAIWaitingCmd(NwSPKCmdType theCmd)
{
    //除了移除指定的指令，还要移除旋风斩和反杀两个指令，
    //因为这两个指令不能在第二次交锋和第三次交锋中使用。
    //如果被移除的指令是闪避，则把所有的闪避都移除，也即一个回合中最多选出一个闪避；
    //如果AI连续施放两个闪避，会很傻。
    int nCount = (int)m_vecAIWaitingCmd.size();
    bool bFind = false;
    bool bAlreadyRemovedCmd = false;
    for (int i = 0; i < nCount; ++i)
    {
        bFind = false;
        for (std::vector<NwSPKCmdType>::iterator it = m_vecAIWaitingCmd.begin();
            it != m_vecAIWaitingCmd.end();
            ++it)
        {
            if (bAlreadyRemovedCmd == false && *it == theCmd)
            {
                m_vecAIWaitingCmd.erase(it);
                bFind = true;
                bAlreadyRemovedCmd = true;
                break;
            }
            else if (*it == NwSPKCmd_XuanFeng)
            {
                m_vecAIWaitingCmd.erase(it);
                bFind = true;
                break;
            }
            else if (*it == NwSPKCmd_FanSha)
            {
                m_vecAIWaitingCmd.erase(it);
                bFind = true;
                break;
            }
            else if (theCmd == NwSPKCmd_ShanBi && *it == NwSPKCmd_ShanBi)
            {
                m_vecAIWaitingCmd.erase(it);
                bFind = true;
                break;
            }
        }
        //
        if (bFind == false)
        {
            //没有需要移除的指令了
            break;
        }
    }
}
//--------------------------------------------------------------------
NwSPKCmdType NwSPKLogic::PickOneFromWaitingCmd()
{
    NwSPKCmdType theType = NwSPKCmd_ZhaoJia;
    const int nAttackCount = (int)m_vecAIWaitingCmd.size();
    if (nAttackCount > 0)
    {
        const int nVecIndex = rand() % nAttackCount;
        theType = m_vecAIWaitingCmd[nVecIndex];
    }
    return theType;
}
//--------------------------------------------------------------------
NwSPKCmdType NwSPKLogic::PickOneFromWaitingCmd_Attack()
{
    NwSPKCmdType theType = NwSPKCmd_ZhaoJia;
    const int nAttackCount = (int)m_vecAIWaitingCmd_Attack.size();
    if (nAttackCount > 0)
    {
        const int nVecIndex = rand() % nAttackCount;
        theType = m_vecAIWaitingCmd_Attack[nVecIndex];
    }
    return theType;
}
//--------------------------------------------------------------------
