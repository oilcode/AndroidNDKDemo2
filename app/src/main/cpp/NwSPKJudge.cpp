//--------------------------------------------------------------------------------------------------
#include "NwSPKJudge.h"
#include "SoCodeBaseInclude.h"
#include "SoMessageBox.h"
#include "SoStringHelp.h"
//--------------------------------------------------------------------------------------------------
NwSPKJudge::NwSPKJudge()
{
    for (int i = 0; i < NwSPKSide_Max; ++i)
    {
        m_pHeroDataList[i] = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
NwSPKJudge::~NwSPKJudge()
{

}
//--------------------------------------------------------------------------------------------------
const NwSPKResultRound* NwSPKJudge::StartJudgeRound(NwSPKHeroData* pLeftHeroData, const NwSPKSelectedCmd* pLeftCmd,
                                                    NwSPKHeroData* pRightHeroData, const NwSPKSelectedCmd* pRightCmd)
{
    m_kResult.ClearResultRound();

    if (pLeftHeroData == NULL || pLeftCmd == NULL || pRightHeroData == NULL || pRightCmd == NULL)
    {
        return &m_kResult;
    }

    m_pHeroDataList[NwSPKSide_Left] = pLeftHeroData;
    m_pHeroDataList[NwSPKSide_Right] = pRightHeroData;

    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        JudgeTouch(i, pLeftCmd->kCmdList[i], pRightCmd->kCmdList[i]);

        pLeftHeroData->ProcessSPKResult(&(m_kResult.kTouchList[i].kSideList[NwSPKSide_Left]));
        pRightHeroData->ProcessSPKResult(&(m_kResult.kTouchList[i].kSideList[NwSPKSide_Right]));

        if (CheckRoundFinished())
        {
            break;
        }
    }

    return &m_kResult;
}
//--------------------------------------------------------------------------------------------------
const NwSPKResultRound* NwSPKJudge::StartJudgeTouch(int nTouchIndex, NwSPKHeroData* pLeftHeroData, NwSPKHeroData* pRightHeroData, 
                                                    NwSPKCmdType theLeftCmd, NwSPKCmdType theRightCmd)
{
    m_kResult.ClearResultRound();

    if (pLeftHeroData == NULL || pRightHeroData == NULL)
    {
        return &m_kResult;
    }

    m_pHeroDataList[NwSPKSide_Left] = pLeftHeroData;
    m_pHeroDataList[NwSPKSide_Right] = pRightHeroData;

    JudgeTouch(nTouchIndex, theLeftCmd, theRightCmd);

    return &m_kResult;
}
//--------------------------------------------------------------------------------------------------
void NwSPKJudge::JudgeTouch(int nTouchIndex, NwSPKCmdType theLeftCmd, NwSPKCmdType theRightCmd)
{
    const NwSPKHeroData* pLeftHeroData = m_pHeroDataList[NwSPKSide_Left];
    const NwSPKHeroData* pRightHeroData = m_pHeroDataList[NwSPKSide_Right];
    NwSPKResultSingle& kLeftResultSingle = m_kResult.kTouchList[nTouchIndex].kSideList[NwSPKSide_Left];
    NwSPKResultSingle& kRightResultSingle = m_kResult.kTouchList[nTouchIndex].kSideList[NwSPKSide_Right];

    //只要施放旋风斩，必定消耗MP
    if (theLeftCmd == NwSPKCmd_XuanFeng)
    {
        kLeftResultSingle.nDeltaMP -= NwSPK_MPCountPerXuanFeng;
    }
    if (theRightCmd == NwSPKCmd_XuanFeng)
    {
        kRightResultSingle.nDeltaMP -= NwSPK_MPCountPerXuanFeng;
    }

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //首先处理buff对战斗结果的影响
    bool bLeftIsXuanYun = pLeftHeroData->IsBuffEnable(NwSPKBuff_XuanYun);
    bool bRightIsXuanYun = pRightHeroData->IsBuffEnable(NwSPKBuff_XuanYun);
    if (bLeftIsXuanYun && bRightIsXuanYun)
    {
        //都眩晕
        kLeftResultSingle.theResult = NwSPKTouchResult_Draw;
        kRightResultSingle.theResult = NwSPKTouchResult_Draw;
        return;
    }
    if (bLeftIsXuanYun)
    {
        //左方眩晕，左方被攻击
        kLeftResultSingle.theResult = NwSPKTouchResult_Lose;
        kRightResultSingle.theResult = NwSPKTouchResult_Win;
        AttackXuanYun(pRightHeroData, theRightCmd, &kRightResultSingle, &kLeftResultSingle);
        return;
    }
    if (bRightIsXuanYun)
    {
        //右方眩晕，右方被攻击
        kLeftResultSingle.theResult = NwSPKTouchResult_Win;
        kRightResultSingle.theResult = NwSPKTouchResult_Lose;
        AttackXuanYun(pLeftHeroData, theLeftCmd, &kLeftResultSingle, &kRightResultSingle);
        return;
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //处理平局
    if (theLeftCmd == theRightCmd)
    {
        //指令相同
        kLeftResultSingle.theResult = NwSPKTouchResult_Draw;
        kRightResultSingle.theResult = NwSPKTouchResult_Draw;
        SameCmd(&kLeftResultSingle, &kRightResultSingle, theLeftCmd);
        return;
    }

    NwSPKTouchResult theCompareResult = CmdCompare(theLeftCmd, theRightCmd);
    if (theCompareResult == NwSPKTouchResult_Draw)
    {
        kLeftResultSingle.theResult = NwSPKTouchResult_Draw;
        kRightResultSingle.theResult = NwSPKTouchResult_Draw;
        DrawCmd(&kLeftResultSingle, &kRightResultSingle, theLeftCmd, theRightCmd);
        return;
    }
    
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //必定有输有赢
    //判断谁输谁赢
    if (theCompareResult == NwSPKTouchResult_Win)
    {
        kLeftResultSingle.theResult = NwSPKTouchResult_Win;
        kRightResultSingle.theResult = NwSPKTouchResult_Lose;
        WinnerAttack(theLeftCmd, theRightCmd, pLeftHeroData, pRightHeroData, &kLeftResultSingle, &kRightResultSingle);
        return;
    }
    else
    {
        kLeftResultSingle.theResult = NwSPKTouchResult_Lose;
        kRightResultSingle.theResult = NwSPKTouchResult_Win;
        WinnerAttack(theRightCmd, theLeftCmd, pRightHeroData, pLeftHeroData, &kRightResultSingle, &kLeftResultSingle);
        return;
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
//--------------------------------------------------------------------------------------------------
void NwSPKJudge::AttackXuanYun(const NwSPKHeroData* pWinnerHero, NwSPKCmdType theCmd, NwSPKResultSingle* pWinnerResultSingle, NwSPKResultSingle* pOtherResultSingle)
{
    //攻击眩晕者，双方都不产生MP
    switch (theCmd)
    {
        case NwSPKCmd_Up:
        case NwSPKCmd_Middle:
        case NwSPKCmd_Down:
        case NwSPKCmd_FanSha:
        {
            pOtherResultSingle->nDeltaHP -= CalculateNormalDamage(pWinnerHero);
        }
        break;
        case NwSPKCmd_XuanFeng:
        {
            pOtherResultSingle->nDeltaHP -= CalculateXuanFengDamage(pWinnerHero);
        }
        break;
        case NwSPKCmd_ZhaoJia:
        case NwSPKCmd_ShanBi:
        {
            //do nothing
        }
        break;
        default:
        {
            const char* szDesc = SoStrFmt("NwSPKJudge::AttackXuanYun : Unknown CmdType[%d]", theCmd);
            SoMessageBox("", szDesc);
        }
        break;
    }
}
//--------------------------------------------------------------------------------------------------
void NwSPKJudge::SameCmd(NwSPKResultSingle* pLeftSingle, NwSPKResultSingle* pRightSingle, NwSPKCmdType theCmd)
{
    if (theCmd == NwSPKCmd_XuanFeng || theCmd == NwSPKCmd_FanSha)
    {
        //旋风斩，反杀不增加MP
    }
    else
    {
        pLeftSingle->nDeltaMP += CalculateMP();
        pRightSingle->nDeltaMP += CalculateMP();
    }
    pLeftSingle->nDeltaSamePoint += 1;
    pRightSingle->nDeltaSamePoint += 1;
}
//--------------------------------------------------------------------------------------------------
void NwSPKJudge::DrawCmd(NwSPKResultSingle* pLeftSingle, NwSPKResultSingle* pRightSingle, NwSPKCmdType theLeftCmd, NwSPKCmdType theRightCmd)
{
    //有两种情况会执行到这里：
    //1，一方是闪避，另一方是招架
    //2，一方是闪避，另一方是旋风斩
    if (theLeftCmd != NwSPKCmd_XuanFeng)
    {
        pLeftSingle->nDeltaMP += CalculateMP();
    }
    if (theRightCmd != NwSPKCmd_XuanFeng)
    {
        pRightSingle->nDeltaMP += CalculateMP();
    }
}
//--------------------------------------------------------------------------------------------------
void NwSPKJudge::WinnerAttack(NwSPKCmdType theWinnerCmd, NwSPKCmdType theOtherCmd, const NwSPKHeroData* pWinnerHero, const NwSPKHeroData* pOtherHero, NwSPKResultSingle* pWinnerSingle, NwSPKResultSingle* pOtherSingle)
{
    switch (theWinnerCmd)
    {
        case NwSPKCmd_ShanBi:
        {
            pOtherSingle->AddBuff(NwSPKBuff_XuanYun, NwSPK_XuanYunTouchCount);
            //闪避成功，只给成功者加MP
            pWinnerSingle->nDeltaMP += CalculateMP();
        }
        break;
        case NwSPKCmd_XuanFeng:
        {
            int nDamage = CalculateXuanFengDamage(pWinnerHero);
            if (theOtherCmd == NwSPKCmd_ZhaoJia)
            {
                nDamage = ReduceDamageByZhaoJia(pOtherHero, nDamage);
            }
            pOtherSingle->nDeltaHP -= nDamage;
            //旋风斩施放成功，双方都不增加MP
            //pWinnerSingle->nDeltaMP += CalculateMP();
            //pOtherSingle->nDeltaMP += CalculateMP();
        }
        break;
        case NwSPKCmd_FanSha:
        {
            int nDamage = CalculateNormalDamage(pWinnerHero);
            if (theOtherCmd == NwSPKCmd_ZhaoJia)
            {
                nDamage = ReduceDamageByZhaoJia(pOtherHero, nDamage);
            }
            pOtherSingle->nDeltaHP -= nDamage;
            //反杀施放成功，双方都不增加MP
            //pWinnerSingle->nDeltaMP += CalculateMP();
            //pOtherSingle->nDeltaMP += CalculateMP();
        }
        break;
        default:
        {
            int nDamage = CalculateNormalDamage(pWinnerHero);
            if (theOtherCmd == NwSPKCmd_ZhaoJia)
            {
                nDamage = ReduceDamageByZhaoJia(pOtherHero, nDamage);
            }
            pOtherSingle->nDeltaHP -= nDamage;
            //
            pWinnerSingle->nDeltaMP += CalculateMP();
            pOtherSingle->nDeltaMP += CalculateMP();
        }
        break;
    }
}
//--------------------------------------------------------------------------------------------------
int NwSPKJudge::CalculateNormalDamage(const NwSPKHeroData* pWinnerHero)
{
    return pWinnerHero->nWuLi;
}
//--------------------------------------------------------------------------------------------------
int NwSPKJudge::CalculateXuanFengDamage(const NwSPKHeroData* pWinnerHero)
{
    return pWinnerHero->nWuLi * 3;
}
//--------------------------------------------------------------------------------------------------
int NwSPKJudge::ReduceDamageByZhaoJia(const NwSPKHeroData* pLoserHero, int nDamage)
{
    return ((nDamage+2) / 3);
}
//--------------------------------------------------------------------------------------------------
int NwSPKJudge::CalculateMP()
{
    return 15;
}
//--------------------------------------------------------------------------------------------------
bool NwSPKJudge::CheckRoundFinished() const
{
    if (m_pHeroDataList[NwSPKSide_Left]->nCurHP <= 0)
    {
        return true;
    }
    if (m_pHeroDataList[NwSPKSide_Right]->nCurHP <= 0)
    {
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
NwSPKTouchResult NwSPKJudge::CmdCompare(NwSPKCmdType theCmd, NwSPKCmdType theOther)
{
    switch (theCmd)
    {
        case NwSPKCmd_Up:
        {
            switch (theOther)
            {
                case NwSPKCmd_Middle:
                case NwSPKCmd_ZhaoJia:
                    return NwSPKTouchResult_Win;
                case NwSPKCmd_Up:
                    return NwSPKTouchResult_Draw;
                default:
                    return NwSPKTouchResult_Lose;
            }
        }
        break;
        case NwSPKCmd_Middle:
        {
            switch (theOther)
            {
                case NwSPKCmd_Down:
                case NwSPKCmd_ZhaoJia:
                    return NwSPKTouchResult_Win;
                case NwSPKCmd_Middle:
                    return NwSPKTouchResult_Draw;
                default:
                    return NwSPKTouchResult_Lose;
            }
        }
        break;
        case NwSPKCmd_Down:
        {
            switch (theOther)
            {
                case NwSPKCmd_Up:
                case NwSPKCmd_ZhaoJia:
                case NwSPKCmd_ShanBi:
                    return NwSPKTouchResult_Win;
                case NwSPKCmd_Down:
                    return NwSPKTouchResult_Draw;
                default:
                    return NwSPKTouchResult_Lose;
            }
        }
        break;
        case NwSPKCmd_ZhaoJia:
        {
            switch (theOther)
            {
                case NwSPKCmd_ZhaoJia:
                case NwSPKCmd_ShanBi:
                    return NwSPKTouchResult_Draw;
                default:
                    return NwSPKTouchResult_Lose;
            }
        }
        break;
        case NwSPKCmd_ShanBi:
        {
            switch (theOther)
            {
                case NwSPKCmd_ZhaoJia:
                case NwSPKCmd_ShanBi:
                case NwSPKCmd_XuanFeng:
                    return NwSPKTouchResult_Draw;
                case NwSPKCmd_Down:
                case NwSPKCmd_FanSha:
                    return NwSPKTouchResult_Lose;
                default:
                    return NwSPKTouchResult_Win;
            }
        }
        break;
        case NwSPKCmd_XuanFeng:
        {
            switch (theOther)
            {
                case NwSPKCmd_XuanFeng:
                case NwSPKCmd_ShanBi:
                    return NwSPKTouchResult_Draw;
                default:
                    return NwSPKTouchResult_Win;
            }
        }
        break;
        case NwSPKCmd_FanSha:
        {
            switch (theOther)
            {
                case NwSPKCmd_XuanFeng:
                    return NwSPKTouchResult_Lose;
                case NwSPKCmd_FanSha:
                    return NwSPKTouchResult_Draw;
                default:
                    return NwSPKTouchResult_Win;
            }
        }
        break;
        default:
        {
            const char* szDesc = SoStrFmt("NwSPKJudge::CmdCompare : Unknown CmdType[%d]", theCmd);
            SoMessageBox("", szDesc);
            return NwSPKTouchResult_Draw;
        }
        break;
    }
    return NwSPKTouchResult_Draw;
}
//--------------------------------------------------------------------------------------------------
