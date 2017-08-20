//----------------------------------------------------------------
#include "GGUIRenderHelp.h"
#include "GGUIImagesetManager.h"
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
#include "GGUIRenderManagerGL.h"
#include "GLTextureManager.h"
#endif
//----------------------------------------------------------------
bool GGUIRenderHelp_Create()
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    if (GGUIRenderManagerGL::CreateUIRenderManagerGL() == false)
    {
        return false;
    }
#endif
    return true;
}
//----------------------------------------------------------------
void GGUIRenderHelp_Release()
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    GGUIRenderManagerGL::ReleaseUIRenderManagerGL();
#endif
}
//----------------------------------------------------------------
void GGUIRenderHelp_Render()
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    GGUIRenderManagerGL::Get()->RenderUIRenderManager();
#endif
}
//----------------------------------------------------------------
void GGUIRenderHelp_AddRnederUnit(const stUIRenderUnit* pUIRenderUnit)
{
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    GGUIRenderManagerGL::Get()->AddRnederUnit(pUIRenderUnit);
#endif
}
//----------------------------------------------------------------
void* GGUIRenderHelp_CreateUITextureFromFile(const char* szFullTexName)
{
    void* pTexture = NULL;
#if (SoTargetPlatform == SoPlatform_Windows)

#elif (SoTargetPlatform == SoPlatform_Android)
    pTexture = GLTextureManager::Get()->CreateUITextureFromFile(szFullTexName);
#endif
    return pTexture;
}
//----------------------------------------------------------------
stUIRenderUnit g_kUnit;
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleImage(int nImagesetId, int nImageRectId, const GGUIRect& kAbsRect, const GGUIColor& kColor, bool bSwapX, bool bSwapY)
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
	if (pImageset == NULL)
	{
		return;
	}
	const stImageRect* imageRect = pImageset->GetRectByID(nImageRectId);
	if (imageRect == NULL)
	{
		return;
	}

	g_kUnit.fRectLeft = kAbsRect.x;
	g_kUnit.fRectRight = kAbsRect.x + kAbsRect.w;
	g_kUnit.fRectTop = kAbsRect.y;
	g_kUnit.fRectBottom = kAbsRect.y + kAbsRect.h;

	if (bSwapX)
	{
		g_kUnit.fTexCoordLeft = imageRect->right;
        g_kUnit.fTexCoordRight = imageRect->left;
	}
	else
	{
		g_kUnit.fTexCoordLeft = imageRect->left;
        g_kUnit.fTexCoordRight = imageRect->right;
	}

    if (bSwapY)
    {
        g_kUnit.fTexCoordTop = imageRect->bottom;
        g_kUnit.fTexCoordBottom = imageRect->top;
    }
    else
    {
        g_kUnit.fTexCoordTop = imageRect->top;
        g_kUnit.fTexCoordBottom = imageRect->bottom;
    }

	g_kUnit.fColorR = kColor.r;
	g_kUnit.fColorG = kColor.g;
	g_kUnit.fColorB = kColor.b;
	g_kUnit.fColorA = kColor.a;
    g_kUnit.uiTexResource = pImageset->GetTexResource();
    GGUIRenderHelp_AddRnederUnit(&g_kUnit);
}
//----------------------------------------------------------------
void GGUIRenderHelp_SimpleText(const char* szText, const GGUIRect& kAbsRect, GGUITextAlignX eAlignX, GGUITextAlignY eAlignY, const SoTinyString& kFontName, const GGUIColor& kColor)
{
	if (szText == 0 || szText[0] == 0)
	{
		return;
	}
	const GGUIImageset* pImageset = GGUIImagesetManager::Get()->GetImagesetByName(kFontName);
	if (pImageset == 0)
	{
		return;
	}

	const int nCharCount = SoStrLen(szText);
	//
	float fStringWidth = 0.0f;
	float fStringHeight = 0.0f;
	pImageset->CalculateStringGlyphSize(szText, nCharCount, &fStringWidth, &fStringHeight);
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
	float fCurRectLeft = fAbsStartPosX;
	float fCurRectTop = fAbsStartPosY;

    int nAccIndex = 0;
    int nSingleWordCharCount = 0;
    const char* szSingleWord = "";
    while (true)
    {
    	szSingleWord = SoGetOneCharacterFromUtf8String(szText, nCharCount, nAccIndex, &nSingleWordCharCount);
    	if (nSingleWordCharCount == 0)
    	{
    		break;
    	}

        const stImageRect* imageRect = pImageset->GetFontRect(szSingleWord);
        if (imageRect)
        {
            g_kUnit.fRectLeft = fCurRectLeft + imageRect->offsetX;
            g_kUnit.fRectRight = g_kUnit.fRectLeft + imageRect->width;
            g_kUnit.fRectTop = fCurRectTop + imageRect->offsetY;
            g_kUnit.fRectBottom = g_kUnit.fRectTop + imageRect->height;
            g_kUnit.fTexCoordLeft = imageRect->left;
            g_kUnit.fTexCoordRight = imageRect->right;
            g_kUnit.fTexCoordTop = imageRect->top;
            g_kUnit.fTexCoordBottom = imageRect->bottom;
            g_kUnit.fColorR = kColor.r;
            g_kUnit.fColorG = kColor.g;
            g_kUnit.fColorB = kColor.b;
            g_kUnit.fColorA = kColor.a;
            g_kUnit.uiTexResource = pImageset->GetTexResource();
            GGUIRenderHelp_AddRnederUnit(&g_kUnit);
            //
            fCurRectLeft += imageRect->advanceX;
        }
        //
        nAccIndex += nSingleWordCharCount;
        nSingleWordCharCount = 0;
    }
}
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
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
			g_kUnit.pTexture = pImageset->GetTexture();
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
#endif
//----------------------------------------------------------------
