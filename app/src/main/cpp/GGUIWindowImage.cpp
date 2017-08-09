//----------------------------------------------------------------
#include "GGUIWindowImage.h"
#include "GGUIRenderHelp.h"
//----------------------------------------------------------------
GGUIWindowImage::GGUIWindowImage()
:m_nImagesetIndex(-1)
,m_nImageRectIndex(-1)
,m_kColor(GGUIColor_Empty)
,m_bSwapX(false)
,m_bSwapY(false)
{
	m_eType = GGUIWindow_Image;
}
//----------------------------------------------------------------
GGUIWindowImage::~GGUIWindowImage()
{

}
//----------------------------------------------------------------
void GGUIWindowImage::ClearWindow()
{
	GGUIWindowBase::ClearWindow();
	m_kColor = GGUIColor_Empty;
	m_nImagesetIndex = -1;
	m_nImageRectIndex = -1;
}
//----------------------------------------------------------------
void GGUIWindowImage::RenderWindow()
{
	if (m_nImagesetIndex == -1)
	{
		return;
	}
	if (m_nImageRectIndex == -1)
	{
		return;
	}
	GGUIRenderHelp_SimpleImage(m_nImagesetIndex, m_nImageRectIndex, m_kRectInAbsCoord, m_kColor, m_bSwapX, m_bSwapY);
}
//----------------------------------------------------------------
void GGUIWindowImage::SetImage(const char* szImage)
{
	GGUIFunc_GetImagesetIndexRectIndex(szImage, &m_nImagesetIndex, &m_nImageRectIndex);
}
//----------------------------------------------------------------
