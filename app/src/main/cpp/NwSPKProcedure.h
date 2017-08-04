//--------------------------------------------------------------------
#ifndef _NwSPKProcedure_h_
#define _NwSPKProcedure_h_
//--------------------------------------------------------------------
#include "NwSPKDefine.h"
//--------------------------------------------------------------------
class NwSPKProcedure
{
public:
	void UpdateSPKProcedure(float fDeltaTime);
    void StartSPKProcedure();
    void PlayerOptionFinished();

protected:
    friend class NwSceneSPK;
    NwSPKProcedure();
    ~NwSPKProcedure();
    void ProcessStepTouch();
    void ProcessStepTouch2();

protected:
    enum eSPKProcedureStep
    {
        //战斗流程尚未开始。
        SPKProcedureStep_None,
        SPKProcedureStep_PrepareForStart, //战斗初始化
        SPKProcedureStep_PrePlayerOption, //玩家选择指令
        SPKProcedureStep_PlayerOption, //玩家选择指令
        SPKProcedureStep_PostPlayerOption, //玩家选择指令
        SPKProcedureStep_PreRound, //本回合战斗开始前的准备阶段
        SPKProcedureStep_PreTouch, //本次交锋前的准备阶段
        SPKProcedureStep_Touch, //交锋中
        SPKProcedureStep_Touch_2, //交锋中，开始刷新血条
        SPKProcedureStep_Touch_3, //交锋中，开始刷新血条
        SPKProcedureStep_PostTouch, //交锋完毕，收尾阶段
        SPKProcedureStep_PostRound, //本回合结束，收尾阶段
        //
        SPKProcedureStep_Max,
    };

private:
	eSPKProcedureStep m_CurrentStep;
    //本步骤结束的倒计时
    float m_fCountDownForCurrentStep;
};
//--------------------------------------------------------------------
#endif //_NwSPKProcedure_h_
//--------------------------------------------------------------------



