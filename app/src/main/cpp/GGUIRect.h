//------------------------------------------------------------
#ifndef _GGUIRect_h_
#define _GGUIRect_h_
//------------------------------------------------------------
class GGUIRect
{
public:
	GGUIRect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) { }
	GGUIRect(float fx, float fy, float fw, float fh) : x(fx), y(fy), w(fw), h(fh) { }
	void Clear();
	bool IsInside(float fPointX, float fPointY) const;

public:
	float x;
	float y;
	float w;
	float h;
};
//------------------------------------------------------------
inline void GGUIRect::Clear()
{
	x = 0.0f;
	y = 0.0f;
	w = 0.0f;
	h = 0.0f;
}
//------------------------------------------------------------
inline bool GGUIRect::IsInside(float fPointX, float fPointY) const
{
	if (fPointX > x && fPointY > y && (fPointX < x + w) && (fPointY < y + h))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//------------------------------------------------------------
extern const GGUIRect GGUIRect_Empty;
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
enum GGUIWindowHorzAttachType
{
	GGUIWindowHorzAttach_Left,
	GGUIWindowHorzAttach_Center,
	GGUIWindowHorzAttach_Right,
};
//------------------------------------------------------------
enum GGUIWindowVertAttachType
{
	GGUIWindowVertAttach_Top,
	GGUIWindowVertAttach_Center,
	GGUIWindowVertAttach_Bottom,
};
//------------------------------------------------------------
class GGUIFullRect
{
public:
	GGUIFullRect() : eHorzAttachType(GGUIWindowHorzAttach_Left), eVertAttachType(GGUIWindowVertAttach_Top)
                   , fScaleX(0.0f), fDeltaX(0.0f), fScaleY(0.0f), fDeltaY(0.0f)
				   , fScaleW(0.0f), fDeltaW(0.0f), fScaleH(0.0f), fDeltaH(0.0f) { }
	void Clear();

public:
	GGUIWindowHorzAttachType eHorzAttachType;
	GGUIWindowVertAttachType eVertAttachType;
	//
	float fScaleX;
	float fDeltaX;
	//
	float fScaleY;
	float fDeltaY;
	//
	float fScaleW;
	float fDeltaW;
	//
	float fScaleH;
	float fDeltaH;
};
//------------------------------------------------------------
inline void GGUIFullRect::Clear()
{
	eHorzAttachType = GGUIWindowHorzAttach_Left;
	eVertAttachType = GGUIWindowVertAttach_Top;
	fScaleX = 0.0f;
	fDeltaX = 0.0f;
	fScaleY = 0.0f;
	fDeltaY = 0.0f;
	fScaleW = 0.0f;
	fDeltaW = 0.0f;
	fScaleH = 0.0f;
	fDeltaH = 0.0f;
}
//------------------------------------------------------------
extern const GGUIFullRect GGUIFullRect_Empty;
//------------------------------------------------------------
#endif //_GGUIRect_h_
//------------------------------------------------------------
