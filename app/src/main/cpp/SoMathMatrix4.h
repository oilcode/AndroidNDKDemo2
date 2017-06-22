//----------------------------------------------------------------
#ifndef _SoMathMatrix4_h_
#define _SoMathMatrix4_h_
//----------------------------------------------------------------
#include "SoMathFloat3.h"
#include "SoMathFloat4.h"
//----------------------------------------------------------------
class SoMathMatrix4
{
public:
	float m[4][4];

public:
	SoMathMatrix4();
	~SoMathMatrix4();

	void MakeIdentity();
	void MakeTranspose();
	void MakeInverse();

	void MakeTranslation(float x, float y, float z);
	void MakeScale(float x, float y, float z);

	void MakeXRotate(float fRadian);
	void MakeYRotate(float fRadian);
	void MakeZRotate(float fRadian);
	void MakeAxisRotate(float fRadian, float fAxisX, float fAxisY, float fAxisZ);
	void MakeEulerRotate(float fXRadian, float fYRadian, float fZRadian);
	void MakeEulerRotateXZ(float fXRadian, float fZRadian);

	void MakePerspective(float width, float height, float nearPlane, float farPlane);
	void MakeOrtho2D(float left, float top, float right, float bottom);
	void MakeLookTo(const SoMathFloat3& kEyePos, const SoMathFloat3& kForward, const SoMathFloat3& kRight, const SoMathFloat3& kUp);
	void MakeLookAt(const SoMathFloat3& kEyePos, const SoMathFloat3& kLookAt, const SoMathFloat3& kUp);

	void operator = (const SoMathMatrix4& kOther);
	//Vector = Matrix * Vector;
	SoMathFloat4 operator * (const SoMathFloat4& kVector) const;
	//Vector = Vector * Matrix;
	friend SoMathFloat4 operator * (const SoMathFloat4& kVector, const SoMathMatrix4& kMatrix);
	//Matrix = Matrix * Matrix;
	SoMathMatrix4 operator * (const SoMathMatrix4& kOther) const;
	//Matrix *= Matrix;
	void operator *= (const SoMathMatrix4& kOther);

};
//----------------------------------------------------------------
inline SoMathMatrix4::SoMathMatrix4()
{
	//do nothing
}
//----------------------------------------------------------------
inline SoMathMatrix4::~SoMathMatrix4()
{
	//do nothing
}
//----------------------------------------------------------------
#endif //_SoMathMatrix4_h_
//----------------------------------------------------------------
