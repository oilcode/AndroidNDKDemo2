//----------------------------------------------------------------
#include "SoMathFloat3.h"
//----------------------------------------------------------------
float SoMathFloat3::Length() const
{
	float f1 = x*x + y*y + z*z;
	float f2;
	SoMath_Sqrt(f1, f2);
	return f2;
}
//----------------------------------------------------------------
void SoMathFloat3::Unitize()
{
	float f1 = x*x + y*y + z*z;
	float f2;
	SoMath_InvSqrt(f1, f2);
	x *= f2;
	y *= f2;
	z *= f2;
}
//----------------------------------------------------------------
float SoMathFloat3::Unitize_Length()
{
	float f1 = x*x + y*y + z*z;
	float f2;
	SoMath_InvSqrt(f1, f2);
	x *= f2;
	y *= f2;
	z *= f2;
	//
	if (SoMath_IsFloatZero2(f2, SoMath_Min_ChuShu))
	{
		return (1.0f / SoMath_Min_ChuShu);
	}
	else
	{
		return (1.0f / f2);
	}
}
//----------------------------------------------------------------
float SoMathFloat3::Dot(const SoMathFloat3& kOther) const
{
	return (x*kOther.x + y*kOther.y + z*kOther.z);
}
//----------------------------------------------------------------
SoMathFloat3 SoMathFloat3::Cross(const SoMathFloat3& kOther) const
{
	float fResultX = y*kOther.z - z*kOther.y;
	float fResultY = z*kOther.x - x*kOther.z;
	float fResultZ = x*kOther.y - y*kOther.x;
	return SoMathFloat3(fResultX, fResultY, fResultZ);
}
//----------------------------------------------------------------
