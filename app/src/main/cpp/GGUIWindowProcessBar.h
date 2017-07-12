//------------------------------------------------------------
#ifndef _GGUIWindowProcessBar_h_
#define _GGUIWindowProcessBar_h_
//------------------------------------------------------------
#include "GGUIWindowContainer.h"
//------------------------------------------------------------
class GGUIWindowImage;
//------------------------------------------------------------
class GGUIWindowProcessBar : public GGUIWindowContainer
{
public:
	void SetProcessValue(float fValue);
	float GetProcessValue() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowProcessBar();
	virtual ~GGUIWindowProcessBar();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void InitProcessBar();

private:
	GGUIWindowImage* m_pBarBG;
	GGUIWindowImage* m_pBarImage;
	float m_fProcessValue;
};
//------------------------------------------------------------
inline float GGUIWindowProcessBar::GetProcessValue() const
{
	return m_fProcessValue;
}
//------------------------------------------------------------
#endif //_GGUIWindowProcessBar_h_
//------------------------------------------------------------
