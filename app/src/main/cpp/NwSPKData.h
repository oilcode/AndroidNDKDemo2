//--------------------------------------------------------------------------------------------------
#ifndef _NwSPKData_h_
#define _NwSPKData_h_
//--------------------------------------------------------------------------------------------------
#include "NwSPKDefine.h"
//--------------------------------------------------------------------------------------------------
class NwSPKData
{
public:
    NwSPKData();
    ~NwSPKData();
    void ResetSPKData();

    NwSPKHeroData* GetLeftHeroData();
    NwSPKHeroData* GetRightHeroData();
    const NwSPKSelectedCmd* GetLeftSelectedCmd();
    const NwSPKSelectedCmd* GetRightSelectedCmd();
    NwSPKCmdType GetLeftCmd_CurrentTouch();
    NwSPKCmdType GetRightCmd_CurrentTouch();

    void PrepareCmdListForNewRound();

    //设置选择了哪三个战斗指令
    void SetLeftSelectedCmd(NwSPKCmdType cmd0, NwSPKCmdType cmd1, NwSPKCmdType cmd2, bool bDongCha);
    //为AI生成战斗指令
    void GenerateCmdForAI();

    //处理一个回合开始的事件
    void OnRoundStart();
    //处理一次交锋结束的事件，返回本回合是否结束
    bool OnTouchFinished();
    int GetTouchIndex();
    bool IsAnySideHPEmpty();
    bool IsLeftSideWin();

private:
    NwSPKHeroData m_kLeftHeroData;
    NwSPKHeroData m_kRightHeroData;
    //记录已经选择好的指令
    NwSPKSelectedCmd m_kLeftSelectedCmd;
    NwSPKSelectedCmd m_kRightSelectedCmd;
    //记录当前是第几回合，回合计数从1开始，没有第0回合
    int m_nRoundCount;
    //记录当前正在处理第几次交锋，取值范围[0,NwSPKTouch_Max)
    int m_nTouchIndex;
};
//--------------------------------------------------------------------------------------------------
#endif //_NwSPKData_h_
//--------------------------------------------------------------------------------------------------
