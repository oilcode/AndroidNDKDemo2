//--------------------------------------------------------------------
#include "NwSPKProcedure.h"
#include "NwSPKLogic.h"
#include "NwUISPK.h"
//--------------------------------------------------------------------
NwSPKProcedure::NwSPKProcedure(NwSPKLogic* pSPKLogic, NwUISPK* pUISPK)
:m_pSPKLogic(pSPKLogic)
,m_pUISPK(pUISPK)
,m_CurrentStep(SPKProcedureStep_None)
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
        case SPKProcedureStep_PrePlayerOption:
        {
            //初始化本回合的武将信息
            m_pSPKLogic->PrepareForRound_MyHero();
            m_pSPKLogic->PrepareForRound_AIHero();
            //根据武将信息，初始化界面
            m_pUISPK->RefreshLeftByHeroData(m_pSPKLogic->GetMyHeroData());
            m_pUISPK->RefreshRightByHeroData(m_pSPKLogic->GetAIHeroData());
            //
            nNextStep = SPKProcedureStep_PlayerOption;
            break;
        }
        case SPKProcedureStep_PostPlayerOption:
        {
            //把玩家选择的指令汇报给 SPKLogic
            eCmdButton cmd0 = m_pUISPK->GetLeftSelectedCmd(TouchBtn_0);
            eCmdButton cmd1 = m_pUISPK->GetLeftSelectedCmd(TouchBtn_1);
            eCmdButton cmd2 = m_pUISPK->GetLeftSelectedCmd(TouchBtn_2);
            m_pSPKLogic->SetPlayerOption(cmd0, cmd1, cmd2);
            //为AI生成战斗指令
            m_pSPKLogic->GenerateCmdForAI();
            //
            nNextStep = SPKProcedureStep_PreRound;
            break;
        }
        case SPKProcedureStep_PreRound:
        {
            m_pSPKLogic->IncreaseRoundCount();
            //把AI的战斗指令显示在界面上
            for (int i = 0; i < TouchBtn_Max; ++i)
            {
                eCmdButton theCmd = m_pSPKLogic->GetAITouchCmd(i);
                m_pUISPK->SetRightSelectedCmd(i, theCmd);
            }
            nNextStep = SPKProcedureStep_PreTouch;
            break;
        }
        case SPKProcedureStep_PreTouch:
        {
            //判断本次交锋的输赢
            m_pSPKLogic->GenerateCurrentTouchResult();
            //玩家模型做攻击和受击表现
            eTouchResult theResult = m_pSPKLogic->GetTouchResult();
            if (theResult == TouchResult_Win)
            {
                m_pUISPK->PlayAnim_LeftUnit(0);
                m_pUISPK->PlayAnim_RightUnit(0);
                int nDamage = m_pSPKLogic->GetTouchAttackDamage();
                if (nDamage > 0)
                {
                    m_pUISPK->PlayDamageString_RightUnit(nDamage);
                }
            }
            else if (theResult == TouchResult_Lose)
            {
                m_pUISPK->PlayAnim_LeftUnit(0);
                m_pUISPK->PlayAnim_RightUnit(0);
                int nDamage = m_pSPKLogic->GetTouchAttackDamage();
                if (nDamage > 0)
                {
                    m_pUISPK->PlayDamageString_LeftUnit(nDamage);
                }
            }
            else if (theResult == TouchResult_Draw)
            {
                m_pUISPK->PlayAnim_LeftUnit(0);
                m_pUISPK->PlayAnim_RightUnit(0);
            }
            m_pUISPK->PlayCmdName_LeftUnit(m_pSPKLogic->GetMyFinalCmdName());
            m_pUISPK->PlayCmdName_RightUnit(m_pSPKLogic->GetAIFinalCmdName());
            m_fCountDownForUnitAnim = 1.0f;
            //
            nNextStep = SPKProcedureStep_Touch;
            break;
        }
        case SPKProcedureStep_Touch:
        {
            m_fCountDownForUnitAnim -= fDeltaTime;
            if (m_fCountDownForUnitAnim < 0.0f)
            {
                //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                //开始刷新血条
                //把本次交锋的结果应用到玩家数据上
                m_pSPKLogic->ApplyTouchResult();
                //把玩家数据显示在界面上
                eTouchResult theResult = m_pSPKLogic->GetTouchResult();
                const SPKHeroData* pMyData = m_pSPKLogic->GetMyHeroData();
                const SPKHeroData* pAIData = m_pSPKLogic->GetAIHeroData();
                if (theResult == TouchResult_Win)
                {
                    m_pUISPK->RefreshLeftEnergy(pMyData->nMaxEnergy, pMyData->nCurEnergy);
                    m_pUISPK->RefreshRightBlood(pAIData->nMaxHP, pAIData->nCurHP);
                }
                else if (theResult == TouchResult_Lose)
                {
                    m_pUISPK->RefreshLeftBlood(pMyData->nMaxHP, pMyData->nCurHP);
                    m_pUISPK->RefreshRightEnergy(pAIData->nMaxEnergy, pAIData->nCurEnergy);
                }
                else
                {
                    m_pUISPK->RefreshLeftEnergy(pMyData->nMaxEnergy, pMyData->nCurEnergy);
                    m_pUISPK->RefreshRightEnergy(pAIData->nMaxEnergy, pAIData->nCurEnergy);
                }
                //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                m_fCountDownForUnitAnim = 1.0f;
                nNextStep = SPKProcedureStep_Touch_2;
            }
            break;
        }
        case SPKProcedureStep_Touch_2:
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
            m_pSPKLogic->TouchFinished();
            if (m_pSPKLogic->IsRoundFinish() == true)
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
            if (m_pSPKLogic->IsFightFinish() == true)
            {
                //战斗结束
                //UISceneSwitch::GoToNextScene(Scene_Logo);
            }
            else
            {
                nNextStep = SPKProcedureStep_PrePlayerOption;
            }
            break;
        }
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
    m_CurrentStep = SPKProcedureStep_PrePlayerOption;
}
//--------------------------------------------------------------------
void NwSPKProcedure::PlayerOptionFinished()
{
    m_CurrentStep = SPKProcedureStep_PostPlayerOption;
}
//--------------------------------------------------------------------








