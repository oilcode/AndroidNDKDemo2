//----------------------------------------------------------------
#include "NwUISPK.h"
#include "NwSceneSPK.h"
#include "NwSPKProcedure.h"
#include "NwActorData.h"
//----------------------------------------------------------------
const char* g_CmdBtnTexture[NwSPKCmd_Max] =
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
NwUISPK::NwUISPK()
{
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        m_pBtnCmdList[i] = NULL;
    }
    for (int i = 0; i < SideMax; ++i)
    {
        for (int j = 0; j < NwSPKTouch_Max; ++j)
        {
            m_pBtnTouchList[i][j] = NULL;
        }
        m_pHPList[i] = NULL;
        m_pMPList[i] = NULL;
        m_pHeroList[i] = NULL;
    }
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        m_kOwnCmdCount[i] = 0;
    }
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        m_kSelectedCmdList[i] = NwSPKCmd_Max;
    }
}
//----------------------------------------------------------------
NwUISPK::~NwUISPK()
{
    
}
//----------------------------------------------------------------
bool NwUISPK::InitUISPK()
{
    CreateWindows();
    return true;
}
//----------------------------------------------------------------
void NwUISPK::ClearUISPK()
{
    GGUIWindowPanel::ClearWindow();
}
//----------------------------------------------------------------
void NwUISPK::StartSelectCmd(const NwActorSPKData* pSPKData)
{
    m_kOwnCmdCount[NwSPKCmd_Up] = pSPKData->nCmdUpCount;
    m_kOwnCmdCount[NwSPKCmd_Middle] = pSPKData->nCmdMiddleCount;
    m_kOwnCmdCount[NwSPKCmd_Down] = pSPKData->nCmdDownCount;
    m_kOwnCmdCount[NwSPKCmd_ZhaoJia] = pSPKData->nCmdZhaoJiaCount;
    m_kOwnCmdCount[NwSPKCmd_ShanBi] = pSPKData->nCmdShanBiCount + pSPKData->nShanBiCountInBag;
    m_kOwnCmdCount[NwSPKCmd_DongCha] = pSPKData->nCmdDongChaCount + pSPKData->nDongChaCountInBag;
    m_kOwnCmdCount[NwSPKCmd_XuanFeng] = pSPKData->nCmdXuanFengCount + pSPKData->nXuanFengCountInBag;
    m_kOwnCmdCount[NwSPKCmd_FanSha] = pSPKData->nCmdFanShaCount + pSPKData->nFanShaCountInBag;
    
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        m_kSelectedCmdList[i] = NwSPKCmd_Max;
    }

    SetAllButtonEnableFlag(true);
    RefreshCmdBtn();
    RefreshTouchBtn();
}
//----------------------------------------------------------------
void NwUISPK::StartSelectCmd2(const SPKHeroData* pSPKData)
{
    m_kOwnCmdCount[NwSPKCmd_Up] = pSPKData->nCmdUp;
    m_kOwnCmdCount[NwSPKCmd_Middle] = pSPKData->nCmdMiddle;
    m_kOwnCmdCount[NwSPKCmd_Down] = pSPKData->nCmdDown;
    m_kOwnCmdCount[NwSPKCmd_ZhaoJia] = pSPKData->nCmdDefend;
    m_kOwnCmdCount[NwSPKCmd_ShanBi] = pSPKData->nCmdDodge + pSPKData->nDodgeCountInBag;
    m_kOwnCmdCount[NwSPKCmd_DongCha] = pSPKData->nCmdInsight + pSPKData->nInsightCountInBag;
    m_kOwnCmdCount[NwSPKCmd_XuanFeng] = pSPKData->nCmdSwoosh + pSPKData->nSwooshCountInBag;
    m_kOwnCmdCount[NwSPKCmd_FanSha] = pSPKData->nCmdRevenge + pSPKData->nRevengeCountInBag;
    
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        m_kSelectedCmdList[i] = NwSPKCmd_Max;
    }

    SetAllButtonEnableFlag(true);
    RefreshCmdBtn();
    RefreshTouchBtn();
}
//----------------------------------------------------------------
void NwUISPK::SetHP(eSideType theSide, int nMax, int nCur)
{
    float fValue = (float)nCur / (float)nMax;
    m_pHPList[theSide]->SetProcessValue(fValue);
}
//----------------------------------------------------------------
void NwUISPK::SetMP(eSideType theSide, int nMax, int nCur)
{
    float fValue = (float)nCur / (float)nMax;
    m_pMPList[theSide]->SetProcessValue(fValue);
}
//----------------------------------------------------------------
void NwUISPK::SetRightSelectedCmd(NwSPKTouchType theTouchIndex, NwSPKCmdType theCmd)
{
    m_pBtnTouchList[SideRight][theTouchIndex]->SetImage(g_CmdBtnTexture[theCmd]);
}
//----------------------------------------------------------------
NwSPKCmdType NwUISPK::GetSelectedCmd(NwSPKTouchType theTouchIndex)
{
    return m_kSelectedCmdList[theTouchIndex];
}
//----------------------------------------------------------------
void NwUISPK::ProcessUIEvent(int nEventType, void* pParam)
{
    if (nEventType == GGUIEvent_Button_Clicked)
    {
        bool bFind = false;
        const GGUIEventParam_Button_Clicked* pClickParam = (GGUIEventParam_Button_Clicked*)pParam;

        if (bFind == false)
        {
            for (int i = 0; i < NwSPKCmd_Max; ++i)
            {
                if (m_pBtnCmdList[i]->GetID() == pClickParam->nWindowID)
                {
                    OnBtnCmd(i);
                    bFind = true;
                    break;
                }
            }
        }

        if (bFind == false)
        {
            for (int i = 0; i < NwSPKTouch_Max; ++i)
            {
                if (m_pBtnTouchList[SideLeft][i]->GetID() == pClickParam->nWindowID)
                {
                    OnBtnTouch(i);
                    bFind = true;
                    break;
                }
            }
        }
    }
}
//--------------------------------------------------------------------
void NwUISPK::OnBtnCmd(int nCmdIndex)
{
    //寻找空的指令槽
    NwSPKTouchType theEmptyTouch = FindEmptyTouchBtn();
    if (theEmptyTouch == NwSPKTouch_Max)
    {
        return;
    }
    //
    m_kSelectedCmdList[theEmptyTouch] = (NwSPKCmdType)nCmdIndex;
    --(m_kOwnCmdCount[nCmdIndex]);
    RefreshCmdBtn();
    RefreshTouchBtn();
    CheckPlayerOptionFinished();
}
//--------------------------------------------------------------------
void NwUISPK::OnBtnTouch(int nTouchIndex)
{
    NwSPKCmdType oldCmd = m_kSelectedCmdList[nTouchIndex];
    if (oldCmd == NwSPKCmd_Max)
    {
        return;
    }
    //
    m_kSelectedCmdList[nTouchIndex] = NwSPKCmd_Max;
    ++(m_kOwnCmdCount[oldCmd]);
    RefreshCmdBtn();
    RefreshTouchBtn();
}
//--------------------------------------------------------------------
void NwUISPK::RefreshCmdBtn()
{
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        if (m_kOwnCmdCount[i] > 0)
        {
            m_pBtnCmdList[i]->SetButtonState(GGUIButtonState_Normal);
            m_pBtnCmdList[i]->SetText(SoStrFmt("%d", m_kOwnCmdCount[i]));
        }
        else
        {
            m_pBtnCmdList[i]->SetButtonState(GGUIButtonState_Disable);
            m_pBtnCmdList[i]->SetText("");
        }
    }
}
//--------------------------------------------------------------------
void NwUISPK::RefreshTouchBtn()
{
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        NwSPKCmdType theCmd = m_kSelectedCmdList[i];
        if (theCmd == NwSPKCmd_Max)
        {
            m_pBtnTouchList[SideLeft][i]->SetImage("uitexture/mm4:hud_30");
        }
        else
        {
            m_pBtnTouchList[SideLeft][i]->SetImage(g_CmdBtnTexture[theCmd]);
        }
        //
        m_pBtnTouchList[SideRight][i]->SetImage("uitexture/mm4:hud_30");
    }
}
//--------------------------------------------------------------------
NwSPKTouchType NwUISPK::FindEmptyTouchBtn()
{
    NwSPKTouchType theR = NwSPKTouch_Max;
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        if (m_kSelectedCmdList[i] == NwSPKCmd_Max)
        {
            theR = (NwSPKTouchType)i;
            break;
        }
    }
    return theR;
}
//--------------------------------------------------------------------
void NwUISPK::CheckPlayerOptionFinished()
{
    if (FindEmptyTouchBtn() == NwSPKTouch_Max)
    {
        //没有空的指令槽了，玩家操作结束
        SetAllButtonEnableFlag(false);
        NwSceneSPK::Get()->GetSPKProcedure()->PlayerOptionFinished();
    }
}
//--------------------------------------------------------------------
void NwUISPK::SetAllButtonEnableFlag(bool bEnable)
{
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        m_pBtnCmdList[i]->SetInputEnable(bEnable);
    }
    for (int i = 0; i < SideMax; ++i)
    {
        for (int j = 0; j < NwSPKTouch_Max; ++j)
        {
            m_pBtnTouchList[i][j]->SetInputEnable(bEnable);
        }
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
    SetSpaceType(GGUIPanelSpace_Normal);

    GGUIWindowButton* pUIButton = NULL;

    kFullRect.fDeltaX = 100.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_Up]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Up] = pUIButton;

    kFullRect.fDeltaX = 250.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_Middle]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Middle] = pUIButton;

    kFullRect.fDeltaX = 400.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_Down]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Down] = pUIButton;

    kFullRect.fDeltaX = 550.0f;
    kFullRect.fDeltaY = 400.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_ZhaoJia]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_ZhaoJia] = pUIButton;


    kFullRect.fDeltaX = 100.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_ShanBi]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_ShanBi] = pUIButton;

    kFullRect.fDeltaX = 250.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_DongCha]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_DongCha] = pUIButton;

    kFullRect.fDeltaX = 400.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_XuanFeng]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_XuanFeng] = pUIButton;

    kFullRect.fDeltaX = 550.0f;
    kFullRect.fDeltaY = 470.0f;
    kFullRect.fDeltaW = 126.0f;
    kFullRect.fDeltaH = 50.0f;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_FanSha]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_FanSha] = pUIButton;

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
    m_pBtnTouchList[SideLeft][NwSPKTouch_0] = pUIButton;

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
    m_pBtnTouchList[SideLeft][NwSPKTouch_1] = pUIButton;

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
    m_pBtnTouchList[SideLeft][NwSPKTouch_2] = pUIButton;

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
    m_pBtnTouchList[SideRight][NwSPKTouch_0] = pUIButton;

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
    m_pBtnTouchList[SideRight][NwSPKTouch_1] = pUIButton;

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
    m_pBtnTouchList[SideRight][NwSPKTouch_2] = pUIButton;


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
    m_pHPList[SideLeft] = pProcessBar;

    kFullRect.fDeltaX = 690.0f;
    kFullRect.fDeltaY = 30.0f;
    kFullRect.fDeltaW = 260.0f;
    kFullRect.fDeltaH = 30.0f;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pHPList[SideRight] = pProcessBar;

    kFullRect.fDeltaX = 20.0f;
    kFullRect.fDeltaY = 70.0f;
    kFullRect.fDeltaW = 260.0f;
    kFullRect.fDeltaH = 30.0f;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pMPList[SideLeft] = pProcessBar;

    kFullRect.fDeltaX = 690.0f;
    kFullRect.fDeltaY = 70.0f;
    kFullRect.fDeltaW = 260.0f;
    kFullRect.fDeltaH = 30.0f;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pMPList[SideRight] = pProcessBar;


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
    m_pHeroList[SideLeft] = pImage;

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
    m_pHeroList[SideRight] = pImage;
}
//----------------------------------------------------------------

