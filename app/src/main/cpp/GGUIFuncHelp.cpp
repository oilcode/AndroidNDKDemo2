//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
#include "GGUIImagesetManager.h"
#include "GGUIPanelManager.h"
//----------------------------------------------------------------
float g_fResolutionWidth = 800.0f;
float g_fResolutionHeight = 600.0f;
//----------------------------------------------------------------
bool GGUIFunc_GetImagesetIndexRectIndex(const char* szTexture, int* pImagesetIndex, int* pRectIndex)
{
	if (szTexture == 0 || szTexture[0] == 0)
	{
		return false;
	}
	const int nSplitIndex = SoStrChr(szTexture, ':');
	if (nSplitIndex == -1)
	{
		return false;
	}
	const char* pImagesetName = SoSubStr(szTexture, 0, nSplitIndex-1);
	SoTinyString kName(pImagesetName);
	const int nImagesetIndex = GGUIImagesetManager::Get()->GetImagesetIDByName(kName);
	if (nImagesetIndex == -1)
	{
		return false;
	}
	GGUIImageset* pImagesetBase = GGUIImagesetManager::Get()->GetImagesetByID(nImagesetIndex);
	if (pImagesetBase == NULL)
	{
		return false;
	}
	//
	GGUIImageset* pImageset = (GGUIImageset*)pImagesetBase;
	kName.SetValue(szTexture + nSplitIndex + 1);
	*pImagesetIndex = nImagesetIndex;
	*pRectIndex = pImageset->GetRectID(kName);
	return true;
}
//----------------------------------------------------------------
void GGUIFunc_UIntConvertToGGUIColor(unsigned int uiColor, GGUIColor* pColor)
{
	const float fScale = 1.0f / 255.0f;

	unsigned int uiR = uiColor >> 24;
	pColor->r = ((float)uiR) * fScale;

	unsigned int uiG = uiColor << 8;
	uiG = uiG >> 24;
	pColor->g = ((float)uiG) * fScale;

	unsigned int uiB = uiColor << 16;
	uiB = uiB >> 24;
	pColor->b = ((float)uiB) * fScale;

	unsigned int uiA = uiColor << 24;
	uiA = uiA >> 24;
	pColor->a = ((float)uiA) * fScale;
}
//----------------------------------------------------------------
void GGUIFunc_OnResolutionChanged(float newWidth, float newHeight)
{
	g_fResolutionWidth = newWidth;
	g_fResolutionHeight = newHeight;
	//
	GGUIPanelManager* pPanelManager = GGUIPanelManager::Get();
	if (pPanelManager)
	{
		pPanelManager->ResolutionChanged(newWidth, newHeight);
	}
}
//----------------------------------------------------------------
float GGUIFunc_GetResolutionWidth()
{
	return g_fResolutionWidth;
}
//----------------------------------------------------------------
float GGUIFunc_GetResolutionHeight()
{
	return g_fResolutionHeight;
}
//----------------------------------------------------------------
