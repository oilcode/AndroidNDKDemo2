//----------------------------------------------------------------
#ifndef _NwUISPK_h_
#define _NwUISPK_h_
//----------------------------------------------------------------
#include "NwBaseInclude.h"
#include "NwSPKDefine.h"
//----------------------------------------------------------------
class NwActorSPKData;
//----------------------------------------------------------------
class NwUISPK : public GGUIWindowPanel
{
public:
    enum eSideType
    {
        SideLeft,
        SideRight,
        SideMax,
    };

public:
    //开始选择指令阶段
    void StartSelectCmd(const NwActorSPKData* pSPKData);
    void StartSelectCmd2(const SPKHeroData* pSPKData);
    //更新血条
    void SetHP(eSideType theSide, int nMax, int nCur);
    void SetMP(eSideType theSide, int nMax, int nCur);
    //设置右方武将选择的指令
    void SetRightSelectedCmd(NwSPKTouchType theTouchIndex, NwSPKCmdType theCmd);
    //获取左方武将选择的指令
    NwSPKCmdType GetSelectedCmd(NwSPKTouchType theTouchIndex);

protected:
    friend class NwSceneSPK;
    NwUISPK();
    ~NwUISPK();
    bool InitUISPK();
    void ClearUISPK();
    void CreateWindows();
    void ProcessUIEvent(int nEventType, void* pParam);
    void OnBtnCmd(int nCmdIndex);
    void OnBtnTouch(int nTouchIndex);
    void RefreshCmdBtn();
    void RefreshTouchBtn();
    //寻找空的指令槽，如果找不到则返回 NwSPKTouch_Max
    NwSPKTouchType FindEmptyTouchBtn();
    //检测玩家选择指令的操作阶段是否结束
    void CheckPlayerOptionFinished();
    //设置所有的按钮可用和不可用
    void SetAllButtonEnableFlag(bool bEnable);

private:
    GGUIWindowButton* m_pBtnCmdList[NwSPKCmd_Max];
    GGUIWindowButton* m_pBtnTouchList[SideMax][NwSPKTouch_Max];
    GGUIWindowProcessBar* m_pHPList[SideMax];
    GGUIWindowProcessBar* m_pMPList[SideMax];
    GGUIWindowImage* m_pHeroList[SideMax];
    //记录客户端主角拥有的指令的个数
    int m_kOwnCmdCount[NwSPKCmd_Max];
    //记录客户端主角已经上架的指令
    NwSPKCmdType m_kSelectedCmdList[NwSPKTouch_Max];
};
//----------------------------------------------------------------
#endif //_NwUISPK_h_
//----------------------------------------------------------------
