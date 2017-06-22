//----------------------------------------------------------------
#include "SoMathMatrix3.h"
//----------------------------------------------------------------
void SoMathMatrix3::MakeIdentity()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
}
//----------------------------------------------------------------
void SoMathMatrix3::MakeXRotate(float fRadian)
{
	float sinValue = sin(fRadian);
	float cosValue = cos(fRadian);
	//
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = -cosValue;
	m[1][2] = -sinValue;
	m[2][0] = 0.0f;
	m[2][1] = sinValue;
	m[2][2] = -cosValue;
#else
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = cosValue;
	m[1][2] = sinValue;
	m[2][0] = 0.0f;
	m[2][1] = -sinValue;
	m[2][2] = cosValue;
#endif

}
//----------------------------------------------------------------
void SoMathMatrix3::MakeYRotate(float fRadian)
{
	float sinValue = sin(fRadian);
	float cosValue = cos(fRadian);
	//
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = -cosValue;
	m[0][1] = 0.0f;
	m[0][2] = sinValue;
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[2][0] = -sinValue;
	m[2][1] = 0.0f;
	m[2][2] = -cosValue;
#else
	m[0][0] = cosValue;
	m[0][1] = 0.0f;
	m[0][2] = -sinValue;
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[2][0] = sinValue;
	m[2][1] = 0.0f;
	m[2][2] = cosValue;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix3::MakeZRotate(float fRadian)
{
	float sinValue = sin(fRadian);
	float cosValue = cos(fRadian);
	//
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = -cosValue;
	m[0][1] = -sinValue;
	m[0][2] = 0.0f;
	m[1][0] = sinValue;
	m[1][1] = -cosValue;
	m[1][2] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
#else
	m[0][0] = cosValue;
	m[0][1] = sinValue;
	m[0][2] = 0.0f;
	m[1][0] = -sinValue;
	m[1][1] = cosValue;
	m[1][2] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix3::MakeAxisRotate(float fRadian, float fAxisX, float fAxisY, float fAxisZ)
{
	float sn = sin(fRadian);
	float cs = cos(fRadian);
	float omcs = 1.0f-cs;

	float x2 = fAxisX*fAxisX;
	float y2 = fAxisY*fAxisY;
	float z2 = fAxisZ*fAxisZ;
	float xym = fAxisX*fAxisY*omcs;
	float xzm = fAxisX*fAxisZ*omcs;
	float yzm = fAxisY*fAxisZ*omcs;
	float xsin = fAxisX*sn;
	float ysin = fAxisY*sn;
	float zsin = fAxisZ*sn;

#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = x2*omcs+cs;
	m[0][1] = xym-zsin;
	m[0][2] = xzm+ysin;
	m[1][0] = xym+zsin;
	m[1][1] = y2*omcs+cs;
	m[1][2] = yzm-xsin;
	m[2][0] = xzm-ysin;
	m[2][1] = yzm+xsin;
	m[2][2] = z2*omcs+cs;
#else
	m[0][0] = x2*omcs+cs;
	m[0][1] = xym+zsin;
	m[0][2] = xzm-ysin;
	m[1][0] = xym-zsin;
	m[1][1] = y2*omcs+cs;
	m[1][2] = yzm+xsin;
	m[2][0] = xzm+ysin;
	m[2][1] = yzm-xsin;
	m[2][2] = z2*omcs+cs;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix3::MakeEulerRotate(float fXRadian, float fYRadian, float fZRadian)
{
	SoMathMatrix3 kX, kY, kZ;
	kX.MakeXRotate(fXRadian);
	kY.MakeYRotate(fYRadian);
	kZ.MakeZRotate(fZRadian);
	*this = kX * (kY * kZ);
}
//----------------------------------------------------------------
void SoMathMatrix3::MakeEulerRotateXZ(float fXRadian, float fZRadian)
{
	SoMathMatrix3 kX, kZ;
	kX.MakeXRotate(fXRadian);
	kZ.MakeZRotate(fZRadian);
	*this = kX * kZ;
}
//----------------------------------------------------------------
void SoMathMatrix3::operator = (const SoMathMatrix3& kOther)
{
	m[0][0] = kOther.m[0][0];
	m[0][1] = kOther.m[0][1];
	m[0][2] = kOther.m[0][2];
	m[1][0] = kOther.m[1][0];
	m[1][1] = kOther.m[1][1];
	m[1][2] = kOther.m[1][2];
	m[2][0] = kOther.m[2][0];
	m[2][1] = kOther.m[2][1];
	m[2][2] = kOther.m[2][2];
}
//----------------------------------------------------------------
SoMathFloat3 SoMathMatrix3::operator * (const SoMathFloat3& kVector) const
{
	float x = m[0][0] * kVector.x + m[0][1] * kVector.y + m[0][2] * kVector.z;
	float y = m[1][0] * kVector.x + m[1][1] * kVector.y + m[1][2] * kVector.z;
	float z = m[2][0] * kVector.x + m[2][1] * kVector.y + m[2][2] * kVector.z;
	return SoMathFloat3(x, y, z);
}
//----------------------------------------------------------------
SoMathFloat3 operator * (const SoMathFloat3& kVector, const SoMathMatrix3& kMatrix)
{
	float x = kMatrix.m[0][0] * kVector.x + kMatrix.m[0][1] * kVector.y + kMatrix.m[0][2] * kVector.z;
	float y = kMatrix.m[1][0] * kVector.x + kMatrix.m[1][1] * kVector.y + kMatrix.m[1][2] * kVector.z;
	float z = kMatrix.m[2][0] * kVector.x + kMatrix.m[2][1] * kVector.y + kMatrix.m[2][2] * kVector.z;
	return SoMathFloat3(x, y, z);
}
//----------------------------------------------------------------
SoMathMatrix3 SoMathMatrix3::operator * (const SoMathMatrix3& kOther) const
{
	SoMathMatrix3 kResult;
	kResult.m[0][0] = m[0][0]*kOther.m[0][0] + m[0][1]*kOther.m[1][0] + m[0][2]*kOther.m[2][0];
	kResult.m[1][0] = m[1][0]*kOther.m[0][0] + m[1][1]*kOther.m[1][0] + m[1][2]*kOther.m[2][0];
	kResult.m[2][0] = m[2][0]*kOther.m[0][0] + m[2][1]*kOther.m[1][0] + m[2][2]*kOther.m[2][0];
	//
	kResult.m[0][1] = m[0][0]*kOther.m[0][1] + m[0][1]*kOther.m[1][1] + m[0][2]*kOther.m[2][1];
	kResult.m[1][1] = m[1][0]*kOther.m[0][1] + m[1][1]*kOther.m[1][1] + m[1][2]*kOther.m[2][1];
	kResult.m[2][1] = m[2][0]*kOther.m[0][1] + m[2][1]*kOther.m[1][1] + m[2][2]*kOther.m[2][1];
	//
	kResult.m[0][2] = m[0][0]*kOther.m[0][2] + m[0][1]*kOther.m[1][2] + m[0][2]*kOther.m[2][2];
	kResult.m[1][2] = m[1][0]*kOther.m[0][2] + m[1][1]*kOther.m[1][2] + m[1][2]*kOther.m[2][2];
	kResult.m[2][2] = m[2][0]*kOther.m[0][2] + m[2][1]*kOther.m[1][2] + m[2][2]*kOther.m[2][2];
	return kResult;
}
//----------------------------------------------------------------
void SoMathMatrix3::operator *= (const SoMathMatrix3& kOther)
{
	SoMathMatrix3 kResult;
	kResult.m[0][0] = m[0][0]*kOther.m[0][0] + m[0][1]*kOther.m[1][0] + m[0][2]*kOther.m[2][0];
	kResult.m[1][0] = m[1][0]*kOther.m[0][0] + m[1][1]*kOther.m[1][0] + m[1][2]*kOther.m[2][0];
	kResult.m[2][0] = m[2][0]*kOther.m[0][0] + m[2][1]*kOther.m[1][0] + m[2][2]*kOther.m[2][0];
	//
	kResult.m[0][1] = m[0][0]*kOther.m[0][1] + m[0][1]*kOther.m[1][1] + m[0][2]*kOther.m[2][1];
	kResult.m[1][1] = m[1][0]*kOther.m[0][1] + m[1][1]*kOther.m[1][1] + m[1][2]*kOther.m[2][1];
	kResult.m[2][1] = m[2][0]*kOther.m[0][1] + m[2][1]*kOther.m[1][1] + m[2][2]*kOther.m[2][1];
	//
	kResult.m[0][2] = m[0][0]*kOther.m[0][2] + m[0][1]*kOther.m[1][2] + m[0][2]*kOther.m[2][2];
	kResult.m[1][2] = m[1][0]*kOther.m[0][2] + m[1][1]*kOther.m[1][2] + m[1][2]*kOther.m[2][2];
	kResult.m[2][2] = m[2][0]*kOther.m[0][2] + m[2][1]*kOther.m[1][2] + m[2][2]*kOther.m[2][2];
	//
	*this = kResult;
}
//----------------------------------------------------------------
