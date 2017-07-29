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
const int g_nCmdCount_Normal = 2;
//--------------------------------------------------------------------
NwSPKLogic::NwSPKLogic()
{
    ResetSPKLogic();
}
//--------------------------------------------------------------------
NwSPKLogic::~NwSPKLogic()
{

}
//--------------------------------------------------------------------
const SPKHeroData* NwSPKLogic::GetMyHeroData()
{
    return &m_kMyHeroData;
}
//--------------------------------------------------------------------
const SPKHeroData* NwSPKLogic::GetAIHeroData()
{
    return &m_kAIHeroData;
}
//--------------------------------------------------------------------
void NwSPKLogic::ResetSPKLogic()
{
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        m_kMyCmdList[i] = NwSPKCmd_Max;
        m_kAICmdList[i] = NwSPKCmd_Max;
    }
    //
    m_kMyHeroData.nWuLi = 70;
    m_kMyHeroData.nMaxHP = 1000;
    m_kMyHeroData.nCurHP = 1000;
    m_kMyHeroData.nMaxEnergy = 100;
    m_kMyHeroData.nCurEnergy = 0;
    //
    m_kAIHeroData.nWuLi = 80;
    m_kAIHeroData.nMaxHP = 1000;
    m_kAIHeroData.nCurHP = 1000;
    m_kAIHeroData.nMaxEnergy = 100;
    m_kAIHeroData.nCurEnergy = 0;
    //
    m_nRoundCount = 0;
    m_nCurrentTouchIndex = 0;
    m_nTouchDrawCount = 0;
}
//--------------------------------------------------------------------
void NwSPKLogic::PrepareForRound_MyHero()
{
    m_kMyHeroData.nCmdUp = g_nCmdCount_Normal;
    m_kMyHeroData.nCmdMiddle = g_nCmdCount_Normal;
    m_kMyHeroData.nCmdDown = g_nCmdCount_Normal;
    m_kMyHeroData.nCmdDefend = g_nCmdCount_Normal;
}
//--------------------------------------------------------------------
void NwSPKLogic::PrepareForRound_AIHero()
{
    m_kAIHeroData.nCmdUp = g_nCmdCount_Normal;
    m_kAIHeroData.nCmdMiddle = g_nCmdCount_Normal;
    m_kAIHeroData.nCmdDown = g_nCmdCount_Normal;
    m_kAIHeroData.nCmdDefend = g_nCmdCount_Normal;
}
//--------------------------------------------------------------------
void NwSPKLogic::SetPlayerOption(NwSPKCmdType nCmd_Touch0, NwSPKCmdType nCmd_Touch1, NwSPKCmdType nCmd_Touch2)
{
    m_kMyCmdList[0] = nCmd_Touch0;
    m_kMyCmdList[1] = nCmd_Touch1;
    m_kMyCmdList[2] = nCmd_Touch2;
    //减少指令的数量
    if (nCmd_Touch0 == NwSPKCmd_XuanFeng)
    {
        //消耗旋风斩
        m_kMyHeroData.IncreaseCmdCount(nCmd_Touch0, -1);
        //尝试消耗斗志
        if (m_kMyHeroData.nCurEnergy >= m_kMyHeroData.nMaxEnergy)
        {
            m_kMyHeroData.nCurEnergy = 0;
        }
    }
    else
    {
        m_kMyHeroData.IncreaseCmdCount(nCmd_Touch0, -1);
        m_kMyHeroData.IncreaseCmdCount(nCmd_Touch1, -1);
        m_kMyHeroData.IncreaseCmdCount(nCmd_Touch2, -1);
    }
}
//--------------------------------------------------------------------
void NwSPKLogic::GenerateCmdForAI()
{
    m_vecAIWaitingCmd.clear();
    PrepareAIWaitingCmd();
    srand(time(0));
    int nVecIndex = 0;
    bool bCmdReady_0 = false;
    bool bCmdReady_1 = false;
    bool bCmdReady_2 = false;

    if (bCmdReady_0 == false)
    {
        //选出第一个指令
        //如果我是眩晕状态，选择什么指令都是浪费的，不如选择招架指令
        if (bCmdReady_0 == false)
        {
            if (m_kAIHeroData.bDizzy == true)
            {
                m_kAICmdList[0] = NwSPKCmd_ZhaoJia;
                bCmdReady_0 = true;
            }
        }

        //如果敌人是眩晕状态，则选出攻击类指令
        if (bCmdReady_0 == false)
        {
            if (m_kMyHeroData.bDizzy == true)
            {
                PrepareAIWaitingCmd_Attack();
                const int nAttackCount = (int)m_vecAIWaitingCmd_Attack.size();
                if (nAttackCount > 0)
                {
                    nVecIndex = rand() % nAttackCount;
                    m_kAICmdList[0] = m_vecAIWaitingCmd_Attack[nVecIndex];
                    bCmdReady_0 = true;
                }
            }
        }

        if (bCmdReady_0 == false)
        {
            nVecIndex = rand() % m_vecAIWaitingCmd.size();
            m_kAICmdList[0] = m_vecAIWaitingCmd[nVecIndex];
            bCmdReady_0 = true;
        }

        //如果第一个指令是旋风斩或者反杀，则需要特殊处理
        if (m_kAICmdList[0] == NwSPKCmd_XuanFeng || m_kAICmdList[0] == NwSPKCmd_FanSha)
        {
            m_kAICmdList[1] = m_kAICmdList[0];
            m_kAICmdList[2] = m_kAICmdList[0];
            //生成指令完毕
            bCmdReady_1 = true;
            bCmdReady_2 = true;
        }
    }


    if (bCmdReady_1 == false)
    {
        //从待选指令中删除第一个指令
        RemoveFromAIWaitingCmd(m_kAICmdList[0]);
        //选出第二个指令
        //如果前面的指令是闪避，则本指令是攻击类指令
        if (m_kAICmdList[0] == NwSPKCmd_ShanBi)
        {
            PrepareAIWaitingCmd_Attack();
            const int nAttackCount = (int)m_vecAIWaitingCmd_Attack.size();
            if (nAttackCount > 0)
            {
                nVecIndex = rand() % nAttackCount;
                m_kAICmdList[1] = m_vecAIWaitingCmd_Attack[nVecIndex];
                bCmdReady_1 = true;
            }
        }
        if (bCmdReady_1 == false)
        {
            nVecIndex = rand() % m_vecAIWaitingCmd.size();
            m_kAICmdList[1] = m_vecAIWaitingCmd[nVecIndex];
            bCmdReady_1 = true;
        }
    }

    
    if (bCmdReady_2 == false)
    {
        //从待选指令中删除第二个指令
        RemoveFromAIWaitingCmd(m_kAICmdList[1]);
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
        if (bCmdReady_2 == false)
        {
            if (m_kAICmdList[1] == NwSPKCmd_ShanBi)
            {
                PrepareAIWaitingCmd_Attack();
                const int nAttackCount = (int)m_vecAIWaitingCmd_Attack.size();
                if (nAttackCount > 0)
                {
                    nVecIndex = rand() % nAttackCount;
                    m_kAICmdList[2] = m_vecAIWaitingCmd_Attack[nVecIndex];
                    bCmdReady_2 = true;
                }
            }
        }

        if (bCmdReady_2 == false)
        {
            nVecIndex = rand() % m_vecAIWaitingCmd.size();
            m_kAICmdList[2] = m_vecAIWaitingCmd[nVecIndex];
            bCmdReady_2 = true;
        }
    }
    
    //减少指令的数量
    if (m_kAICmdList[0] == NwSPKCmd_XuanFeng)
    {
        //消耗旋风斩
        m_kAIHeroData.IncreaseCmdCount(m_kAICmdList[0], -1);
        //尝试消耗斗志
        if (m_kAIHeroData.nCurEnergy >= m_kAIHeroData.nMaxEnergy)
        {
            //消耗斗志
            m_kAIHeroData.nCurEnergy = 0;
        }
    }
    else
    {
        m_kAIHeroData.IncreaseCmdCount(m_kAICmdList[0], -1);
        m_kAIHeroData.IncreaseCmdCount(m_kAICmdList[1], -1);
        m_kAIHeroData.IncreaseCmdCount(m_kAICmdList[2], -1);
    }
}
//--------------------------------------------------------------------
void NwSPKLogic::IncreaseRoundCount()
{
    //新的回合开始了
    ++m_nRoundCount;
    m_nCurrentTouchIndex = 0;
}
//--------------------------------------------------------------------
int NwSPKLogic::GetCurrentTouchIndex()
{
    return m_nCurrentTouchIndex;
}
//--------------------------------------------------------------------
void NwSPKLogic::GenerateCurrentTouchResult()
{
    m_nMyCmd = m_kMyCmdList[m_nCurrentTouchIndex];
    m_nAICmd = m_kAICmdList[m_nCurrentTouchIndex];
    //判断两个指令的大小
    JudgeCmd(m_nMyCmd, m_nAICmd);
    //计算攻击伤害
    CalculateDamage();
}
//--------------------------------------------------------------------
void NwSPKLogic::ApplyTouchResult()
{
    //上一次是眩晕状态的，这一次要解除眩晕
    bool bOldMyDizzy = m_kMyHeroData.bDizzy;
    bool bOldAIDizzy = m_kAIHeroData.bDizzy;
    m_kMyHeroData.bDizzy = false;
    m_kAIHeroData.bDizzy = false;

    if (m_NwSPKTouchResult == NwSPKTouchResult_Win)
    {
        if (m_nMyCmd == NwSPKCmd_ShanBi)
        {
            //对敌人施加一次眩晕
            if (bOldAIDizzy)
            {
                //上一次敌人已经是眩晕的，我的闪避没发挥作用，不再施加眩晕
            }
            else
            {
                m_kAIHeroData.bDizzy = true;
            }
        }

        //血量减少
        m_kAIHeroData.nCurHP -= m_nAttackDamage;
        if (m_kAIHeroData.nCurHP < 0)
        {
            m_kAIHeroData.nCurHP = 0;
        }

        //增加斗志
        if (m_kMyHeroData.nCurEnergy < m_kMyHeroData.nMaxEnergy)
        {
            m_kMyHeroData.nCurEnergy += 20;
            if (m_kMyHeroData.nCurEnergy >= m_kMyHeroData.nMaxEnergy)
            {
                //增加一个旋风斩
                m_kMyHeroData.nCurEnergy = m_kMyHeroData.nMaxEnergy;
                ++(m_kMyHeroData.nCmdSwoosh);
            }
        }
    }
    else if (m_NwSPKTouchResult == NwSPKTouchResult_Lose)
    {
        if (m_nAICmd == NwSPKCmd_ShanBi)
        {
            //对敌人施加一次眩晕
            if (bOldMyDizzy)
            {
                //上一次敌人已经是眩晕的，我的闪避没发挥作用，不再施加眩晕
            }
            else
            {
                m_kMyHeroData.bDizzy = true;
            }
        }

        //血量减少
        m_kMyHeroData.nCurHP -= m_nAttackDamage;
        if (m_kMyHeroData.nCurHP < 0)
        {
            m_kMyHeroData.nCurHP = 0;
        }

        //增加斗志
        if (m_kAIHeroData.nCurEnergy < m_kAIHeroData.nMaxEnergy)
        {
            m_kAIHeroData.nCurEnergy += 20;
            if (m_kAIHeroData.nCurEnergy >= m_kAIHeroData.nMaxEnergy)
            {
                m_kAIHeroData.nCurEnergy = m_kAIHeroData.nMaxEnergy;
                ++(m_kAIHeroData.nCmdSwoosh);
            }
        }
    }
    else if (m_NwSPKTouchResult == NwSPKTouchResult_Draw)
    {
        ++m_nTouchDrawCount;
        if (m_nTouchDrawCount >= 3)
        {
            m_nTouchDrawCount = 0;
            //双方都增加一个“闪避”指令
            ++(m_kMyHeroData.nCmdDodge);
            ++(m_kAIHeroData.nCmdDodge);
        }
        //增加斗志
        if (m_kMyHeroData.nCurEnergy < m_kMyHeroData.nMaxEnergy)
        {
            m_kMyHeroData.nCurEnergy += 10;
            if (m_kMyHeroData.nCurEnergy >= m_kMyHeroData.nMaxEnergy)
            {
                //增加一个旋风斩
                m_kMyHeroData.nCurEnergy = m_kMyHeroData.nMaxEnergy;
                ++(m_kMyHeroData.nCmdSwoosh);
            }
        }
        if (m_kAIHeroData.nCurEnergy < m_kAIHeroData.nMaxEnergy)
        {
            m_kAIHeroData.nCurEnergy += 10;
            if (m_kAIHeroData.nCurEnergy >= m_kAIHeroData.nMaxEnergy)
            {
                m_kAIHeroData.nCurEnergy = m_kAIHeroData.nMaxEnergy;
                ++(m_kAIHeroData.nCmdSwoosh);
            }
        }
    }
}
//--------------------------------------------------------------------
NwSPKTouchResult NwSPKLogic::GetTouchResult()
{
    return m_NwSPKTouchResult;
}
//--------------------------------------------------------------------
NwSPKCmdType NwSPKLogic::GetAITouchCmd(int theTouchIndex)
{
    if (theTouchIndex >= NwSPKTouch_0 && theTouchIndex < NwSPKTouch_Max)
    {
        return m_kAICmdList[theTouchIndex];
    }
    else
    {
        return NwSPKCmd_Max;
    }
}
//--------------------------------------------------------------------
int NwSPKLogic::GetTouchAttackDamage()
{
    return m_nAttackDamage;
}
//--------------------------------------------------------------------
void NwSPKLogic::TouchFinished()
{
    //增加交锋的序号
    ++m_nCurrentTouchIndex;
}
//--------------------------------------------------------------------
bool NwSPKLogic::IsRoundFinish()
{
    if (m_nCurrentTouchIndex >= NwSPKTouch_Max)
    {
        return true;
    }
    //如果是旋风斩，则一次交锋就结束
    if (m_nMyCmd == NwSPKCmd_XuanFeng || m_nAICmd == NwSPKCmd_XuanFeng)
    {
        return true;
    }
    return IsFightFinish();
}
//--------------------------------------------------------------------
bool NwSPKLogic::IsFightFinish()
{
    //如果有人死亡，则战斗结束
    if (m_kMyHeroData.nCurHP <= 0)
    {
        return true;
    }
    if (m_kAIHeroData.nCurHP <= 0)
    {
        return true;
    }
    return false;
}
//--------------------------------------------------------------------
bool NwSPKLogic::IsMainPlayerWin()
{
    if (m_kMyHeroData.nCurHP > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//--------------------------------------------------------------------
void NwSPKLogic::JudgeCmd(int CmdA, int CmdB)
{
    //定义眩晕状态的枚举值
    static const int CmdBtn_Dizzy = NwSPKCmd_Max + 1;

    if (m_kMyHeroData.bDizzy)
    {
        CmdA = CmdBtn_Dizzy;
    }
    if (m_kAIHeroData.bDizzy)
    {
        CmdB = CmdBtn_Dizzy;
    }
    //
    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
    //
    switch (CmdA)
    {
        case NwSPKCmd_Up:
        {
            switch (CmdB)
            {
                case NwSPKCmd_Up:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_Middle:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_Down:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_ZhaoJia:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_ShanBi:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case CmdBtn_Dizzy:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_XuanFeng:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
            }
            break;
        }
        case NwSPKCmd_Middle:
        {
            switch (CmdB)
            {
                case NwSPKCmd_Up:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_Middle:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_Down:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_ZhaoJia:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_ShanBi:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case CmdBtn_Dizzy:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_XuanFeng:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
            }
            break;
        }
        case NwSPKCmd_Down:
        {
            switch (CmdB)
            {
                case NwSPKCmd_Up:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_Middle:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_Down:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_ZhaoJia:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_ShanBi:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case CmdBtn_Dizzy:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_XuanFeng:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
            }
            break;
        }
        case NwSPKCmd_ZhaoJia:
        {
            switch (CmdB)
            {
                case NwSPKCmd_Up:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_Middle:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_Down:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_ZhaoJia:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_ShanBi:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case CmdBtn_Dizzy:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_XuanFeng:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
            }
            break;
        }
        case NwSPKCmd_ShanBi:
        {
            switch (CmdB)
            {
                case NwSPKCmd_Up:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_Middle:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_Down:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_ZhaoJia:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_ShanBi:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case CmdBtn_Dizzy:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_XuanFeng:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
            }
            break;
        }
        case CmdBtn_Dizzy:
        {
            switch (CmdB)
            {
                case NwSPKCmd_Up:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_Middle:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_Down:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case NwSPKCmd_ZhaoJia:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_ShanBi:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case CmdBtn_Dizzy:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
                case NwSPKCmd_XuanFeng:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
            }
            break;
        }
        case NwSPKCmd_XuanFeng:
        {
            switch (CmdB)
            {
                case NwSPKCmd_Up:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_Middle:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_Down:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_ZhaoJia:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_ShanBi:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Lose;
                    break;
                }
                case CmdBtn_Dizzy:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Win;
                    break;
                }
                case NwSPKCmd_XuanFeng:
                {
                    m_NwSPKTouchResult = NwSPKTouchResult_Draw;
                    break;
                }
            }
            break;
        }
    }
}
//--------------------------------------------------------------------
void NwSPKLogic::CalculateDamage()
{
    m_nAttackDamage = 0;
    
    const int result = m_NwSPKTouchResult;
    switch (result)
    {
        case NwSPKTouchResult_Draw:
        {
            m_nAttackDamage = 0;
            break;
        }
        case NwSPKTouchResult_Win:
        {
            if (m_nMyCmd == NwSPKCmd_ShanBi)
            {
                //我成功使用了闪避，不对敌人施加伤害，使敌人眩晕一个交锋
                m_nAttackDamage = 0;
            }
            else if (m_nMyCmd == NwSPKCmd_XuanFeng)
            {
                //我成功施放了旋风斩
                m_nAttackDamage = GetMyAttackDamage() * 3;
            }
            else
            {
                m_nAttackDamage = GetMyAttackDamage();
            }
            //
            if (m_kAIHeroData.bDizzy == false) //对方没有被眩晕
            {
                if (m_nAICmd == NwSPKCmd_ZhaoJia)
                {
                    //对方使用了招架，伤害减少
                    m_nAttackDamage = (int)((float)m_nAttackDamage * 0.3f);
                }
            }
            break;
        }
        case NwSPKTouchResult_Lose:
        {
            if (m_nAICmd == NwSPKCmd_ShanBi)
            {
                //敌人成功使用了闪避，不对我施加伤害，我眩晕一个交锋
                m_nAttackDamage = 0;
            }
            else if (m_nAICmd == NwSPKCmd_XuanFeng)
            {
                //AI成功施放了旋风斩
                m_nAttackDamage = GetAIAttackDamage() * 3;
            }
            else
            {
                m_nAttackDamage = GetAIAttackDamage();
            }
            //
            if (m_kMyHeroData.bDizzy == false) //对方没有被眩晕
            {
                if (m_nMyCmd == NwSPKCmd_ZhaoJia)
                {
                    //对方使用了招架，伤害减少
                    m_nAttackDamage = (int)((float)m_nAttackDamage * 0.3f);
                }
            }
            break;
        }
    }
}
//--------------------------------------------------------------------
int NwSPKLogic::GetMyAttackDamage()
{
    //攻击伤害就是武力值
    return m_kMyHeroData.nWuLi;
}
//--------------------------------------------------------------------
int NwSPKLogic::GetAIAttackDamage()
{
    //攻击伤害就是武力值
    return m_kAIHeroData.nWuLi;
}
//--------------------------------------------------------------------
void NwSPKLogic::PrepareAIWaitingCmd()
{
    for (int i = 0; i < m_kAIHeroData.nCmdUp; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_Up);
    }
    for (int i = 0; i < m_kAIHeroData.nCmdMiddle; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_Middle);
    }
    for (int i = 0; i < m_kAIHeroData.nCmdDown; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_Down);
    }
    for (int i = 0; i < m_kAIHeroData.nCmdDefend; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_ZhaoJia);
    }
    for (int i = 0; i < m_kAIHeroData.nCmdDodge; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_ShanBi);
    }
    for (int i = 0; i < m_kAIHeroData.nCmdInsight; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_DongCha);
    }
    for (int i = 0; i < m_kAIHeroData.nCmdSwoosh; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_XuanFeng);
    }
    for (int i = 0; i < m_kAIHeroData.nCmdRevenge; ++i)
    {
        m_vecAIWaitingCmd.push_back(NwSPKCmd_FanSha);
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



























