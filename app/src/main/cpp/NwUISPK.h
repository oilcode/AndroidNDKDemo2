//----------------------------------------------------------------
#ifndef _NwUISPK_h_
#define _NwUISPK_h_
//----------------------------------------------------------------
#include "NwBaseInclude.h"
#include "NwSPKLogic.h"
//----------------------------------------------------------------
class NwSPKLogic;
class NwSPKProcedure;
//----------------------------------------------------------------
class NwUISPK : public GGUIWindowPanel
{
public:
    static bool CreateUISPK();
    static void ReleaseUISPK();
    static NwUISPK* Get();

    void UpdateUISPK(float fDeltaTime);

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void RefreshLeftByHeroData(const SPKHeroData* pHeroData);
    void RefreshRightByHeroData(const SPKHeroData* pHeroData);

    void RefreshLeftBlood(int nMax, int nCur);
    void RefreshRightBlood(int nMax, int nCur);
    void RefreshLeftEnergy(int nMax, int nCur);
    void RefreshRightEnergy(int nMax, int nCur);
    void RefreshCmdBtn(const SPKHeroData* pHeroData);
    void RefreshTouchBtn();

    eCmdButton GetLeftSelectedCmd(eTouchButton theTouchIndex);
    //设置右方武将选择的指令
    void SetRightSelectedCmd(int theTouchIndex, eCmdButton theCmd);

    void PlayAnim_LeftUnit(int theAnim);
    void PlayAnim_RightUnit(int theAnim);
    //头顶冒字
    void PlayCmdName_LeftUnit(const char* szCmdName);
    void PlayCmdName_RightUnit(const char* szCmdName);
    void PlayDamageString_LeftUnit(int nNumber);
    void PlayDamageString_RightUnit(int nNumber);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


private:
    NwUISPK();
    ~NwUISPK();
    bool InitUISPK();
    void ClearUISPK();
    void CreateWindows();
    void ProcessUIEvent(int nEventType, void* pParam);
    void OnBtnCard(int nCardIndex);
    void OnBtnTouch(int nIndex);

    //寻找空的指令槽，如果找不到则返回TouchBtn_Max
    eTouchButton FindEmptyTouchBtn();
    //检测玩家选择指令的操作阶段是否结束
    void CheckPlayerOptionFinished();
    //设置所有的按钮可用和不可用
    void SetAllButtonEnableFlag(bool bEnable);

private:
    static NwUISPK* ms_pInstance;
    NwSPKLogic* m_pSPKLogic;
    NwSPKProcedure* m_pSPKProcedure;

    GGUIWindowButton* m_pCardBtnList[CmdBtn_Max];
    GGUIWindowButton* m_pLeftTouchBtnList[TouchBtn_Max];
    GGUIWindowButton* m_pRightTouchBtnList[TouchBtn_Max];
    GGUIWindowProcessBar* m_pLeftBlood;
    GGUIWindowProcessBar* m_pRightBlood;
    GGUIWindowProcessBar* m_pLeftEnergy;
    GGUIWindowProcessBar* m_pRightEnergy;
    GGUIWindowImage* m_pHeroLeft;
    GGUIWindowImage* m_pHeroRight;

    //记录玩家已经上架的指令
    eCmdButton m_eLeftSelectedCmd[TouchBtn_Max];

    //保存玩家的武将拥有的指令信息
    SPKHeroData m_kTempHeroData;
};
//----------------------------------------------------------------
inline NwUISPK* NwUISPK::Get()
{
    return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_NwUISPK_h_
//----------------------------------------------------------------
