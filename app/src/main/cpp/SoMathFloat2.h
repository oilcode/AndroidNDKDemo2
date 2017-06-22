//----------------------------------------------------------------
#ifndef _SoMathFloat2_h_
#define _SoMathFloat2_h_
//----------------------------------------------------------------
#include "SoMathBase.h"
//----------------------------------------------------------------
class SoMathFloat2
{
public:
	float x;
	float y;

public:
	SoMathFloat2() : x(0.0f), y(0.0f) {};
	SoMathFloat2(float _x, float _y) : x(_x), y(_y) {};
	SoMathFloat2(const SoMathFloat2& kOther) : x(kOther.x), y(kOther.y) {};
	~SoMathFloat2();

	void operator = (const SoMathFloat2& kOther);
	void operator += (const SoMathFloat2& kOther);
	void operator -= (const SoMathFloat2& kOther);
	void operator *= (float fScale);
	void operator /= (float fScale);

	SoMathFloat2 operator + (const SoMathFloat2& kOther);
	SoMathFloat2 operator - (const SoMathFloat2& kOther);
	SoMathFloat2 operator * (float fScale);
	SoMathFloat2 operator / (float fScale);

	void Reset();
};
//----------------------------------------------------------------
inline SoMathFloat2::~SoMathFloat2()
{
	//do nothing
}
//----------------------------------------------------------------
inline void SoMathFloat2::operator = (const SoMathFloat2& kOther)
{
	//if (this == &kOther)
	x = kOther.x;
	y = kOther.y;
}
//----------------------------------------------------------------
inline void SoMathFloat2::operator += (const SoMathFloat2& kOther)
{
	x += kOther.x;
	y += kOther.y;
}
//----------------------------------------------------------------
inline void SoMathFloat2::operator -= (const SoMathFloat2& kOther)
{
	x -= kOther.x;
	y -= kOther.y;
}
//----------------------------------------------------------------
inline void SoMathFloat2::operator *= (float fScale)
{
	x *= fScale;
	y *= fScale;
}
//----------------------------------------------------------------
inline void SoMathFloat2::operator /= (float fScale)
{
	if (SoMath_IsFloatZero2(fScale, SoMath_Min_ChuShu))
	{
		x /= SoMath_Min_ChuShu;
		y /= SoMath_Min_ChuShu;
	}
	else
	{
		x /= fScale;
		y /= fScale;
	}
}
//----------------------------------------------------------------
inline SoMathFloat2 SoMathFloat2::operator + (const SoMathFloat2& kOther)
{
	return SoMathFloat2(x+kOther.x, y+kOther.y);
}
//----------------------------------------------------------------
inline SoMathFloat2 SoMathFloat2::operator - (const SoMathFloat2& kOther)
{
	return SoMathFloat2(x-kOther.x, y-kOther.y);
}
//----------------------------------------------------------------
inline SoMathFloat2 SoMathFloat2::operator * (float fScale)
{
	return SoMathFloat2(x*fScale, y*fScale);
}
//----------------------------------------------------------------
inline SoMathFloat2 SoMathFloat2::operator / (float fScale)
{
	if (SoMath_IsFloatZero2(fScale, SoMath_Min_ChuShu))
	{
		return SoMathFloat2(x/SoMath_Min_ChuShu, y/SoMath_Min_ChuShu);
	}
	else
	{
		return SoMathFloat2(x/fScale, y/fScale);
	}
}
//----------------------------------------------------------------
inline void SoMathFloat2::Reset()
{
	x = 0.0f;
	y = 0.0f;
}
//----------------------------------------------------------------
#endif //_SoMathFloat2_h_
//----------------------------------------------------------------
