//----------------------------------------------------------------
#include "NwUISPK.h"
#include "NwSceneSPK.h"
#include "NwSPKProcedure.h"
#include "NwSPKData.h"
#include "SoAudio.h"
//----------------------------------------------------------------
const char* g_CmdBtnTexture[NwSPKCmd_Max] = {0};
const char* g_CmdName[NwSPKCmd_Max] = {0};
const char* g_CmdBtnEmptyTex = "mm1:hud_30";
const char* g_HeroTexture1 = "mm1:soldier011";
const char* g_HeroTexture2 = "mm1:soldier012";
const char* g_BuffXuanYunTexture = "mm1:state_01";
const char* g_BuffXuanYunName = "眩晕";
const char* g_LoseTexture = "mm7:Name1";
const char* g_WinTexture = "mm8:Name1";
//----------------------------------------------------------------
NwUISPK::NwUISPK()
{
    g_CmdBtnTexture[NwSPKCmd_Up] = "mm1:hud_31";
    g_CmdBtnTexture[NwSPKCmd_Middle] = "mm1:hud_32";
    g_CmdBtnTexture[NwSPKCmd_Down] = "mm1:hud_33";
    g_CmdBtnTexture[NwSPKCmd_ZhaoJia] = "mm1:hud_34";
    g_CmdBtnTexture[NwSPKCmd_ShanBi] = "mm1:hud_35";
    g_CmdBtnTexture[NwSPKCmd_DongCha] = "mm1:hud_36";
    g_CmdBtnTexture[NwSPKCmd_XuanFeng] = "mm1:hud_37";
    g_CmdBtnTexture[NwSPKCmd_FanSha] = "mm1:hud_38";
    //
    g_CmdName[NwSPKCmd_Up] = "上劈";
    g_CmdName[NwSPKCmd_Middle] = "中砍";
    g_CmdName[NwSPKCmd_Down] = "下刺";
    g_CmdName[NwSPKCmd_ZhaoJia] = "招架";
    g_CmdName[NwSPKCmd_ShanBi] = "闪避";
    g_CmdName[NwSPKCmd_DongCha] = "洞察";
    g_CmdName[NwSPKCmd_XuanFeng] = "旋风斩";
    g_CmdName[NwSPKCmd_FanSha] = "反杀";
    //
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        m_pBtnCmdList[i] = NULL;
    }
    for (int i = 0; i < NwSPKSide_Max; ++i)
    {
        for (int j = 0; j < NwSPKTouch_Max; ++j)
        {
            m_pBtnTouchList[i][j] = NULL;
        }
        m_pHPList[i] = NULL;
        m_pMPList[i] = NULL;
        m_pHPText[i] = NULL;
        m_pMPText[i] = NULL;
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
    m_bDongCha = false;
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
void NwUISPK::PrepareForStart()
{
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        m_kOwnCmdCount[i] = 0;
    }
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        m_kSelectedCmdList[i] = NwSPKCmd_Max;
    }
    for (int i = 0; i < NwSPKSide_Max; ++i)
    {
        m_pImgXuanYunList[i]->SetVisible(false);
    }
    m_pImgSPKResult->SetVisible(false);
    m_bShowPKResult = false;
    m_bXuanYun = false;
    m_bDongCha = false;
}
//----------------------------------------------------------------
void NwUISPK::StartSelectCmd()
{
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        m_kSelectedCmdList[i] = NwSPKCmd_Max;
    }
    if (m_bXuanYun)
    {
        //处于眩晕状态，不能选择第一个指令，填成默认值
        m_kSelectedCmdList[0] = NwSPKCmd_ZhaoJia;
    }
    m_bDongCha = false;
    SetAllButtonEnableFlag(true);
    RefreshTouchBtn();
    RefreshCmdBtn();
}
//----------------------------------------------------------------
void NwUISPK::RefreshUIWithHeroData(const NwSPKHeroData* pSPKData, NwSPKSideType theSide)
{
    SetHP(theSide, pSPKData->nMaxHP, pSPKData->nCurHP);
    SetMP(theSide, pSPKData->nMaxMP, pSPKData->nCurMP);

    //目前只刷新眩晕buff
    bool bXuanYun = pSPKData->kBuffList[NwSPKBuff_XuanYun].IsEnable();
    SetXuanYun(theSide, bXuanYun);

    if (theSide == NwSPKSide_Left)
    {
        for (int i = 0; i < NwSPKCmd_Max; ++i)
        {
            m_kOwnCmdCount[i] = pSPKData->kCmdCountList[i];
        }
        m_bXuanYun = bXuanYun;
        RefreshCmdCount();
    }
}
//----------------------------------------------------------------
void NwUISPK::SetHP(NwSPKSideType theSide, int nMax, int nCur)
{
    float fValue = (float)nCur / (float)nMax;
    m_pHPList[theSide]->FlashProcessValue(fValue);
    //
    int nPercent = ceilf(fValue * 100);
    const char* text = SoStrFmt("血量 %d%%", nPercent);
    m_pHPText[theSide]->SetText(text);
}
//----------------------------------------------------------------
void NwUISPK::SetMP(NwSPKSideType theSide, int nMax, int nCur)
{
    float fValue = (float)nCur / (float)nMax;
    m_pMPList[theSide]->FlashProcessValue(fValue);
    //
    int nPercent = ceilf(fValue * 100);
    const char* text = SoStrFmt("看破 %d", nPercent);
    m_pMPText[theSide]->SetText(text);
}
//----------------------------------------------------------------
void NwUISPK::SetXuanYun(NwSPKSideType theSide, bool bXuanYun)
{
    m_pImgXuanYunList[theSide]->SetVisible(bXuanYun);
}
//----------------------------------------------------------------
void NwUISPK::SetRightSelectedCmd(NwSPKTouchType theTouchIndex, NwSPKCmdType theCmd)
{
    m_pBtnTouchList[NwSPKSide_Right][theTouchIndex]->SetText(g_CmdName[theCmd]);
}
//----------------------------------------------------------------
NwSPKCmdType NwUISPK::GetSelectedCmd(NwSPKTouchType theTouchIndex)
{
    return m_kSelectedCmdList[theTouchIndex];
}
//----------------------------------------------------------------
bool NwUISPK::GetSelectedDongCha()
{
    return m_bDongCha;
}
//----------------------------------------------------------------
const GGUIRect& NwUISPK::GetHeroRect(NwSPKSideType theSide)
{
    return m_pHeroList[theSide]->GetRectInAbsCoord();
}
//----------------------------------------------------------------
void NwUISPK::PlayTouchBtnEffect(NwSPKTouchType theTouchIndex)
{
    GGUIActionGroup* theActionGroup = m_pBtnTouchList[NwSPKSide_Left][theTouchIndex]->CreateActionGroup();
    theActionGroup->SetActionEventHandler(this);

    GGUIActionLine* pActionLine = (GGUIActionLine*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Line);;
    theActionGroup->AddActionLine(pActionLine);

    GGUIActionMove* pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(30.0f, 00.0f, 0.2f);
    pActionLine->AddAction(pActionMove);

    GGUIActionAudio* pActionAudio = (GGUIActionAudio*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Audio);
    pActionAudio->InitActionAudio("audio/touch.wav", 1.0f, 0.0f);
    pActionLine->AddAction(pActionAudio);

    pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(-30.0f, 00.0f, 0.4f);
    pActionLine->AddAction(pActionMove);

    //===========================
    theActionGroup = m_pBtnTouchList[NwSPKSide_Right][theTouchIndex]->CreateActionGroup();
    theActionGroup->SetActionEventHandler(this);

    pActionLine = (GGUIActionLine*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Line);;
    theActionGroup->AddActionLine(pActionLine);

    pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(-30.0f, 00.0f, 0.2f);
    pActionLine->AddAction(pActionMove);

    pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(30.0f, 00.0f, 0.4f);
    pActionLine->AddAction(pActionMove);
}
//----------------------------------------------------------------
void NwUISPK::PlayHeroEffect(NwSPKSideType theSide, float fDeltaScale)
{
    GGUIActionGroup* theActionGroup = m_pHeroList[theSide]->CreateActionGroup();
    theActionGroup->SetActionEventHandler(this);

    GGUIActionLine* pActionLine = (GGUIActionLine*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Line);;
    theActionGroup->AddActionLine(pActionLine);

    if (theSide == NwSPKSide_Left)
    {
        GGUIActionAudio* pActionAudio = (GGUIActionAudio*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Audio);
        pActionAudio->InitActionAudio("audio/attack.wav", 1.0f, 0.0f);
        pActionLine->AddAction(pActionAudio);
    }

    GGUIActionScale* pActionScale = (GGUIActionScale*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Scale);
    pActionScale->InitActionScale(fDeltaScale, fDeltaScale, 0.4f);
    pActionLine->AddAction(pActionScale);

    pActionScale = (GGUIActionScale*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Scale);
    pActionScale->InitActionScale(-fDeltaScale, -fDeltaScale, 0.35f);
    pActionLine->AddAction(pActionScale);
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
        if (pInputMsg->theType == GGUIInputMsg_Up)
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
                if (m_pBtnTouchList[NwSPKSide_Left][i]->GetID() == pClickParam->nWindowID)
                {
                    OnBtnTouch(i);
                    bFind = true;
                    break;
                }
            }
        }
    }
    //else if (nEventType == GGUIEvent_ScrollBar_PosChanged)
    //{
        //const GGUIEventParam_ScrollBar_PosChanged* pScrollParam = (GGUIEventParam_ScrollBar_PosChanged*)pParam;
        //SoAudioVolume(0, pScrollParam->fNewValue);
    //}
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
    else if (nCmdIndex == NwSPKCmd_FanSha)
    {
        for (int i = 0; i < NwSPKTouch_Max; ++i)
        {
            m_kSelectedCmdList[i] = NwSPKCmd_FanSha;
        }
    }
    else if (nCmdIndex == NwSPKCmd_DongCha)
    {
        //把对方选择的指令显示在界面上
        const NwSPKSelectedCmd* pSelectedCmd = NwSceneSPK::Get()->GetSPKData()->GetRightSelectedCmd();
        for (int i = 0; i < NwSPKTouch_Max; ++i)
        {
            NwSPKCmdType theCmd = pSelectedCmd->kCmdList[i];
            m_pBtnTouchList[NwSPKSide_Right][i]->SetText(g_CmdName[theCmd]);
        }
        m_bDongCha = true;
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
    SoAudioPlay("audio/button1.wav", 0.2f, false, false);
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
    SoAudioPlay("audio/button2.wav", 1.0f, false, false);
}
//--------------------------------------------------------------------
void NwUISPK::RefreshCmdBtn()
{
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        if (m_kOwnCmdCount[i] > 0)
        {
            m_pBtnCmdList[i]->SetButtonState(GGUIButtonState_Normal);
        }
        else
        {
            m_pBtnCmdList[i]->SetButtonState(GGUIButtonState_Disable);
        }
        const char* text = SoStrFmt("%s%d", g_CmdName[i], m_kOwnCmdCount[i]);
        m_pBtnCmdList[i]->SetText(text);
    }

    if (m_bXuanYun)
    {
        //眩晕中不能施放旋风斩，不能施放洞察，不能施放反杀。
        m_pBtnCmdList[NwSPKCmd_XuanFeng]->SetButtonState(GGUIButtonState_Disable);
        m_pBtnCmdList[NwSPKCmd_DongCha]->SetButtonState(GGUIButtonState_Disable);
        m_pBtnCmdList[NwSPKCmd_FanSha]->SetButtonState(GGUIButtonState_Disable);
    }
}
//--------------------------------------------------------------------
void NwUISPK::RefreshCmdCount()
{
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        const char* text = SoStrFmt("%s%d", g_CmdName[i], m_kOwnCmdCount[i]);
        m_pBtnCmdList[i]->SetText(text);
    }
}
//--------------------------------------------------------------------
void NwUISPK::RefreshTouchBtn()
{
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        if (m_bXuanYun && i == 0)
        {
            m_pBtnTouchList[NwSPKSide_Left][i]->SetText(g_BuffXuanYunName);
        }
        else
        {
            NwSPKCmdType theCmd = m_kSelectedCmdList[i];
            if (theCmd == NwSPKCmd_Max)
            {
                m_pBtnTouchList[NwSPKSide_Left][i]->SetText("");
            }
            else
            {
                m_pBtnTouchList[NwSPKSide_Left][i]->SetText(g_CmdName[theCmd]);
            }
        }
        //
        if (m_bDongCha == false)
        {
            m_pBtnTouchList[NwSPKSide_Right][i]->SetText("");
        }
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
        m_pBtnTouchList[NwSPKSide_Left][j]->SetInputEnable(bEnable);
        m_pBtnTouchList[NwSPKSide_Right][j]->SetInputEnable(false);
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
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Up] = pUIButton;

    kFullRect.fScaleX = 250.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Middle] = pUIButton;

    kFullRect.fScaleX = 400.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_Down] = pUIButton;

    kFullRect.fScaleX = 550.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_ZhaoJia] = pUIButton;


    kFullRect.fScaleX = 100.0f / fStandardWidth;
    kFullRect.fScaleY = 470.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_ShanBi] = pUIButton;

    kFullRect.fScaleX = 250.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_XuanFeng] = pUIButton;

    kFullRect.fScaleX = 400.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_DongCha] = pUIButton;

    kFullRect.fScaleX = 550.0f / fStandardWidth;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnCmdList[NwSPKCmd_FanSha] = pUIButton;

    //---------------------------------------------------
    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Center;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Top;
    kFullRect.fScaleX = 330.0f / fStandardWidth;
    kFullRect.fScaleY = 50.0f / fStandardHeight;
    kFullRect.fScaleW = 126.0f / fStandardWidth;
    kFullRect.fScaleH = 50.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnTouchList[NwSPKSide_Left][NwSPKTouch_0] = pUIButton;

    kFullRect.fScaleY = 110.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnTouchList[NwSPKSide_Left][NwSPKTouch_1] = pUIButton;

    kFullRect.fScaleY = 170.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnTouchList[NwSPKSide_Left][NwSPKTouch_2] = pUIButton;

    //---------------------------------------------------
    kFullRect.fScaleX = 500.0f / fStandardWidth;
    kFullRect.fScaleY = 50.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnTouchList[NwSPKSide_Right][NwSPKTouch_0] = pUIButton;

    kFullRect.fScaleY = 110.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnTouchList[NwSPKSide_Right][NwSPKTouch_1] = pUIButton;

    kFullRect.fScaleY = 170.0f / fStandardHeight;
    pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
    pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_CmdBtnEmptyTex);
    pUIButton->SetInputEnable(true);
    pUIButton->SetDragEnable(false);
    AddChild(pUIButton);
    m_pBtnTouchList[NwSPKSide_Right][NwSPKTouch_2] = pUIButton;


    //---------------------------------------------------
    GGUIWindowText* pText = NULL;
    GGUIWindowProcessBar* pProcessBar = NULL;
    stUIProcessBarStyle kProcessBarStyle;
    kProcessBarStyle.szTextureBG = "mm1:hud_11";
    kProcessBarStyle.szTextureBar = "mm1:hud_10";
    kProcessBarStyle.fDeltaLeft = 4.0f;
    kProcessBarStyle.fDeltaRight = 4.0f;
    kProcessBarStyle.fDeltaTop = 2.0f;
    kProcessBarStyle.fDeltaBottom = 2.0f;

    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Left;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Top;
    kFullRect.fScaleX = 20.0f / fStandardWidth;
    kFullRect.fScaleY = 10.0f / fStandardHeight;
    kFullRect.fScaleW = 260.0f / fStandardWidth;
    kFullRect.fScaleH = 30.0f / fStandardHeight;
    pText = (GGUIWindowText*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Text);
    pText->SetFullRect(kFullRect);
    pText->SetInputEnable(false);
    pText->SetDragEnable(false);
    AddChild(pText);
    m_pHPText[NwSPKSide_Left] = pText;

    kFullRect.fScaleY = 40.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(false);
    AddChild(pProcessBar);
    pProcessBar->SetProcessBarStyle(&kProcessBarStyle);
    m_pHPList[NwSPKSide_Left] = pProcessBar;

    kFullRect.fScaleY = 70.0f / fStandardHeight;
    pText = (GGUIWindowText*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Text);
    pText->SetFullRect(kFullRect);
    pText->SetInputEnable(false);
    pText->SetDragEnable(false);
    AddChild(pText);
    m_pMPText[NwSPKSide_Left] = pText;


    kFullRect.fScaleY = 100.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(false);
    AddChild(pProcessBar);
    pProcessBar->SetProcessBarStyle(&kProcessBarStyle);
    m_pMPList[NwSPKSide_Left] = pProcessBar;

    //--------------------------
    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Right;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Top;
    kFullRect.fScaleX = 680.0f / fStandardWidth;
    kFullRect.fScaleY = 10.0f / fStandardHeight;
    kFullRect.fScaleW = 260.0f / fStandardWidth;
    kFullRect.fScaleH = 30.0f / fStandardHeight;
    pText = (GGUIWindowText*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Text);
    pText->SetFullRect(kFullRect);
    pText->SetInputEnable(false);
    pText->SetDragEnable(false);
    AddChild(pText);
    m_pHPText[NwSPKSide_Right] = pText;

    kFullRect.fScaleY = 40.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(false);
    AddChild(pProcessBar);
    pProcessBar->SetProcessBarStyle(&kProcessBarStyle);
    m_pHPList[NwSPKSide_Right] = pProcessBar;

    kFullRect.fScaleY = 70.0f / fStandardHeight;
    pText = (GGUIWindowText*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Text);
    pText->SetFullRect(kFullRect);
    pText->SetInputEnable(false);
    pText->SetDragEnable(false);
    AddChild(pText);
    m_pMPText[NwSPKSide_Right] = pText;


    kFullRect.fScaleY = 100.0f / fStandardHeight;
    pProcessBar = (GGUIWindowProcessBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ProcessBar);
    pProcessBar->SetFullRect(kFullRect);
    pProcessBar->SetInputEnable(true);
    pProcessBar->SetDragEnable(false);
    AddChild(pProcessBar);
    pProcessBar->SetProcessBarStyle(&kProcessBarStyle);
    m_pMPList[NwSPKSide_Right] = pProcessBar;


    //-----------------------------
    GGUIWindowImage* pImage = NULL;

    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Center;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Center;
    kFullRect.fScaleX = 320.0f / fStandardWidth;
    kFullRect.fScaleY = 280.0f / fStandardHeight;
    kFullRect.fScaleW = 130.0f / fStandardWidth;
    kFullRect.fScaleH = 95.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_HeroTexture1);
    pImage->SetInputEnable(true);
    pImage->SetDragEnable(false);
    pImage->SetSwapX(true);
    AddChild(pImage);
    m_pHeroList[NwSPKSide_Left] = pImage;

    kFullRect.fScaleX = 540.0f / fStandardWidth;
    kFullRect.fScaleY = 250.0f / fStandardHeight;
    kFullRect.fScaleW = 93.0f / fStandardWidth;
    kFullRect.fScaleH = 125.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_HeroTexture2);
    pImage->SetInputEnable(true);
    pImage->SetDragEnable(false);
    AddChild(pImage);
    m_pHeroList[NwSPKSide_Right] = pImage;


    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Center;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Center;
    kFullRect.fScaleX = 240.0f / fStandardWidth;
    kFullRect.fScaleY = 230.0f / fStandardHeight;
    kFullRect.fScaleW = 56.0f / fStandardWidth;
    kFullRect.fScaleH = 32.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_BuffXuanYunTexture);
    pImage->SetInputEnable(false);
    AddChild(pImage);
    m_pImgXuanYunList[NwSPKSide_Left] = pImage;

    kFullRect.fScaleX = 630.0f / fStandardWidth;
    kFullRect.fScaleY = 220.0f / fStandardHeight;
    kFullRect.fScaleW = 56.0f / fStandardWidth;
    kFullRect.fScaleH = 32.0f / fStandardHeight;
    pImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
    pImage->SetFullRect(kFullRect);
    pImage->SetImage(g_BuffXuanYunTexture);
    pImage->SetInputEnable(false);
    AddChild(pImage);
    m_pImgXuanYunList[NwSPKSide_Right] = pImage;

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



    /*
    kFullRect.eHorzAttachType = GGUIWindowHorzAttach_Left;
    kFullRect.eVertAttachType = GGUIWindowVertAttach_Center;
    kFullRect.fScaleX = 10.0f / fStandardWidth;
    kFullRect.fScaleY = 450.0f / fStandardWidth;
    kFullRect.fScaleW = 300.0f / fStandardWidth;
    kFullRect.fScaleH = 100.0f / fStandardWidth;
    GGUIWindowScrollBar* pScrollBar = (GGUIWindowScrollBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ScrollBar);
    pScrollBar->SetFullRect(kFullRect);
    pScrollBar->SetDragEnable(true);
    AddChild(pScrollBar);
    pScrollBar->SetRange(0.0f, 1.0f, 0.05f);
    pScrollBar->SetValue(0.5f);
    */
}
//----------------------------------------------------------------

