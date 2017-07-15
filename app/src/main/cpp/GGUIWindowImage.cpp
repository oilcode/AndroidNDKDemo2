//----------------------------------------------------------------
#include "GGUIWindowImage.h"
#include "GGUIRenderHelp.h"
//----------------------------------------------------------------
GGUIWindowImage::GGUIWindowImage()
:m_nImagesetIndex(-1)
,m_nImageRectIndex(-1)
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
	GGUIRenderHelp_SimpleImage(m_nImagesetIndex, m_nImageRectIndex, m_kRectInAbsCoord, GGUIColor_Empty);
}
//----------------------------------------------------------------
void GGUIWindowImage::SetImage(const char* szImage)
{
	GGUIFunc_GetImagesetIndexRectIndex(szImage, &m_nImagesetIndex, &m_nImageRectIndex);
}
//----------------------------------------------------------------
