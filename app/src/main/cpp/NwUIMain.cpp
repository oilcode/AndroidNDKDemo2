//----------------------------------------------------------------
#include "NwUIMain.h"
//----------------------------------------------------------------
NwUIMain* NwUIMain::ms_pInstance = 0;
//----------------------------------------------------------------
bool NwUIMain::CreateUIMain()
{
	bool br = true;
	if (ms_pInstance == 0)
	{
		ms_pInstance = new NwUIMain;
		if (ms_pInstance && ms_pInstance->InitUIMain())
		{
			br = true;
		}
		else
		{
			ReleaseUIMain();
			br = false;
		}
	}
	return br;
}
//----------------------------------------------------------------
void NwUIMain::ReleaseUIMain()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}
//----------------------------------------------------------------
NwUIMain::NwUIMain()
:m_nButtonID(-1)
{

}
//----------------------------------------------------------------
NwUIMain::~NwUIMain()
{
	ClearUIMain();
}
//----------------------------------------------------------------
bool NwUIMain::InitUIMain()
{
	GGUIFullRect kFullRect;
	kFullRect.fDeltaX = 100.0f;
	kFullRect.fDeltaY = 50.0f;
	kFullRect.fDeltaW = 100.0f;
	kFullRect.fDeltaH = 200.0f;
	GGUIWindowImage* pUIImageA = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
	pUIImageA->SetFullRect(kFullRect);
	pUIImageA->SetTexture("uitexture/mm1:Name1");
	pUIImageA->SetInputEnable(true);
	pUIImageA->SetDragEnable(true);

	kFullRect.fDeltaX = 300.0f;
	kFullRect.fDeltaY = 150.0f;
	kFullRect.fDeltaW = 100.0f;
	kFullRect.fDeltaH = 30.0f;
	GGUIWindowButton* pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
	pUIButton->SetFullRect(kFullRect);
	pUIButton->SetTexture("uitexture/mm1:Name1");
	pUIButton->SetText("点我吧");
	pUIButton->SetDragEnable(true);
	m_nButtonID = pUIButton->GetID();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


	kFullRect.fDeltaX = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fDeltaW = GGUIFunc_GetResolutionWidth();
	kFullRect.fDeltaH = GGUIFunc_GetResolutionHeight();
	SetFullRect(kFullRect);
	SetInputEnable(true);
	SetDragEnable(false); //本Panel是全屏窗口，不能拖拽。
    SetSpaceType(GGUIPanelSpace_1);

	AddChild(pUIImageA);
	AddChild(pUIButton);

	return true;
}
//----------------------------------------------------------------
void NwUIMain::ClearUIMain()
{
	GGUIWindowPanel::ClearWindow();
	m_nButtonID = -1;
}
//----------------------------------------------------------------
void NwUIMain::UpdateUIMain(float fDeltaTime)
{

}
//----------------------------------------------------------------
void NwUIMain::ProcessUIEvent(int nEventType, void* pParam)
{

}
//----------------------------------------------------------------
