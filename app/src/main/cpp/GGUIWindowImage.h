//----------------------------------------------------------------
#ifndef _GGUIWindowImage_h_
#define _GGUIWindowImage_h_
//----------------------------------------------------------------
#include "GGUIWindowBase.h"
//----------------------------------------------------------------
class GGUIWindowImage : public GGUIWindowBase
{
public:
	//--szImage "ImagesetName:RectName"
	void SetImage(const char* szImage);
    void SetSwapX(bool bSwapX);
    void SetSwapY(bool bSwapY);

	int GetImagesetIndex() const;
	int GetImageRectIndex() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowImage();
	virtual ~GGUIWindowImage();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void RenderWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

private:
	int m_nImagesetIndex;
	int m_nImageRectIndex;
    bool m_bSwapX;
    bool m_bSwapY;
};
//----------------------------------------------------------------
inline int GGUIWindowImage::GetImagesetIndex() const
{
	return m_nImagesetIndex;
}
//----------------------------------------------------------------
inline int GGUIWindowImage::GetImageRectIndex() const
{
	return m_nImageRectIndex;
}
//----------------------------------------------------------------
inline void GGUIWindowImage::SetSwapX(bool bSwapX)
{
    m_bSwapX = bSwapX;
}
//----------------------------------------------------------------
inline void GGUIWindowImage::SetSwapY(bool bSwapY)
{
    m_bSwapY = bSwapY;
}
//----------------------------------------------------------------
#endif //_GGUIWindowImage_h_
//----------------------------------------------------------------
