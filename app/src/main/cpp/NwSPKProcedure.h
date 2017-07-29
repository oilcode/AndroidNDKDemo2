//--------------------------------------------------------------------
#ifndef _NwSPKProcedure_h_
#define _NwSPKProcedure_h_
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

protected:
    enum eSPKProcedureStep
    {
        //战斗流程尚未开始。
        SPKProcedureStep_None,
        SPKProcedureStep_PrePlayerOption, //玩家进行本回合操作的准备阶段
        SPKProcedureStep_PlayerOption, //玩家正在进行本回合操作
        SPKProcedureStep_PostPlayerOption, //玩家本回合操作结束，收尾阶段
        SPKProcedureStep_PreRound, //本回合战斗开始前的准备阶段
        SPKProcedureStep_PreTouch, //本次交锋前的准备阶段
        SPKProcedureStep_Touch, //交锋中
        SPKProcedureStep_Touch_2, //交锋中，开始刷新血条
        SPKProcedureStep_PostTouch, //交锋完毕，收尾阶段
        SPKProcedureStep_PostRound, //本回合结束，收尾阶段
        //
        SPKProcedureStep_Max,
    };

private:
	eSPKProcedureStep m_CurrentStep;
    //等待武将播放动画结束的倒计时
    float m_fCountDownForUnitAnim;
};
//--------------------------------------------------------------------
#endif //_NwSPKProcedure_h_
//--------------------------------------------------------------------



