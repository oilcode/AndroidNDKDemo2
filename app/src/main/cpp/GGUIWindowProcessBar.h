//------------------------------------------------------------
#ifndef _GGUIWindowProcessBar_h_
#define _GGUIWindowProcessBar_h_
//------------------------------------------------------------
#include "GGUIWindowContainer.h"
//------------------------------------------------------------
struct stUIProcessBarStyle
{
	const char* szTextureBG;
	const char* szTextureBar;
	//距离间隔是几个像素。
	float fDeltaLeft;
	float fDeltaRight;
	float fDeltaTop;
	float fDeltaBottom;
};
//------------------------------------------------------------
class GGUIWindowImage;
//------------------------------------------------------------
class GGUIWindowProcessBar : public GGUIWindowContainer
{
public:
	void SetProcessBarStyle(const stUIProcessBarStyle* pStyle);
	//设置新值，没有动画效果。
	void SetProcessValue(float fValue);
	//设置新值，并播放动画。
	void FlashProcessValue(float fValue);
	float GetProcessValue() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowProcessBar();
	virtual ~GGUIWindowProcessBar();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void UpdateWindow(float fDeltaTime);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void InitProcessBar();

private:
	GGUIWindowImage* m_pBarBG;
	GGUIWindowImage* m_pBarImage;
	//最终的真实的进度值。
	float m_fProcessValue;
	//下面变量用于展示动画效果。
	float m_fProcessValueForFlash;
	float m_fSpeedForFlash;
	float m_fRemainTimeForFlash;
};
//------------------------------------------------------------
inline float GGUIWindowProcessBar::GetProcessValue() const
{
	return m_fProcessValue;
}
//------------------------------------------------------------
#endif //_GGUIWindowProcessBar_h_
//------------------------------------------------------------
