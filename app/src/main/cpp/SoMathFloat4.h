//----------------------------------------------------------------
#ifndef _SoMathFloat4_h_
#define _SoMathFloat4_h_
//----------------------------------------------------------------
#include "SoMathBase.h"
#include "SoMathFloat3.h"
//----------------------------------------------------------------
class SoMathFloat4
{
public:
	float x;
	float y;
	float z;
	float w;

public:
	SoMathFloat4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
	SoMathFloat4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};
	SoMathFloat4(const SoMathFloat4& kOther) : x(kOther.x), y(kOther.y), z(kOther.z), w(kOther.w) {};
	~SoMathFloat4();

	void operator = (const SoMathFloat4& kOther);
	void operator += (const SoMathFloat4& kOther);
	void operator -= (const SoMathFloat4& kOther);
	void operator *= (float fScale);
	void operator /= (float fScale);

	SoMathFloat4 operator + (const SoMathFloat4& kOther);
	SoMathFloat4 operator - (const SoMathFloat4& kOther);
	SoMathFloat4 operator * (float fScale);
	SoMathFloat4 operator / (float fScale);
	SoMathFloat4 operator - () const;

	void Reset();
    SoMathFloat3 GetFloat3();
};
//----------------------------------------------------------------
inline SoMathFloat4::~SoMathFloat4()
{
	//do nothing
}
//----------------------------------------------------------------
inline void SoMathFloat4::operator = (const SoMathFloat4& kOther)
{
	//if (this == &kOther)
	x = kOther.x;
	y = kOther.y;
	z = kOther.z;
	w = kOther.w;
}
//----------------------------------------------------------------
inline void SoMathFloat4::operator += (const SoMathFloat4& kOther)
{
	x += kOther.x;
	y += kOther.y;
	z += kOther.z;
	w += kOther.w;
}
//----------------------------------------------------------------
inline void SoMathFloat4::operator -= (const SoMathFloat4& kOther)
{
	x -= kOther.x;
	y -= kOther.y;
	z -= kOther.z;
	w -= kOther.w;
}
//----------------------------------------------------------------
inline void SoMathFloat4::operator *= (float fScale)
{
	x *= fScale;
	y *= fScale;
	z *= fScale;
	w *= fScale;
}
//----------------------------------------------------------------
inline void SoMathFloat4::operator /= (float fScale)
{
	if (SoMath_IsFloatZero2(fScale, SoMath_Min_ChuShu))
	{
		x /= SoMath_Min_ChuShu;
		y /= SoMath_Min_ChuShu;
		z /= SoMath_Min_ChuShu;
		w /= SoMath_Min_ChuShu;
	}
	else
	{
		x /= fScale;
		y /= fScale;
		z /= fScale;
		w /= fScale;
	}
}
//----------------------------------------------------------------
inline SoMathFloat4 SoMathFloat4::operator + (const SoMathFloat4& kOther)
{
	return SoMathFloat4(x+kOther.x, y+kOther.y, z+kOther.z, w+kOther.w);
}
//----------------------------------------------------------------
inline SoMathFloat4 SoMathFloat4::operator - (const SoMathFloat4& kOther)
{
	return SoMathFloat4(x-kOther.x, y-kOther.y, z-kOther.z, w-kOther.w);
}
//----------------------------------------------------------------
inline SoMathFloat4 SoMathFloat4::operator * (float fScale)
{
	return SoMathFloat4(x*fScale, y*fScale, z*fScale, w*fScale);
}
//----------------------------------------------------------------
inline SoMathFloat4 SoMathFloat4::operator / (float fScale)
{
	if (SoMath_IsFloatZero2(fScale, SoMath_Min_ChuShu))
	{
		return SoMathFloat4(x/SoMath_Min_ChuShu, y/SoMath_Min_ChuShu, z/SoMath_Min_ChuShu, w/SoMath_Min_ChuShu);
	}
	else
	{
		return SoMathFloat4(x/fScale, y/fScale, z/fScale, w/fScale);
	}
}
//----------------------------------------------------------------
inline SoMathFloat4 SoMathFloat4::operator - () const
{
	return SoMathFloat4(-x, -y, -z, -w);
}
//----------------------------------------------------------------
inline void SoMathFloat4::Reset()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}
//----------------------------------------------------------------
inline SoMathFloat3 SoMathFloat4::GetFloat3()
{
    return SoMathFloat3(x, y, z);
}
//----------------------------------------------------------------
#endif
//----------------------------------------------------------------
