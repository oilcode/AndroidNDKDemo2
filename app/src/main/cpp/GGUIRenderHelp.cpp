//----------------------------------------------------------------
#include "GGUIRenderHelp.h"
//#include "SoD3DTextureSystemFont.h"
#include "GGUIRenderManager.h"
#include "GGUIImagesetManager.h"
#include "GGUIComponentText.h"
//----------------------------------------------------------------
stUIRenderUnit g_kUnit;
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleImage(int nImagesetId, int nImageRectId, const GGUIRect& kAbsRect, const GGUIColor& kColor)
{
	if (nImagesetId == -1)
	{
		return;
	}
	if (nImageRectId == -1)
	{
		return;
	}
	const GGUIImageset* pImageset = GGUIImagesetManager::Get()->GetImagesetByID(nImagesetId);
	if (pImageset == 0)
	{
		return;
	}
	//
	const GGUIRect& imageRect = pImageset->GetRect(nImageRectId);
	g_kUnit.fRectLeft = kAbsRect.x;
	g_kUnit.fRectTop = kAbsRect.y;
	g_kUnit.fRectWidth = kAbsRect.w;
	g_kUnit.fRectHeight = kAbsRect.h;
	g_kUnit.fTexCoordLeft = imageRect.x;
	g_kUnit.fTexCoordTop = imageRect.y;
	g_kUnit.fTexCoordWidth = imageRect.w;
	g_kUnit.fTexCoordHeight = imageRect.h;
	g_kUnit.uiTexResourceId = pImageset->GetTexResourceID();
	g_kUnit.fColorR = kColor.r;
	g_kUnit.fColorG = kColor.g;
	g_kUnit.fColorB = kColor.b;
	g_kUnit.fColorA = kColor.a;
	GGUIRenderManager::Get()->AddRnederUnit(&g_kUnit);
}
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleText(const char* szText, const GGUIRect& kAbsRect, GGUITextAlignX eAlignX, GGUITextAlignY eAlignY, const SoTinyString& kFontName, const GGUIColor& kColor)
{
	if (szText == 0 || szText[0] == 0)
	{
		return;
	}
	GGUIRenderManager* pRenderManager = GGUIRenderManager::Get();
	if (pRenderManager == 0)
	{
		return;
	}
	const GGUIImageset* pImageset = GGUIImagesetManager::Get()->GetImagesetByName(kFontName);
	if (pImageset == 0)
	{
		return;
	}
	//wchar_t* wString = SoAnsiToUnicode(szText);
    wchar_t* wString = L"";
    if (wString[0] == 0)
	{
		return;
	}
	const int nWCharCount = SoWStrLen(wString);
	//
	float fStringWidth = 0.0f;
	float fStringHeight = 0.0f;
	//下面这个函数内部，会把尚未绘制的字形绘制出来，并添加到Imageset中。
	//所以后面的代码就不需要绘制字形。
	//SoD3DTextureSystemFont::Get()->CalculateGlyphSize(wString, nWCharCount, &fStringWidth, &fStringHeight);
	if (fStringWidth < 1.0f || fStringHeight < 1.0f)
	{
		//字符串宽度或者高度小于1个像素，不需要绘制。
		return;
	}
	//
	float fAbsStartPosX = 0.0f;
	float fAbsStartPosY = 0.0f;
	switch (eAlignX)
	{
	case GGUITextAlignX_Left:
		{
			fAbsStartPosX = kAbsRect.x;
		} break;
	case GGUITextAlignX_Center:
		{
			fAbsStartPosX = kAbsRect.x + (kAbsRect.w - fStringWidth) * 0.5f;
		} break;
	case GGUITextAlignX_Right:
		{
			fAbsStartPosX = kAbsRect.x + kAbsRect.w - fStringWidth;
		} break;
	default:
		break;
	}
	switch (eAlignY)
	{
	case GGUITextAlignY_Top:
		{
			fAbsStartPosY = kAbsRect.y;
		} break;
	case GGUITextAlignY_Center:
		{
			fAbsStartPosY = kAbsRect.y + (kAbsRect.h - fStringHeight) * 0.5f;
		} break;
	case GGUITextAlignY_Bottom:
		{
			fAbsStartPosY = kAbsRect.y + kAbsRect.h - fStringHeight;
		} break;
	default:
		break;
	}
	//
	SoTinyString kRectName;
	wchar_t wRectName[2] = {0};
	float fCurRectLeft = fAbsStartPosX;
	float fCurRectTop = fAbsStartPosY;
	const float fTexWidth = pImageset->GetTextureWidth();
	const float fTexHeight = pImageset->GetTextureHeight();
	int nRectIndex = -1;
	for (int i = 0; i < nWCharCount; ++i)
	{
		wRectName[0] = wString[i];
		kRectName = (char*)wRectName;
		nRectIndex = pImageset->GetRectID(kRectName);
		if (nRectIndex == -1)
		{
			continue;
		}
		//
		const GGUIRect& imageRect = pImageset->GetRect(nRectIndex);
		g_kUnit.fRectLeft = fCurRectLeft;
		g_kUnit.fRectTop = fCurRectTop;
		g_kUnit.fRectWidth = imageRect.w * fTexWidth;
		g_kUnit.fRectHeight = imageRect.h * fTexHeight;
		g_kUnit.fTexCoordLeft = imageRect.x;
		g_kUnit.fTexCoordTop = imageRect.y;
		g_kUnit.fTexCoordWidth = imageRect.w;
		g_kUnit.fTexCoordHeight = imageRect.h;
		g_kUnit.uiTexResourceId = pImageset->GetTexResourceID();
		g_kUnit.fColorR = kColor.r;
		g_kUnit.fColorG = kColor.g;
		g_kUnit.fColorB = kColor.b;
		g_kUnit.fColorA = kColor.a;
		pRenderManager->AddRnederUnit(&g_kUnit);
		//
		fCurRectLeft += g_kUnit.fRectWidth;
	}
}
//----------------------------------------------------------------
void GGUIRenderHelp_ComponetText(const GGUIComponentText* pCompText)
{
	const int nCount = pCompText->GetTextChunkCount();
	if (nCount == 0)
	{
		return;
	}

	SoTinyString kRectName;
	wchar_t wRectName[2] = {0};
	//
	for (int i = 0; i < nCount; ++i)
	{
		const GGUITextChunk* pChunk = pCompText->GetTextChunk(i);
		if (pChunk == 0)
		{
			continue;
		}
		const GGUIImageset* pImageset = GGUIImagesetManager::Get()->GetImagesetByID(pChunk->FontImagesetID);
		if (pImageset == 0)
		{
			continue;
		}
		//
		const float fTexWidth = pImageset->GetTextureWidth();
		const float fTexHeight = pImageset->GetTextureHeight();
		//
		float fCurRectLeft = pChunk->kRect.x;
		float fCurRectTop = pChunk->kRect.y;
		const int nCharCount = pChunk->TextCount;
		for (int j = 0; j < nCharCount; ++j)
		{
			wRectName[0] = pChunk->szText[j];
			kRectName = (char*)wRectName;
			const int nRectIndex = pImageset->GetRectID(kRectName);
			if (nRectIndex == -1)
			{
				continue;
			}
			//
			const GGUIRect& imageRect = pImageset->GetRect(nRectIndex);
			g_kUnit.fRectLeft = fCurRectLeft;
			g_kUnit.fRectTop = fCurRectTop;
			g_kUnit.fRectWidth = imageRect.w * fTexWidth;
			g_kUnit.fRectHeight = imageRect.h * fTexHeight;
			g_kUnit.fTexCoordLeft = imageRect.x;
			g_kUnit.fTexCoordTop = imageRect.y;
			g_kUnit.fTexCoordWidth = imageRect.w;
			g_kUnit.fTexCoordHeight = imageRect.h;
			g_kUnit.uiTexResourceId = pImageset->GetTexResourceID();
			g_kUnit.fColorR = pChunk->kColor.r;
			g_kUnit.fColorG = pChunk->kColor.g;
			g_kUnit.fColorB = pChunk->kColor.b;
			g_kUnit.fColorA = pChunk->kColor.a;
			GGUIRenderManager::Get()->AddRnederUnit(&g_kUnit);
			//
			fCurRectLeft += g_kUnit.fRectWidth;
		}
	}
}
//----------------------------------------------------------------
