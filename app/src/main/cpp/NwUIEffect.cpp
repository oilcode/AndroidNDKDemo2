//--------------------------------------------------------------------------------------------------
#include "NwUIEffect.h"
//--------------------------------------------------------------------------------------------------
NwUIEffect* NwUIEffect::ms_pInstance = NULL;
//--------------------------------------------------------------------------------------------------
bool NwUIEffect::CreateUIEffect()
{
    bool br = true;
    if (ms_pInstance == 0)
    {
        ms_pInstance = SoNew NwUIEffect;
        if (ms_pInstance && ms_pInstance->InitUIEffect())
        {
            br = true;
        }
        else
        {
            ReleaseUIEffect();
            br = false;
        }
    }
    return br;
}
//--------------------------------------------------------------------------------------------------
void NwUIEffect::ReleaseUIEffect()
{
    if (ms_pInstance)
    {
    	ms_pInstance->ClearUIEffect();
        SoDelete ms_pInstance;
        ms_pInstance = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
NwUIEffect::NwUIEffect()
{
	for (int i = 0; i < UIEffect_MaxDamageNumber; ++i)
	{
		m_pDamageNumberList[i] = NULL;
	}
}
//--------------------------------------------------------------------------------------------------
NwUIEffect::~NwUIEffect()
{

}
//--------------------------------------------------------------------------------------------------
bool NwUIEffect::InitUIEffect()
{
	float fStandardWidth = 960.0f;
	float fStandardHeight = 540.0f;
	SetStandardWidthHeight(fStandardWidth, fStandardHeight);
    SetInputEnable(false);
    SetDragEnable(false); //本Panel是全屏窗口，不能拖拽。
    SetSpaceType(GGUIPanelSpace_Effect);
    //
    CreateWindow_DamageNumber();
    //
    return true;
}
//--------------------------------------------------------------------------------------------------
void NwUIEffect::ClearUIEffect()
{
	GGUIWindowPanel::ClearWindow();
}
//--------------------------------------------------------------------------------------------------
void NwUIEffect::CreateWindow_DamageNumber()
{
	GGUIFullRect kFullRect;
    kFullRect.fDeltaX = 0.0f;
    kFullRect.fDeltaY = 0.0f;
    kFullRect.fDeltaW = 300.0f;
    kFullRect.fDeltaH = 80.0f;

	for (int i = 0; i < UIEffect_MaxDamageNumber; ++i)
	{
    	GGUIWindowText* pUIText = (GGUIWindowText*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Text);
    	pUIText->SetFullRect(kFullRect);
    	pUIText->SetColor(GGUIColor_Red);
    	pUIText->SetFont("uitexture/nwfont");
    	pUIText->SetInputEnable(false);
    	pUIText->SetDragEnable(false);
    	pUIText->SetVisible(false);
    	AddChild(pUIText);
		m_pDamageNumberList[i] = pUIText;
	}
}
//--------------------------------------------------------------------------------------------------
GGUIWindowText* NwUIEffect::GetUnusedDamageNumber(int* pIndex)
{
	GGUIWindowText* pUnused = NULL;
	for (int i = 0; i < UIEffect_MaxDamageNumber; ++i)
	{
		if (m_pDamageNumberList[i])
		{
			if (m_pDamageNumberList[i]->GetVisible() == false)
			{
				pUnused = m_pDamageNumberList[i];
				if (pIndex)
				{
					*pIndex = i;
				}
				break;
			}
		}
	}
	return pUnused;
}
//--------------------------------------------------------------------------------------------------
void NwUIEffect::PlayDamageNumber(const stDamageNumberParam& kParam)
{
	int nIndex = 0;
	GGUIWindowText* pText = GetUnusedDamageNumber(&nIndex);
	if (pText == NULL)
	{
		return;
	}

	pText->SetVisible(true);
	pText->SetFullRectDeltaPos(kParam.fStartPosX, kParam.fStartPosY);
	pText->SetText(SoStrFmt("%d", kParam.nNumber));

    GGUIActionGroup* theActionGroup = pText->CreateActionGroup();
    //theActionGroup->RemoveAllAction();
    //theActionGroup->SetDestWindow(pText);
	theActionGroup->SetActionEventHandler(this);

    GGUIActionLine* pActionLine = (GGUIActionLine*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Line);;
    theActionGroup->AddActionLine(pActionLine);

    GGUIActionMove* pActionMove = (GGUIActionMove*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Move);
    pActionMove->InitActionMove(0.0f, 50.0f, kParam.fTime);
    pActionLine->AddAction(pActionMove);

    GGUIActionEvent* pActionEvent = (GGUIActionEvent*)GGUIActionFactory::Get()->CreateUIAction(GGUIAction_Event);
    pActionEvent->InitActionEvent(UIEffect_EventID_DamageNumberFirst + nIndex);
    pActionLine->AddAction(pActionEvent);
}
//--------------------------------------------------------------------------------------------------
void NwUIEffect::UpdateWindow(float fDeltaTime)
{
	GGUIWindowPanel::UpdateWindow(fDeltaTime);
}
//--------------------------------------------------------------------------------------------------
bool NwUIEffect::InputWindow(GGUIInputMsg* pInputMsg)
{
	if (GGUIWindowPanel::InputWindow(pInputMsg) == true)
	{
		//父类已经处理了input，派生类不要再处理。
		return true;
	}
	
	return false;
}
//--------------------------------------------------------------------------------------------------
void NwUIEffect::ProcessUIEvent(int nEventType, void* pParam)
{
	GGUIWindowPanel::ProcessUIEvent(nEventType, pParam);
}
//--------------------------------------------------------------------------------------------------
void NwUIEffect::ProcessActionEvent(int nEventId)
{
	if (nEventId < UIEffect_EventID_DamageNumberFirst + UIEffect_MaxDamageNumber)
	{
		int nIndex = nEventId - UIEffect_EventID_DamageNumberFirst;
		if (nIndex >= 0 && nIndex < UIEffect_MaxDamageNumber)
		{
            GGUIWindowText* pText = m_pDamageNumberList[nIndex];
            //pText->CreateActionGroup()->RemoveAllAction();
            pText->SetVisible(false);
		}
	}
}
//--------------------------------------------------------------------------------------------------
