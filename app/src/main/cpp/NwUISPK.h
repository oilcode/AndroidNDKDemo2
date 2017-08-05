//----------------------------------------------------------------
#ifndef _NwUISPK_h_
#define _NwUISPK_h_
//----------------------------------------------------------------
#include "NwBaseInclude.h"
#include "NwSPKDefine.h"
//----------------------------------------------------------------
class NwUISPK : public GGUIWindowPanel
{
public:
    void PrepareForStart();
    //开始选择指令阶段
    void StartSelectCmd();
    void RefreshUIWithHeroData(const NwSPKHeroData* pSPKData, NwSPKSideType theSide);
    //设置右方武将选择的指令
    void SetRightSelectedCmd(NwSPKTouchType theTouchIndex, NwSPKCmdType theCmd);
    //获取左方武将选择的指令
    NwSPKCmdType GetSelectedCmd(NwSPKTouchType theTouchIndex);
    //获取武将图片的矩形范围
    const GGUIRect& GetHeroRect(NwSPKSideType theSide);
    //做交锋的提示动画
    void PlayTouchBtnEffect(NwSPKTouchType theTouchIndex);
    //显示PK结果
    void ShowPKResult(bool bWin);

protected:
    friend class NwSceneSPK;
    NwUISPK();
    ~NwUISPK();
    bool InitUISPK();
    void ClearUISPK();
    void CreateWindows();
    bool InputWindow(GGUIInputMsg* pInputMsg);
    void ProcessUIEvent(int nEventType, void* pParam);
    void OnBtnCmd(int nCmdIndex);
    void OnBtnTouch(int nTouchIndex);
    void RefreshCmdBtn();
    void RefreshCmdCount();
    void RefreshTouchBtn();
    //更新血条
    void SetHP(NwSPKSideType theSide, int nMax, int nCur);
    void SetMP(NwSPKSideType theSide, int nMax, int nCur);
    void SetXuanYun(NwSPKSideType theSide, bool bXuanYun);
    //寻找空的指令槽，如果找不到则返回 NwSPKTouch_Max
    NwSPKTouchType FindEmptyTouchBtn();
    //检测玩家选择指令的操作阶段是否结束
    void CheckPlayerOptionFinished();
    //设置所有的按钮可用和不可用
    void SetAllButtonEnableFlag(bool bEnable);

private:
    GGUIWindowButton* m_pBtnCmdList[NwSPKCmd_Max];
    GGUIWindowButton* m_pBtnTouchList[NwSPKSide_Max][NwSPKTouch_Max];
    GGUIWindowProcessBar* m_pHPList[NwSPKSide_Max];
    GGUIWindowProcessBar* m_pMPList[NwSPKSide_Max];
    GGUIWindowImage* m_pHeroList[NwSPKSide_Max];
    GGUIWindowImage* m_pImgXuanYunList[NwSPKSide_Max];
    GGUIWindowImage* m_pImgSPKResult;
    //记录客户端主角拥有的指令的个数
    int m_kOwnCmdCount[NwSPKCmd_Max];
    //记录客户端主角已经上架的指令
    NwSPKCmdType m_kSelectedCmdList[NwSPKTouch_Max];
    //在玩家选择指令期间，是否处于眩晕中
    bool m_bXuanYun;
    //是否正在显示战斗结果
    bool m_bShowPKResult;
};
//----------------------------------------------------------------
#endif //_NwUISPK_h_
//----------------------------------------------------------------
