//----------------------------------------------------------------
#include "NwUISPK.h"
#include "NwSPKLogic.h"
#include "NwSPKProcedure.h"
#include "GGUIActionFactory.h"

//----------------------------------------------------------------
NwUISPK* NwUISPK::ms_pInstance = 0;
const char* g_CmdBtnTexture[CmdBtn_Max] =
{
    "uitexture/mm4:hud_31",
    "uitexture/mm4:hud_32",
    "uitexture/mm4:hud_33",
    "uitexture/mm4:hud_34",
    "uitexture/mm5:hud_35",
    "uitexture/mm5:hud_36",
    "uitexture/mm5:hud_37",
    "uitexture/mm5:hud_38",
};
//----------------------------------------------------------------
bool NwUISPK::CreateUISPK()
{
    bool br = true;
    if (ms_pInstance == 0)
    {
        ms_pInstance = new NwUISPK;
        if (ms_pInstance && ms_pInstance->InitUISPK())
        {
            br = true;
        }
        else
        {
            ReleaseUISPK();
            br = false;
        }
    }
    return br;
}
//----------------------------------------------------------------
void NwUISPK::ReleaseUISPK()
{
    if (ms_pInstance)
    {
        delete ms_pInstance;
        ms_pInstance = 0;
    }
}
//----------------------------------------------------------------
NwUISPK::NwUISPK()
:m_pSPKLogic(NULL)
,m_pSPKProcedure(NULL)
,m_pLeftBlood(NULL)
,m_pRightBlood(NULL)
,m_pLeftEnergy(NULL)
,m_pRightEnergy(NULL)
,m_pHeroLeft(NULL)
,m_pHeroRight(NULL)
{
    for (int i = 0; i < CmdBtn_Max; ++i)
    {
        m_pCardBtnList[i] = NULL;
    }
    for (int i = 0; i < TouchBtn_Max; ++i)
    {
        m_pLeftTouchBtnList[i] = NULL;
        m_pRightTouchBtnList[i] = NULL;
        m_eLeftSelectedCmd[i] = CmdBtn_Max;
    }
}
//----------------------------------------------------------------
NwUISPK::~NwUISPK()
{
    ClearUISPK();
}
//----------------------------------------------------------------
bool NwUISPK::InitUISPK()
{
    CreateWindows();
    m_pSPKLogic = SoNew NwSPKLogic;
    m_pSPKProcedure = SoNew NwSPKProcedure(m_pSPKLogic, this);
    m_pSPKProcedure->StartSPKProcedure();
    return true;
}
//----------------------------------------------------------------
void NwUISPK::ClearUISPK()
{
    GGUIWindowPanel::ClearWindow();
    if (m_pSPKLogic)
    {
        SoDelete m_pSPKLogic;
        m_pSPKLogic = NULL;
    }
    if (m_pSPKProcedure)
    {
        SoDelete m_pSPKProcedure;
        m_pSPKProcedure = NULL;
    }
    for (int i = 0; i < CmdBtn_Max; ++i)
    {
        m_pCardBtnList[i] = NULL;
    }
}
//----------------------------------------------------------------
void NwUISPK::UpdateUISPK(float fDeltaTime)
{
    if (m_pSPKProcedure)
    {
        m_pSPKProcedure->UpdateSPKProcedure(fDeltaTime);
    }
}
//----------------------------------------------------------------
bool NwUISPK::InputWindow(GGUIInputMsg* pInputMsg)
{
    if (GGUIWindowPanel::InputWindow(pInputMsg))
    {
        return true;
    }

    if (pInputMsg->theType == GGUIInputMsg_TouchUp)
    {
        pInputMsg->bSwallowed = true;

        GGUIActionGroup* theActionGroup = m_pHeroRight->CreateActionGroup();
        theActionGroup->ClearAllAction();

        const GGUIFullRect& kFullRect = m_pHeroRight->GetFullRect();
        GGUIActionMove* pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
        pActionMove->InitActionMove(pInputMsg->fPosX - kFullRect.fDeltaX, pInputMsg->fPosY - kFullRect.fDeltaY, 1.0f);

        GGUIActionLine* pActionLine = (GGUIActionLine*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Line);;
        pActionLine->AddAction(pActionMove);

        theActionGroup->AddActionLine(pActionLine);
        return true;
    }

    return false;
}
//----------------------------------------------------------------
void NwUISPK::ProcessUIEvent(int nEventType, void* pParam)
{
    if (nEventType == GGUIEvent_Button_Clicked)
    {
        const GGUIEventParam_Button_Clicked* pClickParam = (GGUIEventParam_Button_Clicked*)pParam;
        for (int i = 0; i < CmdBtn_Max; ++i)
        {
            if (m_pCardBtnList[i]->GetID() == pClickParam->nWindowID)
            {
                OnBtnCard(i);
                break;
            }
        }
        for (int i = 0; i < TouchBtn_Max; ++i)
        {
            if (m_pLeftTouchBtnList[i]->GetID() == pClickParam->nWindowID)
            {
                OnBtnTouch(i);
                break;
            }
        }
    }
}
//--------------------------------------------------------------------
void NwUISPK::ProcessActionEvent(int nEventId)
{

}
//--------------------------------------------------------------------
void NwUISPK::OnBtnCard(int nCardIndex)
{
    //寻找空的指令槽
    eTouchButton theEmptyTouch = FindEmptyTouchBtn();
    if (theEmptyTouch == TouchBtn_Max)
    {
        return;
    }
    //
    m_eLeftSelectedCmd[theEmptyTouch] = (eCmdButton)nCardIndex;
    RefreshTouchBtn();
    CheckPlayerOptionFinished();
}
//--------------------------------------------------------------------
void NwUISPK::OnBtnTouch(int nIndex)
{
    if (m_eLeftSelectedCmd[nIndex] == CmdBtn_Max)
    {
        return;
    }
    //
    m_eLeftSelectedCmd[nIndex] = CmdBtn_Max;
    RefreshTouchBtn();
}
//--------------------------------------------------------------------
eTouchButton NwUISPK::FindEmptyTouchBtn()
{
    eTouchButton theR = TouchBtn_Max;
    for (int i = 0; i < TouchBtn_Max; ++i)
    {
        if (m_eLeftSelectedCmd[i] == CmdBtn_Max)
        {
            theR = (eTouchButton)i;
            break;
        }
    }
    return theR;
}
//--------------------------------------------------------------------
void NwUISPK::CheckPlayerOptionFinished()
{
    if (FindEmptyTouchBtn() == TouchBtn_Max)
    {
        //没有空的指令槽了，玩家操作结束
        SetAllButtonEnableFlag(false);
        m_pSPKProcedure->PlayerOptionFinished();
    }
}
//--------------------------------------------------------------------
void NwUISPK::SetAllButtonEnableFlag(bool bEnable)
{
    for (int i = 0; i < CmdBtn_Max; ++i)
    {
        m_pCardBtnList[i]->SetInputEnable(bEnable);
    }
    for (int i = 0; i < TouchBtn_Max; ++i)
    {
        m_pLeftTouchBtnList[i]->SetInputEnable(bEnable);
        m_pRightTouchBtnList[i]->SetInputEnable(bEnable);
    }
}
//--------------------------------------------------------------------
void NwUISPK::CreateWindows()
{
    GGUIFullRect kFullRect;
    kFullRect.fDeltaX = 0.0f;
    kFullRect.fDeltaY = 0.0f;
    kFullRect.fDeltaW = GGUIFunc_GetResolutionWidth();
    kFullRect.fDeltaH = GGUIFunc_GetResolutionHeight();
    SetFullRect(kFullRect);
    SetInputEnable(true);
    SetDragEnable(false); //本Panel是全屏窗口，不能拖拽。
    SetSpaceType(GGUIPanelSpace_1);

    GGUIWindowButton* pUIButton = NULL;

    kFullRect.fDeltaX = 100.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Up]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Up] = pUIButton;

    kFullRect.fDeltaX = 250.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Middle]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Middle] = pUIButton;

    kFullRect.fDeltaX = 400.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Down]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Down] = pUIButton;

    kFullRect.fDeltaX = 550.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Defend]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Defend] = pUIButton;


    kFullRect.fDeltaX = 100.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Dodge]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Dodge] = pUIButton;

    kFullRect.fDeltaX = 250.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Insight]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Insight] = pUIButton;

    kFullRect.fDeltaX = 400.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Swoosh]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Swoosh] = pUIButton;

    kFullRect.fDeltaX = 550.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[CmdBtn_Revenge]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pCardBtnList[CmdBtn_Revenge] = pUIButton;

    //---------------------------------------------------
    kFullRect.fDeltaX = 320.0f;
    kFullRect.fDeltaY = 50.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage("uitexture/mm4:hud_30");
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pLeftTouchBtnList[TouchBtn_0] = pUIButton;

    kFullRect.fDeltaX = 320.0f;
    kFullRect.fDeltaY = 110.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage("uitexture/mm4:hud_30");
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pLeftTouchBtnList[TouchBtn_1] = pUIButton;

    kFullRect.fDeltaX = 320.0f;
    kFullRect.fDeltaY = 170.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage("uitexture/mm4:hud_30");
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pLeftTouchBtnList[TouchBtn_2] = pUIButton;

    //---------------------------------------------------
    kFullRect.fDeltaX = 500.0f;
    kFullRect.fDeltaY = 50.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage("uitexture/mm4:hud_30");
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pRightTouchBtnList[TouchBtn_0] = pUIButton;

    kFullRect.fDeltaX = 500.0f;
    kFullRect.fDeltaY = 110.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage("uitexture/mm4:hud_30");
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pRightTouchBtnList[TouchBtn_1] = pUIButton;

    kFullRect.fDeltaX = 500.0f;
    kFullRect.fDeltaY = 170.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage("uitexture/mm4:hud_30");
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pRightTouchBtnList[TouchBtn_2] = pUIButton;


    //---------------------------------------------------
    GGUIWindowProcessBar* pProcessBar = NULL;

    kFullRect.fDeltaX = 20.0f;
    kFullRect.fDeltaY = 30.0f;
    kFullRect.fDeltaW = 260.0f;
    kFullRect.fDeltaH = 30.0f;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pLeftBlood = pProcessBar;
    m_pLeftBlood->SetProcessValue(0.3f);

    kFullRect.fDeltaX = 690.0f;
    kFullRect.fDeltaY = 30.0f;
    kFullRect.fDeltaW = 260.0f;
    kFullRect.fDeltaH = 30.0f;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pRightBlood = pProcessBar;
    m_pRightBlood->SetProcessValue(0.3f);

    kFullRect.fDeltaX = 20.0f;
    kFullRect.fDeltaY = 70.0f;
    kFullRect.fDeltaW = 260.0f;
    kFullRect.fDeltaH = 30.0f;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pLeftEnergy = pProcessBar;
    m_pLeftEnergy->SetProcessValue(0.3f);

    kFullRect.fDeltaX = 690.0f;
    kFullRect.fDeltaY = 70.0f;
    kFullRect.fDeltaW = 260.0f;
    kFullRect.fDeltaH = 30.0f;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pRightEnergy = pProcessBar;
    m_pRightEnergy->SetProcessValue(0.3f);


    GGUIWindowImage* pImage = NULL;

    kFullRect.fDeltaX = 300.0f;
    kFullRect.fDeltaY = 230.0f;
    kFullRect.fDeltaW = 130.0f;
    kFullRect.fDeltaH = 95.0f;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage("uitexture/mm5:hero_1");
    pImage->SetInputEnable(true);
    pImage->SetDragEnable(true);
    pImage->SetSwapX(true);
    AddChild(pImage);
    m_pHeroLeft = pImage;

    kFullRect.fDeltaX = 480.0f;
    kFullRect.fDeltaY = 220.0f;
    kFullRect.fDeltaW = 93.0f;
    kFullRect.fDeltaH = 125.0f;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage("uitexture/mm5:hero_2");
    pImage->SetInputEnable(true);
    pImage->SetDragEnable(true);
    AddChild(pImage);
    m_pHeroRight = pImage;
}
//--------------------------------------------------------------------
void NwUISPK::RefreshLeftByHeroData(const SPKHeroData* pHeroData)
{
    RefreshLeftBlood(pHeroData->nMaxHP, pHeroData->nCurHP);
    RefreshLeftEnergy(pHeroData->nMaxEnergy, pHeroData->nCurEnergy);
    //
    for (int i = 0; i < TouchBtn_Max; ++i)
    {
        m_eLeftSelectedCmd[i] = CmdBtn_Max;
    }
    RefreshTouchBtn();
    //
    memcpy(&m_kTempHeroData, pHeroData, sizeof(m_kTempHeroData));
    RefreshCmdBtn(pHeroData);
    //
    SetAllButtonEnableFlag(true);
}
//--------------------------------------------------------------------
void NwUISPK::RefreshRightByHeroData(const SPKHeroData* pHeroData)
{
    RefreshRightBlood(pHeroData->nMaxHP, pHeroData->nCurHP);
    RefreshRightEnergy(pHeroData->nMaxEnergy, pHeroData->nCurEnergy);
    //
    for (int i = 0; i < TouchBtn_Max; ++i)
    {
        m_pRightTouchBtnList[i]->SetImage("uitexture/mm4:hud_30");
    }
}
//--------------------------------------------------------------------
void NwUISPK::RefreshLeftBlood(int nMax, int nCur)
{
    float fRate = (float)nCur / (float)nMax;
    m_pLeftBlood->SetProcessValue(fRate);
}
//--------------------------------------------------------------------
void NwUISPK::RefreshRightBlood(int nMax, int nCur)
{
    float fRate = (float)nCur / (float)nMax;
    m_pRightBlood->SetProcessValue(fRate);
}
//--------------------------------------------------------------------
void NwUISPK::RefreshLeftEnergy(int nMax, int nCur)
{
    float fRate = (float)nCur / (float)nMax;
    m_pLeftEnergy->SetProcessValue(fRate);
}
//--------------------------------------------------------------------
void NwUISPK::RefreshRightEnergy(int nMax, int nCur)
{
    float fRate = (float)nCur / (float)nMax;
    m_pRightEnergy->SetProcessValue(fRate);
}
//--------------------------------------------------------------------
void NwUISPK::RefreshCmdBtn(const SPKHeroData* pHeroData)
{
    //do nothing
}
//--------------------------------------------------------------------
void NwUISPK::RefreshTouchBtn()
{
    for (int i = 0; i < TouchBtn_Max; ++i)
    {
        if (m_eLeftSelectedCmd[i] == CmdBtn_Max)
        {
            m_pLeftTouchBtnList[i]->SetImage("uitexture/mm4:hud_30");
        }
        else
        {
            m_pLeftTouchBtnList[i]->SetImage(g_CmdBtnTexture[m_eLeftSelectedCmd[i]]);
        }
    }
}
//--------------------------------------------------------------------
eCmdButton NwUISPK::GetLeftSelectedCmd(eTouchButton theTouchIndex)
{
    if (theTouchIndex >= 0 && theTouchIndex < TouchBtn_Max)
    {
        return m_eLeftSelectedCmd[theTouchIndex];
    }
    else
    {
        return CmdBtn_Max;
    }
}
//--------------------------------------------------------------------
void NwUISPK::SetRightSelectedCmd(int theTouchIndex, eCmdButton theCmd)
{
    if (theTouchIndex >= 0 && theTouchIndex < TouchBtn_Max)
    {
        if (theCmd == CmdBtn_Max)
        {
            m_pRightTouchBtnList[theTouchIndex]->SetImage("uitexture/mm4:hud_30");
        }
        else
        {
            m_pRightTouchBtnList[theTouchIndex]->SetImage(g_CmdBtnTexture[theCmd]);
        }
    }
}
//--------------------------------------------------------------------
void NwUISPK::PlayAnim_LeftUnit(int theAnim)
{
    //do nothing
}
//--------------------------------------------------------------------
void NwUISPK::PlayAnim_RightUnit(int theAnim)
{
    //do nothing
}
//--------------------------------------------------------------------
void NwUISPK::PlayCmdName_LeftUnit(const char* szCmdName)
{
    //do nothing
}
//--------------------------------------------------------------------
void NwUISPK::PlayCmdName_RightUnit(const char* szCmdName)
{
    //do nothing
}
//--------------------------------------------------------------------
void NwUISPK::PlayDamageString_LeftUnit(int nNumber)
{
    //do nothing
}
//--------------------------------------------------------------------
void NwUISPK::PlayDamageString_RightUnit(int nNumber)
{
    //do nothing
}
//----------------------------------------------------------------


