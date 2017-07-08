//----------------------------------------------------------------
#include "GGUIPanelManager.h"
#include "WinInputMsg.h"
//----------------------------------------------------------------
GGUIPanelManager* GGUIPanelManager::ms_pInstance = 0;
//----------------------------------------------------------------
bool GGUIPanelManager::CreateUIPanelManager()
{
	bool br = true;
	if (ms_pInstance == 0)
	{
		ms_pInstance = new GGUIPanelManager;
		if (ms_pInstance && ms_pInstance->InitUIPanelManager())
		{
			br = true;
		}
		else
		{
			ReleaseUIPanelManager();
			br = false;
		}
	}
	return br;
}
//----------------------------------------------------------------
void GGUIPanelManager::ReleaseUIPanelManager()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}
//----------------------------------------------------------------
GGUIPanelManager::GGUIPanelManager()
{

}
//----------------------------------------------------------------
GGUIPanelManager::~GGUIPanelManager()
{
	ClearUIPanelManager();
}
//----------------------------------------------------------------
bool GGUIPanelManager::InitUIPanelManager()
{
	for (int i = 0; i < GGUIPanelSpace_Max; ++i)
	{
		m_kUISpaceArray[i].InitArray(sizeof(GGUIWindowPanel*), 10, 10);
		m_bUISpaceVisible[i] = true;
	}
	return true;
}
//----------------------------------------------------------------
void GGUIPanelManager::ClearUIPanelManager()
{
	for (int i = 0; i < GGUIPanelSpace_Max; ++i)
	{
		m_kUISpaceArray[i].ClearArray();
		m_bUISpaceVisible[i] = true;
	}
}
//----------------------------------------------------------------
void GGUIPanelManager::UpdateUIPanelManager(float fDeltaTime)
{
	SoArray* pArray = 0;
	int nPanelCount = 0;
	void* pElement = 0;
	GGUIWindowPanel* pPanel = 0;
	for (int i = 0; i < GGUIPanelSpace_Max; ++i)
	{
		pArray = &(m_kUISpaceArray[i]);
		nPanelCount = pArray->GetSize();
		for (int j = 0; j < nPanelCount; ++j)
		{
			pElement = pArray->GetAt(j);
			if (pElement)
			{
				pPanel = *(GGUIWindowPanel**)pElement;
				pPanel->UpdateWindow(fDeltaTime);
			}
		}
	}
}
//----------------------------------------------------------------
void GGUIPanelManager::RenderUIPanelManager()
{
	SoArray* pArray = 0;
	int nPanelCount = 0;
	void* pElement = 0;
	GGUIWindowPanel* pPanel = 0;
	for (int i = 0; i < GGUIPanelSpace_Max; ++i)
	{
		if (m_bUISpaceVisible[i] == false)
		{
			continue;
		}
		//
		pArray = &(m_kUISpaceArray[i]);
		nPanelCount = pArray->GetSize();
		for (int j = 0; j < nPanelCount; ++j)
		{
			pElement = pArray->GetAt(j);
			if (pElement)
			{
				pPanel = *(GGUIWindowPanel**)pElement;
				if (pPanel->GetVisible() == false)
				{
					continue;
				}
				pPanel->RenderWindow();
			}
		}
	}
}
//----------------------------------------------------------------
void GGUIPanelManager::InputUIPanelManager(AnInputMsgInfo* kMsgInfo)
{
	SoArray* pArray = 0;
	int nPanelCount = 0;
	void* pElement = 0;
	GGUIWindowPanel* pPanel = 0;
	//注意，UISpace的排序是倒序，即越靠近屏幕越优先处理。
	//与GGUIWindowContainer内的子窗口的排序是相同的。
	for (int i = GGUIPanelSpace_Max-1; i >= 0; --i)
	{
		if (m_bUISpaceVisible[i] == false)
		{
			continue;
		}
		//
		pArray = &(m_kUISpaceArray[i]);
		nPanelCount = pArray->GetSize();
		//注意，Panel的排序是倒序，即越靠近屏幕越优先处理。
		//与GGUIWindowContainer内的子窗口的排序是相同的。
		for (int j = nPanelCount-1; j >= 0; --j)
		{
			pElement = pArray->GetAt(j);
			if (pElement)
			{
				pPanel = *(GGUIWindowPanel**)pElement;
				if (pPanel->GetVisible() == false)
				{
					continue;
				}
				if (pPanel->GetInputEnable() == false)
				{
					continue;
				}
				pPanel->InputWindow2(kMsgInfo);
				if (kMsgInfo->bSwallowed == true)
				{
					break;
				}
			}
		}
		//
		if (kMsgInfo->bSwallowed == true)
		{
			break;
		}
	}
}
//----------------------------------------------------------------
void GGUIPanelManager::ResolutionChanged(float newWidth, float newHeight)
{
	GGUIWindowPanel* pPanel = 0;
	int nPanelCount = 0;
	for (int i = 0; i < GGUIPanelSpace_Max; ++i)
	{
		nPanelCount = UISpace_GetPanelCount(i);
		for (int k = 0; k < nPanelCount; ++k)
		{
			pPanel = GetUIPanel(i, k);
			if (pPanel)
			{
				pPanel->OnResolutionChanged(newWidth, newHeight);
			}
		}
	}
}
//----------------------------------------------------------------
void GGUIPanelManager::AddUIPanel(GGUIWindowPanel* pPanel, int eSpaceType)
{
	if (eSpaceType >= 0 && eSpaceType < GGUIPanelSpace_Max)
	{
		if (pPanel)
		{
			m_kUISpaceArray[eSpaceType].PushBack(&pPanel);
		}
	}
}
//----------------------------------------------------------------
void GGUIPanelManager::RemoveUIPanel(GGUIWindowPanel* pPanel, int eSpaceType)
{
	if (eSpaceType >= 0 && eSpaceType < GGUIPanelSpace_Max)
	{
		if (pPanel)
		{
			m_kUISpaceArray[eSpaceType].Remove(&pPanel);
		}
	}
}
//----------------------------------------------------------------
GGUIWindowPanel* GGUIPanelManager::GetUIPanel(int eSpaceType, int nIndex)
{
	GGUIWindowPanel* pPanel = 0;
	if (eSpaceType >= 0 && eSpaceType < GGUIPanelSpace_Max)
	{
		void* pElement = m_kUISpaceArray[eSpaceType].GetAt(nIndex);
		if (pElement)
		{
			pPanel = *(GGUIWindowPanel**)pElement;
		}
	}
	return pPanel;
}
//----------------------------------------------------------------
void GGUIPanelManager::MakeTopUIPanel(GGUIWindowPanel* pPanel)
{
	if (pPanel)
	{
		const int eSpaceType = pPanel->GetSpaceType();
		if (eSpaceType >= 0 && eSpaceType < GGUIPanelSpace_Max)
		{
			const int nCurIndex = m_kUISpaceArray[eSpaceType].GetIndex(&pPanel);
			if (nCurIndex != -1)
			{
				const int nTopIndex = m_kUISpaceArray[eSpaceType].GetSize() - 1;
				if (nCurIndex != nTopIndex)
				{
					m_kUISpaceArray[eSpaceType].SwapAt(nCurIndex, nTopIndex);
				}
			}
		}
	}
}
//----------------------------------------------------------------
void GGUIPanelManager::UISpace_SetVisible(int eSpaceType, bool bVisible)
{
	if (eSpaceType >= 0 && eSpaceType < GGUIPanelSpace_Max)
	{
		m_bUISpaceVisible[eSpaceType] = bVisible;
	}
}
//----------------------------------------------------------------
bool GGUIPanelManager::UISpace_GetVisible(int eSpaceType)
{
	if (eSpaceType >= 0 && eSpaceType < GGUIPanelSpace_Max)
	{
		return m_bUISpaceVisible[eSpaceType];
	}
	else
	{
		return false;
	}
}
//----------------------------------------------------------------
int GGUIPanelManager::UISpace_GetPanelCount(int eSpaceType)
{
	int nCount = 0;
	if (eSpaceType >= 0 && eSpaceType < GGUIPanelSpace_Max)
	{
		nCount = m_kUISpaceArray[eSpaceType].GetSize();
	}
	return nCount;
}
//----------------------------------------------------------------
