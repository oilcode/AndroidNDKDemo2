//--------------------------------------------------------------------
#include "NwSPKProcedure.h"
#include "NwSceneSPK.h"
#include "NwSPKLogic.h"
#include "NwUISPK.h"
#include "NwUIEffect.h"
//--------------------------------------------------------------------
NwSPKProcedure::NwSPKProcedure()
:m_CurrentStep(SPKProcedureStep_None)
,m_fCountDownForUnitAnim(-1.0f)
{

}
//--------------------------------------------------------------------
NwSPKProcedure::~NwSPKProcedure()
{

}
//--------------------------------------------------------------------
void NwSPKProcedure::UpdateSPKProcedure(float fDeltaTime)
{
    NwSPKLogic* pSPKLogic = NwSceneSPK::Get()->GetSPKLogic();
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
            //初始化本回合的武将信息
            pSPKLogic->PrepareForRound_MyHero();
            pSPKLogic->PrepareForRound_AIHero();
            //根据武将信息，初始化界面
            const SPKHeroData* pLeftData = pSPKLogic->GetMyHeroData();
            const SPKHeroData* pRightData = pSPKLogic->GetAIHeroData();
            pUISPK->PrepareForStart(pLeftData);
            pUISPK->SetHP(NwUISPK::SideLeft, pLeftData->nMaxHP, pLeftData->nCurHP);
            pUISPK->SetHP(NwUISPK::SideRight, pRightData->nMaxHP, pRightData->nCurHP);
            pUISPK->SetMP(NwUISPK::SideLeft, pLeftData->nMaxEnergy, pLeftData->nCurEnergy);
            pUISPK->SetMP(NwUISPK::SideRight, pRightData->nMaxEnergy, pRightData->nCurEnergy);
            //
            nNextStep = SPKProcedureStep_PrePlayerOption;
            break;
        }
        case SPKProcedureStep_PrePlayerOption:
        {
            //初始化本回合的武将信息
            pSPKLogic->PrepareForRound_MyHero();
            pSPKLogic->PrepareForRound_AIHero();
            //根据武将信息，刷新界面
            const SPKHeroData* pLeftData = pSPKLogic->GetMyHeroData();
            pUISPK->StartSelectCmd(pLeftData);
            //
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
            //把玩家选择的指令汇报给 SPKLogic
            NwSPKCmdType cmd0 = pUISPK->GetSelectedCmd(NwSPKTouch_0);
            NwSPKCmdType cmd1 = pUISPK->GetSelectedCmd(NwSPKTouch_1);
            NwSPKCmdType cmd2 = pUISPK->GetSelectedCmd(NwSPKTouch_2);
            pSPKLogic->SetPlayerOption(cmd0, cmd1, cmd2);
            //为AI生成战斗指令
            pSPKLogic->GenerateCmdForAI();
            //
            nNextStep = SPKProcedureStep_PreRound;
            break;
        }
        case SPKProcedureStep_PreRound:
        {
            pSPKLogic->IncreaseRoundCount();
            //把AI的战斗指令显示在界面上
            for (int i = 0; i < NwSPKTouch_Max; ++i)
            {
                NwSPKCmdType theCmd = pSPKLogic->GetAITouchCmd(i);
                pUISPK->SetRightSelectedCmd((NwSPKTouchType)i, theCmd);
            }
            nNextStep = SPKProcedureStep_PreTouch;
            break;
        }
        case SPKProcedureStep_PreTouch:
        {
            //做交锋的提示动画
            pUISPK->PlayTouchBtnEffect((NwSPKTouchType)pSPKLogic->GetCurrentTouchIndex());
            //判断本次交锋的输赢
            pSPKLogic->GenerateCurrentTouchResult();
            m_fCountDownForUnitAnim = 1.0f;
            nNextStep = SPKProcedureStep_Touch;
            break;
        }
        case SPKProcedureStep_Touch:
        {
            m_fCountDownForUnitAnim -= fDeltaTime;
            if (m_fCountDownForUnitAnim < 0.0f)
            {
                //玩家模型做攻击和受击表现
                NwSPKTouchResult theResult = pSPKLogic->GetTouchResult();
                if (theResult == NwSPKTouchResult_Win)
                {
                    int nDamage = pSPKLogic->GetTouchAttackDamage();
                    if (nDamage > 0)
                    {
                        const GGUIRect& kRect = pUISPK->GetHeroRect(NwUISPK::SideRight);
                        stDamageNumberParam kParam;
                        kParam.nNumber = nDamage;
                        kParam.fStartPosX = kRect.x + kRect.w + 20.0f;
                        kParam.fStartPosY = kRect.y;
                        kParam.fTime = 1.8f;
                        NwUIEffect::Get()->PlayDamageNumber(kParam);
                    }
                }
                else if (theResult == NwSPKTouchResult_Lose)
                {
                    int nDamage = pSPKLogic->GetTouchAttackDamage();
                    if (nDamage > 0)
                    {
                        const GGUIRect& kRect = pUISPK->GetHeroRect(NwUISPK::SideLeft);
                        stDamageNumberParam kParam;
                        kParam.nNumber = nDamage;
                        kParam.fStartPosX = kRect.x - 100.0f;
                        kParam.fStartPosY = kRect.y;
                        kParam.fTime = 1.8f;
                        NwUIEffect::Get()->PlayDamageNumber(kParam);
                    }
                }
                else if (theResult == NwSPKTouchResult_Draw)
                {

                }

                if (theResult == NwSPKTouchResult_Draw)
                {
                    //没有伤害跳字，所以缩短时间
                    m_fCountDownForUnitAnim = 0.1f;
                }
                else
                {
                    m_fCountDownForUnitAnim = 1.0f;
                }
                nNextStep = SPKProcedureStep_Touch_2;
            }
            break;
        }
        case SPKProcedureStep_Touch_2:
        {
            m_fCountDownForUnitAnim -= fDeltaTime;
            if (m_fCountDownForUnitAnim < 0.0f)
            {
                //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                //开始刷新血条
                //把本次交锋的结果应用到玩家数据上
                pSPKLogic->ApplyTouchResult();
                //把玩家数据显示在界面上
                NwSPKTouchResult theResult = pSPKLogic->GetTouchResult();
                const SPKHeroData* pMyData = pSPKLogic->GetMyHeroData();
                const SPKHeroData* pAIData = pSPKLogic->GetAIHeroData();
                if (theResult == NwSPKTouchResult_Win)
                {
                    pUISPK->SetMP(NwUISPK::SideLeft, pMyData->nMaxEnergy, pMyData->nCurEnergy);
                    pUISPK->SetHP(NwUISPK::SideRight, pAIData->nMaxHP, pAIData->nCurHP);
                }
                else if (theResult == NwSPKTouchResult_Lose)
                {
                    pUISPK->SetHP(NwUISPK::SideLeft, pMyData->nMaxHP, pMyData->nCurHP);
                    pUISPK->SetMP(NwUISPK::SideRight, pAIData->nMaxEnergy, pAIData->nCurEnergy);
                }
                else
                {
                    pUISPK->SetMP(NwUISPK::SideLeft, pMyData->nMaxEnergy, pMyData->nCurEnergy);
                    pUISPK->SetMP(NwUISPK::SideRight, pAIData->nMaxEnergy, pAIData->nCurEnergy);
                }
                pUISPK->SetXuanYun(NwUISPK::SideLeft, pMyData->bDizzy);
                pUISPK->SetXuanYun(NwUISPK::SideRight, pAIData->bDizzy);
                //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                m_fCountDownForUnitAnim = 0.5f;
                nNextStep = SPKProcedureStep_Touch_3;
            }
            break;
        }
        case SPKProcedureStep_Touch_3:
        {
            m_fCountDownForUnitAnim -= fDeltaTime;
            if (m_fCountDownForUnitAnim < 0.0f)
            {
                nNextStep = SPKProcedureStep_PostTouch;
            }
            break;
        }
        case SPKProcedureStep_PostTouch:
        {
            //
            pSPKLogic->TouchFinished();
            if (pSPKLogic->IsRoundFinish())
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
            if (pSPKLogic->IsFightFinish())
            {
                //战斗结束
                pUISPK->ShowPKResult(pSPKLogic->IsMainPlayerWin());
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








