//----------------------------------------------------------------
#include "GGUIRenderHelp.h"
#include "GGUIRenderManager.h"
#include "GGUIImagesetManager.h"
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
	const GGUIImageset* pImageset = (GGUIImageset*)GGUIImagesetManager::Get()->GetImagesetByID(nImagesetId);
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
	const GGUIImagesetFont* pImageset = (GGUIImagesetFont*)GGUIImagesetManager::Get()->GetImagesetByName(kFontName);
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

        const stImageFontRect* imageRect = pImageset->GetRect(szSingleWord);
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
            g_kUnit.uiTexResourceId = pImageset->GetTexResourceID();
            g_kUnit.fColorR = kColor.r;
            g_kUnit.fColorG = kColor.g;
            g_kUnit.fColorB = kColor.b;
            g_kUnit.fColorA = kColor.a;
            pRenderManager->AddRnederUnit(&g_kUnit);
            //
            fCurRectLeft += imageRect->advanceX;
        }
        //
        nAccIndex += nSingleWordCharCount;
        nSingleWordCharCount = 0;
    }
}
//----------------------------------------------------------------
