//----------------------------------------------------------------
#ifndef _SoMathFloat3_h_
#define _SoMathFloat3_h_
//----------------------------------------------------------------
#include "SoMathBase.h"
//----------------------------------------------------------------
class SoMathFloat3
{
public:
	float x;
	float y;
	float z;

public:
	SoMathFloat3() : x(0.0f), y(0.0f), z(0.0f) {};
	SoMathFloat3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	SoMathFloat3(const SoMathFloat3& kOther) : x(kOther.x), y(kOther.y), z(kOther.z) {};
	~SoMathFloat3();

	void operator = (const SoMathFloat3& kOther);
	void operator += (const SoMathFloat3& kOther);
	void operator -= (const SoMathFloat3& kOther);
	void operator *= (float fScale);
	void operator /= (float fScale);

	SoMathFloat3 operator + (const SoMathFloat3& kOther) const;
	SoMathFloat3 operator - (const SoMathFloat3& kOther) const;
	SoMathFloat3 operator * (float fScale) const;
	SoMathFloat3 operator / (float fScale) const;
	SoMathFloat3 operator - () const;

	void Reset();
	float Length() const;
	void Unitize();
	float Unitize_Length();
	float Dot(const SoMathFloat3& kOther) const;
	SoMathFloat3 Cross(const SoMathFloat3& kOther) const;
};
//----------------------------------------------------------------
inline SoMathFloat3::~SoMathFloat3()
{
	//do nothing
}
//----------------------------------------------------------------
inline void SoMathFloat3::operator = (const SoMathFloat3& kOther)
{
	//if (this == &kOther)
	x = kOther.x;
	y = kOther.y;
	z = kOther.z;
}
//----------------------------------------------------------------
inline void SoMathFloat3::operator += (const SoMathFloat3& kOther)
{
	x += kOther.x;
	y += kOther.y;
	z += kOther.z;
}
//----------------------------------------------------------------
inline void SoMathFloat3::operator -= (const SoMathFloat3& kOther)
{
	x -= kOther.x;
	y -= kOther.y;
	z -= kOther.z;
}
//----------------------------------------------------------------
inline void SoMathFloat3::operator *= (float fScale)
{
	x *= fScale;
	y *= fScale;
	z *= fScale;
}
//----------------------------------------------------------------
inline void SoMathFloat3::operator /= (float fScale)
{
	if (SoMath_IsFloatZero2(fScale, SoMath_Min_ChuShu))
	{
		x /= SoMath_Min_ChuShu;
		y /= SoMath_Min_ChuShu;
		z /= SoMath_Min_ChuShu;
	}
	else
	{
		x /= fScale;
		y /= fScale;
		z /= fScale;
	}
}
//----------------------------------------------------------------
inline SoMathFloat3 SoMathFloat3::operator + (const SoMathFloat3& kOther) const
{
	return SoMathFloat3(x+kOther.x, y+kOther.y, z+kOther.z);
}
//----------------------------------------------------------------
inline SoMathFloat3 SoMathFloat3::operator - (const SoMathFloat3& kOther) const
{
	return SoMathFloat3(x-kOther.x, y-kOther.y, z-kOther.z);
}
//----------------------------------------------------------------
inline SoMathFloat3 SoMathFloat3::operator * (float fScale) const
{
	return SoMathFloat3(x*fScale, y*fScale, z*fScale);
}
//----------------------------------------------------------------
inline SoMathFloat3 SoMathFloat3::operator / (float fScale) const
{
	if (SoMath_IsFloatZero2(fScale, SoMath_Min_ChuShu))
	{
		return SoMathFloat3(x/SoMath_Min_ChuShu, y/SoMath_Min_ChuShu, z/SoMath_Min_ChuShu);
	}
	else
	{
		return SoMathFloat3(x/fScale, y/fScale, z/fScale);
	}
}
//----------------------------------------------------------------
inline SoMathFloat3 SoMathFloat3::operator - () const
{
	return SoMathFloat3(-x, -y, -z);
}
//----------------------------------------------------------------
inline void SoMathFloat3::Reset()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
//----------------------------------------------------------------
#endif
//----------------------------------------------------------------
