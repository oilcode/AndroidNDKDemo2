//--------------------------------------------------------------------
#include "NwSPKProcedure.h"
#include "NwSceneSPK.h"
#include "NwSPKData.h"
#include "NwSPKJudge.h"
#include "NwUISPK.h"
#include "NwUIEffect.h"
//--------------------------------------------------------------------
NwSPKProcedure::NwSPKProcedure()
:m_CurrentStep(SPKProcedureStep_None)
,m_fCountDownForCurrentStep(-1.0f)
{

}
//--------------------------------------------------------------------
NwSPKProcedure::~NwSPKProcedure()
{

}
//--------------------------------------------------------------------
void NwSPKProcedure::UpdateSPKProcedure(float fDeltaTime)
{
    NwSPKData* pSPKData = NwSceneSPK::Get()->GetSPKData();
    NwUISPK* pUISPK = NwSceneSPK::Get()->GetUISPK();

    //更新战斗流程。
	const int nCurrentStep = (int)m_CurrentStep;
    eSPKProcedureStep nNextStep = SPKProcedureStep_Max;
    //
    switch (nCurrentStep)
    {
        case SPKProcedureStep_None:
        {
            //尚未开始，什么都不做
            break;
        }
        case SPKProcedureStep_PrepareForStart:
        {
            pUISPK->PrepareForStart();
            nNextStep = SPKProcedureStep_PrePlayerOption;
            break;
        }
        case SPKProcedureStep_PrePlayerOption:
        {
            pSPKData->OnRoundStart();
            //初始化本回合的武将信息
            pSPKData->PrepareCmdListForNewRound();
            //根据武将信息，刷新界面
            const NwSPKHeroData* pLeftHeroData = pSPKData->GetLeftHeroData();
            const NwSPKHeroData* pRightHeroData = pSPKData->GetRightHeroData();
            pUISPK->RefreshUIWithHeroData(pLeftHeroData, NwSPKSide_Left);
            pUISPK->RefreshUIWithHeroData(pRightHeroData, NwSPKSide_Right);
            //注意，先执行RefreshUIWithHeroData，再执行这个函数。
            pUISPK->StartSelectCmd();
            nNextStep = SPKProcedureStep_PlayerOption;
            break;
        }
        case SPKProcedureStep_PlayerOption:
        {
            //什么都不做。玩家正在操作界面。等待玩家操作结束的事件。
            break;
        }
        case SPKProcedureStep_PostPlayerOption:
        {
            //把玩家选择的指令汇报给 SPKData
            NwSPKCmdType cmd0 = pUISPK->GetSelectedCmd(NwSPKTouch_0);
            NwSPKCmdType cmd1 = pUISPK->GetSelectedCmd(NwSPKTouch_1);
            NwSPKCmdType cmd2 = pUISPK->GetSelectedCmd(NwSPKTouch_2);
            pSPKData->SetLeftSelectedCmd(cmd0, cmd1, cmd2);
            //为AI生成战斗指令
            pSPKData->GenerateCmdForAI();
            nNextStep = SPKProcedureStep_PreRound;
            break;
        }
        case SPKProcedureStep_PreRound:
        {
            //把AI的战斗指令显示在界面上
            const NwSPKSelectedCmd* pRightSelectedCmd = pSPKData->GetRightSelectedCmd();
            for (int i = 0; i < NwSPKTouch_Max; ++i)
            {
                pUISPK->SetRightSelectedCmd((NwSPKTouchType)i, pRightSelectedCmd->kCmdList[i]);
            }
            nNextStep = SPKProcedureStep_PreTouch;
            break;
        }
        case SPKProcedureStep_PreTouch:
        {
            //做交锋的提示动画
            pUISPK->PlayTouchBtnEffect((NwSPKTouchType)pSPKData->GetTouchIndex());
            //判断本次交锋的输赢
            NwSPKJudge* pSPKJudge = NwSceneSPK::Get()->GetSPKJudge();
            pSPKJudge->StartJudgeTouch(pSPKData->GetTouchIndex(), pSPKData->GetLeftHeroData(), pSPKData->GetRightHeroData(),
                                        pSPKData->GetLeftCmd_CurrentTouch(), pSPKData->GetRightCmd_CurrentTouch());
            m_fCountDownForCurrentStep = 1.0f;
            nNextStep = SPKProcedureStep_Touch;
            break;
        }
        case SPKProcedureStep_Touch:
        {
            m_fCountDownForCurrentStep -= fDeltaTime;
            if (m_fCountDownForCurrentStep < 0.0f)
            {
                ProcessStepTouch();
                nNextStep = SPKProcedureStep_Touch_2;
            }
            break;
        }
        case SPKProcedureStep_Touch_2:
        {
            m_fCountDownForCurrentStep -= fDeltaTime;
            if (m_fCountDownForCurrentStep < 0.0f)
            {
                ProcessStepTouch2();
                nNextStep = SPKProcedureStep_Touch_3;
            }
            break;
        }
        case SPKProcedureStep_Touch_3:
        {
            m_fCountDownForCurrentStep -= fDeltaTime;
            if (m_fCountDownForCurrentStep < 0.0f)
            {
                nNextStep = SPKProcedureStep_PostTouch;
            }
            break;
        }
        case SPKProcedureStep_PostTouch:
        {
            bool bRoundFinish = pSPKData->OnTouchFinished();
            //把玩家数据显示在界面上，主要目的是刷新buff状态
            pUISPK->RefreshUIWithHeroData(pSPKData->GetLeftHeroData(), NwSPKSide_Left);
            pUISPK->RefreshUIWithHeroData(pSPKData->GetRightHeroData(), NwSPKSide_Right);
            //
            if (bRoundFinish)
            {
                nNextStep = SPKProcedureStep_PostRound;
            }
            else
            {
                nNextStep = SPKProcedureStep_PreTouch;
            }
            break;
        }
        case SPKProcedureStep_PostRound:
        {
            if (pSPKData->IsAnySideHPEmpty())
            {
                //战斗结束
                pUISPK->ShowPKResult(pSPKData->IsLeftSideWin());
            }
            else
            {
                nNextStep = SPKProcedureStep_PrePlayerOption;
            }
            break;
        }
        default:
            break;
    }
    //
    if (nNextStep != SPKProcedureStep_Max)
    {
        m_CurrentStep = nNextStep;
    }
}
//--------------------------------------------------------------------
void NwSPKProcedure::StartSPKProcedure()
{
    m_CurrentStep = SPKProcedureStep_PrepareForStart;
}
//--------------------------------------------------------------------
void NwSPKProcedure::PlayerOptionFinished()
{
    m_CurrentStep = SPKProcedureStep_PostPlayerOption;
}
//--------------------------------------------------------------------
void NwSPKProcedure::ProcessStepTouch()
{
    //做攻击和受击表现
    //目前只有伤害跳字表现
    NwSPKData* pSPKData = NwSceneSPK::Get()->GetSPKData();
    NwSPKJudge* pSPKJudge = NwSceneSPK::Get()->GetSPKJudge();
    NwUISPK* pUISPK = NwSceneSPK::Get()->GetUISPK();

    const int nTouchIndex = pSPKData->GetTouchIndex();
    const NwSPKResultRound* pJudgeResult = pSPKJudge->GetResultRound();
    const NwSPKResultSingle& kLeftResult = pJudgeResult->kTouchList[nTouchIndex].kSideList[NwSPKSide_Left];
    const NwSPKResultSingle& kRightResult = pJudgeResult->kTouchList[nTouchIndex].kSideList[NwSPKSide_Right];

    bool bPlayDamageNum = false;
    NwSPKTouchResult theLeftResult = kLeftResult.theResult;
    if (theLeftResult == NwSPKTouchResult_Win)
    {
        if (kRightResult.nDeltaHP < 0)
        {
            //右方做伤害跳字
            const GGUIRect& kRect = pUISPK->GetHeroRect(NwSPKSide_Right);
            stDamageNumberParam kParam;
            kParam.nNumber = kRightResult.nDeltaHP;
            kParam.fStartPosX = kRect.x + kRect.w + 20.0f;
            kParam.fStartPosY = kRect.y;
            kParam.fTime = 1.8f;
            NwUIEffect::Get()->PlayDamageNumber(kParam);
            bPlayDamageNum = true;
        }
    }
    else if (theLeftResult == NwSPKTouchResult_Lose)
    {
        if (kLeftResult.nDeltaHP)
        {
            //左方做伤害跳字
            const GGUIRect& kRect = pUISPK->GetHeroRect(NwSPKSide_Left);
            stDamageNumberParam kParam;
            kParam.nNumber = kLeftResult.nDeltaHP;
            kParam.fStartPosX = kRect.x - 100.0f;
            kParam.fStartPosY = kRect.y;
            kParam.fTime = 1.8f;
            NwUIEffect::Get()->PlayDamageNumber(kParam);
            bPlayDamageNum = true;
        }
    }
    else if (theLeftResult == NwSPKTouchResult_Draw)
    {
        //没有伤害跳字
    }

    if (bPlayDamageNum)
    {
        m_fCountDownForCurrentStep = 1.0f;
    }
    else
    {
        //没有伤害跳字，所以缩短时间
        m_fCountDownForCurrentStep = 0.1f;
    }
}
//--------------------------------------------------------------------
void NwSPKProcedure::ProcessStepTouch2()
{
    //把战斗结果应用到角色数据上，并刷新UI界面。
    NwSPKData* pSPKData = NwSceneSPK::Get()->GetSPKData();
    NwSPKJudge* pSPKJudge = NwSceneSPK::Get()->GetSPKJudge();
    NwUISPK* pUISPK = NwSceneSPK::Get()->GetUISPK();

    const int nTouchIndex = pSPKData->GetTouchIndex();
    NwSPKHeroData* pLeftHeroData = pSPKData->GetLeftHeroData();
    NwSPKHeroData* pRightHeroData = pSPKData->GetRightHeroData();
    const NwSPKResultRound* pJudgeResult = pSPKJudge->GetResultRound();
    const NwSPKResultSingle& kLeftResult = pJudgeResult->kTouchList[nTouchIndex].kSideList[NwSPKSide_Left];
    const NwSPKResultSingle& kRightResult = pJudgeResult->kTouchList[nTouchIndex].kSideList[NwSPKSide_Right];

    pLeftHeroData->ProcessSPKResult(&kLeftResult);
    pRightHeroData->ProcessSPKResult(&kRightResult);

    //把玩家数据显示在界面上
    pUISPK->RefreshUIWithHeroData(pLeftHeroData, NwSPKSide_Left);
    pUISPK->RefreshUIWithHeroData(pRightHeroData, NwSPKSide_Right);
    
    m_fCountDownForCurrentStep = 0.5f;
}
//--------------------------------------------------------------------








