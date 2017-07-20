//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionScale_h_
#define _GGUIActionScale_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionScale : public GGUIActionBase
{
	friend class GGUIActionFactory;
public:
	virtual void UpdateAction(float fDeltaTime);
	virtual bool IsActionFinished() const;

	void InitActionScale(float fDeltaScaleX, float fDeltaScaleY, float fTime);

protected:
    GGUIActionScale();
    virtual ~GGUIActionScale();
    virtual void ClearAction();

protected:
	float m_fSpeedX;
	float m_fSpeedY;
	float m_fRemainTime;
};
//--------------------------------------------------------------------------------------------------
inline bool GGUIActionScale::IsActionFinished() const
{
	return (m_fRemainTime < 0.0f);
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionScale_h_
//--------------------------------------------------------------------------------------------------
