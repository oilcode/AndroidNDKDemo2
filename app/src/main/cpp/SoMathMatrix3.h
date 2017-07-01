//----------------------------------------------------------------
#ifndef _SoMathMatrix3_h_
#define _SoMathMatrix3_h_
//----------------------------------------------------------------
#include "SoMathFloat3.h"
//----------------------------------------------------------------
class SoMathMatrix3
{
public:
	float m[3][3];

public:
	SoMathMatrix3();
	~SoMathMatrix3();

	void MakeIdentity();
	void MakeTranspose();
	void MakeInverse();

	void MakeXRotate(float fRadian);
	void MakeYRotate(float fRadian);
	void MakeZRotate(float fRadian);
	void MakeAxisRotate(float fRadian, float fAxisX, float fAxisY, float fAxisZ);
	void MakeEulerRotate(float fXRadian, float fYRadian, float fZRadian);
	void MakeEulerRotateXZ(float fXRadian, float fZRadian);

	void operator = (const SoMathMatrix3& kOther);
	//Vector = Matrix * Vector;
	SoMathFloat3 operator * (const SoMathFloat3& kVector) const;
	//Vector = Vector * Matrix;
	friend SoMathFloat3 operator * (const SoMathFloat3& kVector, const SoMathMatrix3& kMatrix);
	//Matrix = Matrix * Matrix;
	SoMathMatrix3 operator * (const SoMathMatrix3& kOther) const;
	//Matrix *= Matrix;
	void operator *= (const SoMathMatrix3& kOther);
};
//----------------------------------------------------------------
inline SoMathMatrix3::SoMathMatrix3()
{
	//do nothing
}
//----------------------------------------------------------------
inline SoMathMatrix3::~SoMathMatrix3()
{
	//do nothing
}
//----------------------------------------------------------------
#endif //_SoMathMatrix3_h_
//----------------------------------------------------------------
