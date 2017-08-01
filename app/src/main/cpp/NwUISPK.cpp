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
const char* g_CmdBtnEmptyTex = "uitexture/mm4:hud_30";
const char* g_HeroTexture1 = "uitexture/mm5:hero_1";
const char* g_HeroTexture2 = "uitexture/mm5:hero_2";
const char* g_XuanYunTexture = "uitexture/mm4:hud_35";
const char* g_LoseTexture = "uitexture/mm7:Name1";
const char* g_WinTexture = "uitexture/mm8:Name1";
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
        m_pImgXuanYunList[i] = NULL;
    }
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        m_kOwnCmdCount[i] = 0;
    }
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        m_kSelectedCmdList[i] = NwSPKCmd_Max;
    }
    m_pImgSPKResult = NULL;
    m_bXuanYun = false;
    m_bShowPKResult = false;
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
void NwUISPK::PrepareForStart(const SPKHeroData* pSPKData)
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
    for (int i = 0; i < SideMax; ++i)
    {
        m_pImgXuanYunList[i]->SetVisible(false);
    }
    m_pImgSPKResult->SetVisible(false);
    m_bShowPKResult = false;
    m_bXuanYun = false;

    SetAllButtonEnableFlag(true);
    RefreshCmdBtn();
    RefreshTouchBtn();
}
//----------------------------------------------------------------
void NwUISPK::StartSelectCmd(const SPKHeroData* pSPKData)
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
    m_bXuanYun = pSPKData->bDizzy;
    if (m_bXuanYun)
    {
        //当前处于眩晕中，第一个指令无效，随便填一个值。
        m_kSelectedCmdList[0] = NwSPKCmd_ZhaoJia;
        //眩晕中不能施放旋风斩。
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
void NwUISPK::SetXuanYun(eSideType theSide, bool bXuanYun)
{
    m_pImgXuanYunList[theSide]->SetVisible(bXuanYun);
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
const GGUIRect& NwUISPK::GetHeroRect(eSideType theSide)
{
    return m_pHeroList[theSide]->GetRectInAbsCoord();
}
//----------------------------------------------------------------
void NwUISPK::PlayTouchBtnEffect(NwSPKTouchType theTouchIndex)
{
    GGUIActionGroup* theActionGroup = m_pBtnTouchList[SideLeft][theTouchIndex]->CreateActionGroup();
    theActionGroup->SetActionEventHandler(this);

    GGUIActionLine* pActionLine = (GGUIActionLine*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Line);;
    theActionGroup->AddActionLine(pActionLine);

    GGUIActionMove* pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(30.0f, 00.0f, 0.2f);
    pActionLine->AddAction(pActionMove);

    pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(-30.0f, 00.0f, 0.5f);
    pActionLine->AddAction(pActionMove);

    //===========================
    theActionGroup = m_pBtnTouchList[SideRight][theTouchIndex]->CreateActionGroup();
    theActionGroup->SetActionEventHandler(this);

    pActionLine = (GGUIActionLine*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Line);;
    theActionGroup->AddActionLine(pActionLine);

    pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(-30.0f, 00.0f, 0.2f);
    pActionLine->AddAction(pActionMove);

    pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(30.0f, 00.0f, 0.5f);
    pActionLine->AddAction(pActionMove);
}
//----------------------------------------------------------------
void NwUISPK::ShowPKResult(bool bWin)
{
    m_pImgSPKResult->SetVisible(true);
    m_pImgSPKResult->SetImage(bWin ? g_WinTexture : g_LoseTexture);
    m_bShowPKResult = true;
}
//----------------------------------------------------------------
bool NwUISPK::InputWindow(GGUIInputMsg* pInputMsg)
{
    if (GGUIWindowPanel::InputWindow(pInputMsg) == true)
    {
        //父类已经处理了input，派生类不要再处理。
        return true;
    }

    if (m_bShowPKResult)
    {
        if (pInputMsg->theType == GGUIInputMsg_TouchUp)
        {
            pInputMsg->bSwallowed = true;
            m_bShowPKResult = false;
            NwSceneSPK::Get()->StartSPK();
            return true;
        }
    }

    return false;
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
    if (nCmdIndex == NwSPKCmd_XuanFeng)
    {
        for (int i = 0; i < NwSPKTouch_Max; ++i)
        {
            m_kSelectedCmdList[i] = NwSPKCmd_XuanFeng;
        }
    }
    else
    {
        //寻找空的指令槽
        NwSPKTouchType theEmptyTouch = FindEmptyTouchBtn();
        if (theEmptyTouch != NwSPKTouch_Max)
        {
            m_kSelectedCmdList[theEmptyTouch] = (NwSPKCmdType)nCmdIndex;
        }
    }
    //
    --(m_kOwnCmdCount[nCmdIndex]);
    RefreshCmdBtn();
    RefreshTouchBtn();
    CheckPlayerOptionFinished();
}
//--------------------------------------------------------------------
void NwUISPK::OnBtnTouch(int nTouchIndex)
{
    if (m_bXuanYun && nTouchIndex == 0)
    {
        return;
    }
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
            m_pBtnCmdList[i]->SetText(SoStrFmt("     %d", m_kOwnCmdCount[i]));
        }
        else
        {
            m_pBtnCmdList[i]->SetButtonState(GGUIButtonState_Disable);
            m_pBtnCmdList[i]->SetText("     0");
        }

        if (m_bXuanYun && i == NwSPKCmd_XuanFeng)
        {
            //眩晕中不能施放旋风斩。
            m_pBtnCmdList[i]->SetButtonState(GGUIButtonState_Disable);
        }
    }
}
//--------------------------------------------------------------------
void NwUISPK::RefreshTouchBtn()
{
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        if (m_bXuanYun && i == 0)
        {
            m_pBtnTouchList[SideLeft][i]->SetImage(g_XuanYunTexture);
        }
        else
        {
            NwSPKCmdType theCmd = m_kSelectedCmdList[i];
            if (theCmd == NwSPKCmd_Max)
            {
                m_pBtnTouchList[SideLeft][i]->SetImage(g_CmdBtnEmptyTex);
            }
            else
            {
                m_pBtnTouchList[SideLeft][i]->SetImage(g_CmdBtnTexture[theCmd]);
            }
        }
        //
        m_pBtnTouchList[SideRight][i]->SetImage(g_CmdBtnEmptyTex);
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
        m_pBtnCmdList[i]->SetButtonState(bEnable ? GGUIButtonState_Normal : GGUIButtonState_Disable);
    }
    for (int j = 0; j < NwSPKTouch_Max; ++j)
    {
        m_pBtnTouchList[SideLeft][j]->SetInputEnable(bEnable);
        m_pBtnTouchList[SideRight][j]->SetInputEnable(false);
    }
}
//--------------------------------------------------------------------
void NwUISPK::CreateWindows()
{
    float fStandardWidth = 960.0f;
    float fStandardHeight = 540.0f;
    SetStandardWidthHeight(fStandardWidth, fStandardHeight);
    SetInputEnable(true);
    SetDragEnable(false); //本Panel是全屏窗口，不能拖拽。
    SetSpaceType(GGUIPanelSpace_Normal);

    GGUIWindowButton* pUIButton = NULL;
    GGUIFullRect kFullRect;

    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Center;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Bottom;
    kFullRect.fScaleX = 100.0f / fStandardWidth;
    kFullRect.fScaleY = 400.0f / fStandardHeight;
    kFullRect.fScaleW = 126.0f / fStandardWidth;
    kFullRect.fScaleH = 50.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_Up]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Up] = pUIButton;

    kFullRect.fScaleX = 250.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_Middle]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Middle] = pUIButton;

    kFullRect.fScaleX = 400.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_Down]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Down] = pUIButton;

    kFullRect.fScaleX = 550.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_ZhaoJia]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_ZhaoJia] = pUIButton;


    kFullRect.fScaleX = 100.0f / fStandardWidth;
    kFullRect.fScaleY = 470.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_ShanBi]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_ShanBi] = pUIButton;

    kFullRect.fScaleX = 250.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_DongCha]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_DongCha] = pUIButton;

    kFullRect.fScaleX = 400.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_XuanFeng]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_XuanFeng] = pUIButton;

    kFullRect.fScaleX = 550.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnTexture[NwSPKCmd_FanSha]);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_FanSha] = pUIButton;

    //---------------------------------------------------
    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Center;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Top;
    kFullRect.fScaleX = 320.0f / fStandardWidth;
    kFullRect.fScaleY = 50.0f / fStandardHeight;
    kFullRect.fScaleW = 126.0f / fStandardWidth;
    kFullRect.fScaleH = 50.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnTouchList[SideLeft][NwSPKTouch_0] = pUIButton;

    kFullRect.fScaleY = 110.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnTouchList[SideLeft][NwSPKTouch_1] = pUIButton;

    kFullRect.fScaleY = 170.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnTouchList[SideLeft][NwSPKTouch_2] = pUIButton;

    //---------------------------------------------------
    kFullRect.fScaleX = 500.0f / fStandardWidth;
    kFullRect.fScaleY = 50.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnTouchList[SideRight][NwSPKTouch_0] = pUIButton;

    kFullRect.fScaleY = 110.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnTouchList[SideRight][NwSPKTouch_1] = pUIButton;

    kFullRect.fScaleY = 170.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(true);
    AddChild(pUIButton);
    m_pBtnTouchList[SideRight][NwSPKTouch_2] = pUIButton;


    //---------------------------------------------------
    GGUIWindowProcessBar* pProcessBar = NULL;

    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Left;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Top;
    kFullRect.fScaleX = 20.0f / fStandardWidth;
    kFullRect.fScaleY = 30.0f / fStandardHeight;
    kFullRect.fScaleW = 260.0f / fStandardWidth;
    kFullRect.fScaleH = 30.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pHPList[SideLeft] = pProcessBar;

    kFullRect.fScaleY = 70.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pMPList[SideLeft] = pProcessBar;

    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Right;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Top;
    kFullRect.fScaleX = 690.0f / fStandardWidth;
    kFullRect.fScaleY = 30.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pHPList[SideRight] = pProcessBar;

    kFullRect.fScaleY = 70.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(true);
    AddChild(pProcessBar);
    m_pMPList[SideRight] = pProcessBar;


    GGUIWindowImage* pImage = NULL;

    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Center;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Center;
    kFullRect.fScaleX = 300.0f / fStandardWidth;
    kFullRect.fScaleY = 230.0f / fStandardHeight;
    kFullRect.fScaleW = 130.0f / fStandardWidth;
    kFullRect.fScaleH = 95.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_HeroTexture1);
    pImage->SetInputEnable(true);
    pImage->SetDragEnable(true);
    pImage->SetSwapX(true);
    AddChild(pImage);
    m_pHeroList[SideLeft] = pImage;

    kFullRect.fScaleX = 480.0f / fStandardWidth;
    kFullRect.fScaleY = 220.0f / fStandardHeight;
    kFullRect.fScaleW = 93.0f / fStandardWidth;
    kFullRect.fScaleH = 125.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_HeroTexture2);
    pImage->SetInputEnable(true);
    pImage->SetDragEnable(true);
    AddChild(pImage);
    m_pHeroList[SideRight] = pImage;


    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Center;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Center;
    kFullRect.fScaleX = 240.0f / fStandardWidth;
    kFullRect.fScaleY = 230.0f / fStandardHeight;
    kFullRect.fScaleW = 56.0f / fStandardWidth;
    kFullRect.fScaleH = 32.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_XuanYunTexture);
    pImage->SetInputEnable(false);
    AddChild(pImage);
    m_pImgXuanYunList[SideLeft] = pImage;

    kFullRect.fScaleX = 630.0f / fStandardWidth;
    kFullRect.fScaleY = 220.0f / fStandardHeight;
    kFullRect.fScaleW = 56.0f / fStandardWidth;
    kFullRect.fScaleH = 32.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_XuanYunTexture);
    pImage->SetInputEnable(false);
    AddChild(pImage);
    m_pImgXuanYunList[SideRight] = pImage;

    kFullRect.fScaleX = 200.0f / fStandardWidth;
    kFullRect.fScaleY = 20.0f / fStandardHeight;
    kFullRect.fScaleW = 512.0f / fStandardWidth;
    kFullRect.fScaleH = 512.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_WinTexture);
    pImage->SetInputEnable(false);
    AddChild(pImage);
    m_pImgSPKResult = pImage;

}
//----------------------------------------------------------------

