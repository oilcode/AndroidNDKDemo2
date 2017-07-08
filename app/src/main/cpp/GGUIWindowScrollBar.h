//------------------------------------------------------------
#ifndef _GGUIWindowScrollBar_h_
#define _GGUIWindowScrollBar_h_
//------------------------------------------------------------
#include "GGUIWindowContainer.h"
//------------------------------------------------------------
class GGUIWindowButton;
//------------------------------------------------------------
class GGUIWindowScrollBar : public GGUIWindowContainer
{
public:
	void SetRange(float fMin, float fMax, float fStep);
	void SetValue(float fValue);
	float GetValue() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowScrollBar();
	virtual ~GGUIWindowScrollBar();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void ProcessUIEvent(int nEventType, void* pParam);
	virtual void SetUIEventHandler(GGUIWindowBase* pHandler);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void InitScrollBar();
	//当滑块的位置发生了变化，就要调用本函数来规范滑块的位置，并计算当前值。
	void AdjustCenterBtnPos();

private:
	GGUIWindowButton* m_pBtnLeft;
	GGUIWindowButton* m_pBtnRight;
	GGUIWindowButton* m_pBtnCenter;
	//记录最初的滑块的位置，当滑块移动后，用来规范滑块的位置。
	float m_fCenterBtn_FullRectDeltaY;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<
	//取值范围的最大值。
	float m_fRangeMaxValue;
	//取值范围的最小值。
	float m_fRangeMinValue;
	//点击两侧按钮时，当前值的变化量。
	//注意，是当前值的变化，不是滑块的位置变化。
	float m_fRangeStep;
	//点击两侧按钮时，滑块的位置变化。
	float m_fRangePosDeltaPerStep;
	//滑块移动时，每个像素会导致值变化多少。
	float m_fRangeValueDeltaPerPixel;
	//当前值。取值范围是[m_fRangeMinValue, m_fRangeMaxValue]。
	float m_fRangeCurValue;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>
};
//------------------------------------------------------------
inline float GGUIWindowScrollBar::GetValue() const
{
	return m_fRangeCurValue;
}
//------------------------------------------------------------
#endif //_GGUIWindowScrollBar_h_
//------------------------------------------------------------
