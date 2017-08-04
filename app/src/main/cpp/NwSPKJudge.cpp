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
        SameCmd(&kLeftResultSingle, &kRightResultSingle);
        return;
    }

    NwSPKTouchResult theCompareResult = CmdCompare(theLeftCmd, theRightCmd);
    if (theCompareResult == NwSPKTouchResult_Draw)
    {
        kLeftResultSingle.theResult = NwSPKTouchResult_Draw;
        kRightResultSingle.theResult = NwSPKTouchResult_Draw;
        DrawCmd(&kLeftResultSingle, &kRightResultSingle);
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
    switch (theCmd)
    {
        case NwSPKCmd_Up:
        case NwSPKCmd_Middle:
        case NwSPKCmd_Down:
        case NwSPKCmd_FanSha:
        {
            pWinnerResultSingle->nDeltaMP += CalculateMP();
            pOtherResultSingle->nDeltaHP -= CalculateNormalDamage(pWinnerHero);
        }
        break;
        case NwSPKCmd_XuanFeng:
        {
            pWinnerResultSingle->nDeltaMP += CalculateMP();
            pOtherResultSingle->nDeltaHP -= CalculateXuanFengDamage(pWinnerHero);
        }
        break;
        case NwSPKCmd_ZhaoJia:
        case NwSPKCmd_ShanBi:
        {
            pWinnerResultSingle->nDeltaMP += CalculateMP();
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
void NwSPKJudge::SameCmd(NwSPKResultSingle* pLeftSingle, NwSPKResultSingle* pRightSingle)
{
    pLeftSingle->nDeltaMP += CalculateMP();
    pRightSingle->nDeltaMP += CalculateMP();
    pLeftSingle->nDeltaSamePoint += 1;
    pRightSingle->nDeltaSamePoint += 1;
}
//--------------------------------------------------------------------------------------------------
void NwSPKJudge::DrawCmd(NwSPKResultSingle* pLeftSingle, NwSPKResultSingle* pRightSingle)
{
    pLeftSingle->nDeltaMP += CalculateMP();
    pRightSingle->nDeltaMP += CalculateMP();
}
//--------------------------------------------------------------------------------------------------
void NwSPKJudge::WinnerAttack(NwSPKCmdType theWinnerCmd, NwSPKCmdType theOtherCmd, const NwSPKHeroData* pWinnerHero, const NwSPKHeroData* pOtherHero, NwSPKResultSingle* pWinnerSingle, NwSPKResultSingle* pOtherSingle)
{
    switch (theWinnerCmd)
    {
        case NwSPKCmd_ShanBi:
        {
            pOtherSingle->AddBuff(NwSPKBuff_XuanYun, NwSPK_XuanYunTouchCount);
            //
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
            //
            pWinnerSingle->nDeltaMP += CalculateMP();
            pOtherSingle->nDeltaMP += CalculateMP();
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
