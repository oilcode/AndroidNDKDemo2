//----------------------------------------------------------------
#include "SoMathMatrix4.h"
//----------------------------------------------------------------
void SoMathMatrix4::MakeIdentity()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeTranspose()
{
	SoMathMatrix4 kResult;
	kResult.m[0][0] = m[0][0];
	kResult.m[0][1] = m[1][0];
	kResult.m[0][2] = m[2][0];
	kResult.m[0][3] = m[3][0];

	kResult.m[1][0] = m[0][1];
	kResult.m[1][1] = m[1][1];
	kResult.m[1][2] = m[2][1];
	kResult.m[1][3] = m[3][1];

	kResult.m[2][0] = m[0][2];
	kResult.m[2][1] = m[1][2];
	kResult.m[2][2] = m[2][2];
	kResult.m[2][3] = m[3][2];

	kResult.m[3][0] = m[0][3];
	kResult.m[3][1] = m[1][3];
	kResult.m[3][2] = m[2][3];
	kResult.m[3][3] = m[3][3];
	*this = kResult;
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeInverse()
{
	SoMathMatrix4 kResult;
	float det_1 = 0.0f;
	float pos = 0.0f;
	float neg = 0.0f;
	float temp = m[0][0] * m[1][1] * m[2][2];
	if (temp >= 0.0f)
	{
		pos += temp;
	}
	else
	{
		neg += temp;
	}

	temp = m[1][0] * m[2][1] * m[0][2];
	if (temp >= 0.0f)
	{
		pos += temp;
	}
	else
	{
		neg += temp;
	}

	temp = m[2][0] * m[0][1] * m[1][2];
	if (temp >= 0.0f)
	{
		pos += temp;
	}
	else
	{
		neg += temp;
	}

	temp = -m[2][0] * m[1][1] * m[0][2];
	if (temp >= 0.0f)
	{
		pos += temp;
	}
	else
	{
		neg += temp;
	}

	temp = -m[1][0] * m[0][1] * m[2][2];
	if (temp >= 0.0f)
	{
		pos += temp;
	}
	else
	{
		neg += temp;
	}

	temp = -m[0][0] * m[2][1] * m[1][2];
	if (temp >= 0.0f)
	{
		pos += temp;
	}
	else
	{
		neg += temp;
	}

	det_1 = pos + neg;
	if (det_1 == 0.0f)
	{
		//error
		det_1 = SoMath_Min_ChuShu;
	}

	det_1 = 1.0f / det_1;

	kResult.m[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * det_1;
	kResult.m[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * det_1;
	kResult.m[0][2] = (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * det_1;

	kResult.m[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * det_1;
	kResult.m[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]) * det_1;
	kResult.m[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * det_1;

	kResult.m[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * det_1;
	kResult.m[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * det_1;
	kResult.m[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * det_1;

	kResult.m[3][0] = -(m[3][0] * kResult.m[0][0] + m[3][1] * kResult.m[1][0] + m[3][2] * kResult.m[2][0]);
	kResult.m[3][1] = -(m[3][0] * kResult.m[0][1] + m[3][1] * kResult.m[1][1] + m[3][2] * kResult.m[2][1]);
	kResult.m[3][2] = -(m[3][0] * kResult.m[0][2] + m[3][1] * kResult.m[1][2] + m[3][2] * kResult.m[2][2]);

	kResult.m[0][3] = 0.0f;
	kResult.m[1][3] = 0.0f;
	kResult.m[2][3] = 0.0f;
	kResult.m[3][3] = 1.0f;

	*this = kResult;
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeTranslation(float x, float y, float z)
{
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = x;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = y;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = z;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
#else
	m[0][0] = 1.0f;
	m[1][0] = 0.0f;
	m[2][0] = 0.0f;
	m[3][0] = x;

	m[0][1] = 0.0f;
	m[1][1] = 1.0f;
	m[2][1] = 0.0f;
	m[3][1] = y;

	m[0][2] = 0.0f;
	m[1][2] = 0.0f;
	m[2][2] = 1.0f;
	m[3][2] = z;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeScale(float x, float y, float z)
{
	m[0][0] = x;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = y;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = z;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeXRotate(float fRadian)
{
	float sinValue = sin(fRadian);
	float cosValue = cos(fRadian);
	//
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = cosValue;
	m[1][2] = sinValue;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = -sinValue;
	m[2][2] = cosValue;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
#else
	m[0][0] = 1.0f;
	m[1][0] = 0.0f;
	m[2][0] = 0.0f;
	m[3][0] = 0.0f;

	m[0][1] = 0.0f;
	m[1][1] = cosValue;
	m[2][1] = sinValue;
	m[3][1] = 0.0f;

	m[0][2] = 0.0f;
	m[1][2] = -sinValue;
	m[2][2] = cosValue;
	m[3][2] = 0.0f;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeYRotate(float fRadian)
{
	float sinValue = sin(fRadian);
	float cosValue = cos(fRadian);
	//
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = cosValue;
	m[0][1] = 0.0f;
	m[0][2] = -sinValue;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = sinValue;
	m[2][1] = 0.0f;
	m[2][2] = cosValue;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
#else
	m[0][0] = cosValue;
	m[1][0] = 0.0f;
	m[2][0] = -sinValue;
	m[3][0] = 0.0f;

	m[0][1] = 0.0f;
	m[1][1] = 1.0f;
	m[2][1] = 0.0f;
	m[3][1] = 0.0f;

	m[0][2] = sinValue;
	m[1][2] = 0.0f;
	m[2][2] = cosValue;
	m[3][2] = 0.0f;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeZRotate(float fRadian)
{
	float sinValue = sin(fRadian);
	float cosValue = cos(fRadian);
	//
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = cosValue;
	m[0][1] = sinValue;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = -sinValue;
	m[1][1] = cosValue;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
#else
	m[0][0] = cosValue;
	m[1][0] = sinValue;
	m[2][0] = 0.0f;
	m[3][0] = 0.0f;

	m[0][1] = -sinValue;
	m[1][1] = cosValue;
	m[2][1] = 0.0f;
	m[3][1] = 0.0f;

	m[0][2] = 0.0f;
	m[1][2] = 0.0f;
	m[2][2] = 1.0f;
	m[3][2] = 0.0f;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeAxisRotate(float fRadian, float fAxisX, float fAxisY, float fAxisZ)
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
	m[0][3] = 0.0f;

	m[1][0] = xym+zsin;
	m[1][1] = y2*omcs+cs;
	m[1][2] = yzm-xsin;
	m[1][3] = 0.0f;

	m[2][0] = xzm-ysin;
	m[2][1] = yzm+xsin;
	m[2][2] = z2*omcs+cs;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
#else
	m[0][0] = x2*omcs+cs;
	m[1][0] = xym-zsin;
	m[2][0] = xzm+ysin;
	m[3][0] = 0.0f;

	m[0][1] = xym+zsin;
	m[1][1] = y2*omcs+cs;
	m[2][1] = yzm-xsin;
	m[3][1] = 0.0f;

	m[0][2] = xzm-ysin;
	m[1][2] = yzm+xsin;
	m[2][2] = z2*omcs+cs;
	m[3][2] = 0.0f;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeEulerRotate(float fXRadian, float fYRadian, float fZRadian)
{
	SoMathMatrix4 kX, kY, kZ;
	kX.MakeXRotate(fXRadian);
	kY.MakeYRotate(fYRadian);
	kZ.MakeZRotate(fZRadian);
	*this = kX * (kY * kZ);
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeEulerRotateXZ(float fXRadian, float fZRadian)
{
	SoMathMatrix4 kX, kZ;
	kX.MakeXRotate(fXRadian);
	kZ.MakeZRotate(fZRadian);
	*this = kX * kZ;
}
//----------------------------------------------------------------
void SoMathMatrix4::MakePerspective(float width, float height, float nearPlane, float farPlane)
{
#ifdef SoMath_Matrix_RowMajor_DirectX

#else
	float n2 = 2.0f * nearPlane;
	float rcpnmf = 1.0f / (nearPlane - farPlane);

	m[0][0] = n2 / width;
	m[1][0] = 0.0f;
	m[2][0] = 0.0f;
	m[3][0] = 0.0f;

	m[0][1] = 0.0f;
	m[1][1] = n2 / height;
	m[2][1] = 0.0f;
	m[3][1] = 0.0f;

	m[0][2] = 0.0f;
	m[1][2] = 0.0f;
	m[2][2] = (farPlane + nearPlane) * rcpnmf;
	m[3][2] = farPlane * rcpnmf * n2;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = -1.0f;
	m[3][3] = 0.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeOrtho2D(float left, float top, float right, float bottom)
{
#ifdef SoMath_Matrix_RowMajor_DirectX

#else
	const float zNear = -1.0f;
	const float zFar = 1.0f;
	const float inv_z = 1.0f / (zFar - zNear);
	const float inv_y = 1.0f / (bottom - top);
	const float inv_x = 1.0f / (right - left);

	m[0][0] = 2.0f * inv_x;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 2.0f * inv_y;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = -2.0f * inv_z;
	m[2][3] = 0.0f;

	m[3][0] = -(right + left) * inv_x;
	m[3][1] = (top + bottom) * inv_y;
	m[3][2] = -(zFar + zNear) * inv_z;
	m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeLookTo(const SoMathFloat3& kEyePos, const SoMathFloat3& kForward, const SoMathFloat3& kRight, const SoMathFloat3& kUp)
{
#ifdef SoMath_Matrix_RowMajor_DirectX
	m[0][0] = kRight.x;
	m[0][1] = kRight.y;
	m[0][2] = kRight.z;

	m[1][0] = kUp.x;
	m[1][1] = kUp.y;
	m[1][2] = kUp.z;

	m[2][0] = -kForward.x;
	m[2][1] = -kForward.y;
	m[2][2] = -kForward.z;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;

	m[0][3] = -(kEyePos.x * m[0][0] + kEyePos.y * m[0][1] + kEyePos.z * m[0][2]);
	m[1][3] = -(kEyePos.x * m[1][0] + kEyePos.y * m[1][1] + kEyePos.z * m[1][2]);
	m[2][3] = -(kEyePos.x * m[2][0] + kEyePos.y * m[2][1] + kEyePos.z * m[2][2]);
	m[3][3] = 1.0f;
#else
	m[0][0] = kRight.x;
	m[1][0] = kRight.y;
	m[2][0] = kRight.z;

	m[0][1] = kUp.x;
	m[1][1] = kUp.y;
	m[2][1] = kUp.z;

	m[0][2] = -kForward.x;
	m[1][2] = -kForward.y;
	m[2][2] = -kForward.z;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;

    m[3][0] = -(kEyePos.x * m[0][0] + kEyePos.y * m[1][0] + kEyePos.z * m[2][0]);
    m[3][1] = -(kEyePos.x * m[0][1] + kEyePos.y * m[1][1] + kEyePos.z * m[2][1]);
    m[3][2] = -(kEyePos.x * m[0][2] + kEyePos.y * m[1][2] + kEyePos.z * m[2][2]);
    m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::MakeLookAt(const SoMathFloat3& kEyePos, const SoMathFloat3& kLookAt, const SoMathFloat3& kUp)
{
	SoMathFloat3 kForward = kLookAt - kEyePos;
	kForward.Unitize();
	SoMathFloat3 kRight = kForward.Cross(kUp);
	SoMathFloat3 kUp2 = kRight.Cross(kForward);

#ifdef SoMath_Matrix_RowMajor_DirectX
    m[0][0] = kRight.x;
	m[0][1] = kRight.y;
	m[0][2] = kRight.z;

	m[1][0] = kUp2.x;
	m[1][1] = kUp2.y;
	m[1][2] = kUp2.z;

	m[2][0] = -kForward.x;
	m[2][1] = -kForward.y;
	m[2][2] = -kForward.z;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;

	m[0][3] = -(kEyePos.x * m[0][0] + kEyePos.y * m[0][1] + kEyePos.z * m[0][2]);
	m[1][3] = -(kEyePos.x * m[1][0] + kEyePos.y * m[1][1] + kEyePos.z * m[1][2]);
	m[2][3] = -(kEyePos.x * m[2][0] + kEyePos.y * m[2][1] + kEyePos.z * m[2][2]);
	m[3][3] = 1.0f;
#else
	m[0][0] = kRight.x;
	m[1][0] = kRight.y;
	m[2][0] = kRight.z;

	m[0][1] = kUp2.x;
	m[1][1] = kUp2.y;
	m[2][1] = kUp2.z;

	m[0][2] = -kForward.x;
	m[1][2] = -kForward.y;
	m[2][2] = -kForward.z;

	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;

	m[3][0] = -(kEyePos.x * m[0][0] + kEyePos.y * m[1][0] + kEyePos.z * m[2][0]);
	m[3][1] = -(kEyePos.x * m[0][1] + kEyePos.y * m[1][1] + kEyePos.z * m[2][1]);
	m[3][2] = -(kEyePos.x * m[0][2] + kEyePos.y * m[1][2] + kEyePos.z * m[2][2]);
	m[3][3] = 1.0f;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::operator = (const SoMathMatrix4& kOther)
{
	m[0][0] = kOther.m[0][0];
	m[0][1] = kOther.m[0][1];
	m[0][2] = kOther.m[0][2];
	m[0][3] = kOther.m[0][3];

	m[1][0] = kOther.m[1][0];
	m[1][1] = kOther.m[1][1];
	m[1][2] = kOther.m[1][2];
	m[1][3] = kOther.m[1][3];

	m[2][0] = kOther.m[2][0];
	m[2][1] = kOther.m[2][1];
	m[2][2] = kOther.m[2][2];
	m[2][3] = kOther.m[2][3];

	m[3][0] = kOther.m[3][0];
	m[3][1] = kOther.m[3][1];
	m[3][2] = kOther.m[3][2];
	m[3][3] = kOther.m[3][3];
}
//----------------------------------------------------------------
SoMathFloat4 SoMathMatrix4::operator * (const SoMathFloat4& kVector) const
{
#ifdef SoMath_Matrix_RowMajor_DirectX
	float x = m[0][0] * kVector.x + m[0][1] * kVector.y + m[0][2] * kVector.z + m[0][3] * kVector.w;
	float y = m[1][0] * kVector.x + m[1][1] * kVector.y + m[1][2] * kVector.z + m[1][3] * kVector.w;
	float z = m[2][0] * kVector.x + m[2][1] * kVector.y + m[2][2] * kVector.z + m[2][3] * kVector.w;
	float w = m[3][0] * kVector.x + m[3][1] * kVector.y + m[3][2] * kVector.z + m[3][3] * kVector.w;
	return SoMathFloat4(x, y, z, w);
#else
    float x = m[0][0] * kVector.x + m[1][0] * kVector.y + m[2][0] * kVector.z + m[3][0] * kVector.w;
    float y = m[0][1] * kVector.x + m[1][1] * kVector.y + m[2][1] * kVector.z + m[3][1] * kVector.w;
    float z = m[0][2] * kVector.x + m[1][2] * kVector.y + m[2][2] * kVector.z + m[3][2] * kVector.w;
    float w = m[0][3] * kVector.x + m[1][3] * kVector.y + m[2][3] * kVector.z + m[3][3] * kVector.w;
    return SoMathFloat4(x, y, z, w);
#endif
}
//----------------------------------------------------------------
SoMathFloat4 operator * (const SoMathFloat4& kVector, const SoMathMatrix4& kMatrix)
{
#ifdef SoMath_Matrix_RowMajor_DirectX
	float x = kMatrix.m[0][0] * kVector.x + kMatrix.m[0][1] * kVector.y + kMatrix.m[0][2] * kVector.z + kMatrix.m[0][3] * kVector.w;
	float y = kMatrix.m[1][0] * kVector.x + kMatrix.m[1][1] * kVector.y + kMatrix.m[1][2] * kVector.z + kMatrix.m[1][3] * kVector.w;
	float z = kMatrix.m[2][0] * kVector.x + kMatrix.m[2][1] * kVector.y + kMatrix.m[2][2] * kVector.z + kMatrix.m[2][3] * kVector.w;
	float w = kMatrix.m[3][0] * kVector.x + kMatrix.m[3][1] * kVector.y + kMatrix.m[3][2] * kVector.z + kMatrix.m[3][3] * kVector.w;
	return SoMathFloat4(x, y, z, w);
#else
    float x = kMatrix.m[0][0] * kVector.x + kMatrix.m[1][0] * kVector.y + kMatrix.m[2][0] * kVector.z + kMatrix.m[3][0] * kVector.w;
    float y = kMatrix.m[0][1] * kVector.x + kMatrix.m[1][1] * kVector.y + kMatrix.m[2][1] * kVector.z + kMatrix.m[3][1] * kVector.w;
    float z = kMatrix.m[0][2] * kVector.x + kMatrix.m[1][2] * kVector.y + kMatrix.m[2][2] * kVector.z + kMatrix.m[3][2] * kVector.w;
    float w = kMatrix.m[0][3] * kVector.x + kMatrix.m[1][3] * kVector.y + kMatrix.m[2][3] * kVector.z + kMatrix.m[3][3] * kVector.w;
    return SoMathFloat4(x, y, z, w);
#endif
}
//----------------------------------------------------------------
SoMathMatrix4 SoMathMatrix4::operator * (const SoMathMatrix4& kOther) const
{
#ifdef SoMath_Matrix_RowMajor_DirectX
	SoMathMatrix4 kResult;
	kResult.m[0][0] = m[0][0]*kOther.m[0][0] + m[0][1]*kOther.m[1][0] + m[0][2]*kOther.m[2][0] + m[0][3]*kOther.m[3][0];
	kResult.m[1][0] = m[1][0]*kOther.m[0][0] + m[1][1]*kOther.m[1][0] + m[1][2]*kOther.m[2][0] + m[1][3]*kOther.m[3][0];
	kResult.m[2][0] = m[2][0]*kOther.m[0][0] + m[2][1]*kOther.m[1][0] + m[2][2]*kOther.m[2][0] + m[2][3]*kOther.m[3][0];
	kResult.m[3][0] = m[3][0]*kOther.m[0][0] + m[3][1]*kOther.m[1][0] + m[3][2]*kOther.m[2][0] + m[3][3]*kOther.m[3][0];
	//
	kResult.m[0][1] = m[0][0]*kOther.m[0][1] + m[0][1]*kOther.m[1][1] + m[0][2]*kOther.m[2][1] + m[0][3]*kOther.m[3][1];
	kResult.m[1][1] = m[1][0]*kOther.m[0][1] + m[1][1]*kOther.m[1][1] + m[1][2]*kOther.m[2][1] + m[1][3]*kOther.m[3][1];
	kResult.m[2][1] = m[2][0]*kOther.m[0][1] + m[2][1]*kOther.m[1][1] + m[2][2]*kOther.m[2][1] + m[2][3]*kOther.m[3][1];
	kResult.m[3][1] = m[3][0]*kOther.m[0][1] + m[3][1]*kOther.m[1][1] + m[3][2]*kOther.m[2][1] + m[3][3]*kOther.m[3][1];
	//
	kResult.m[0][2] = m[0][0]*kOther.m[0][2] + m[0][1]*kOther.m[1][2] + m[0][2]*kOther.m[2][2] + m[0][3]*kOther.m[3][2];
	kResult.m[1][2] = m[1][0]*kOther.m[0][2] + m[1][1]*kOther.m[1][2] + m[1][2]*kOther.m[2][2] + m[1][3]*kOther.m[3][2];
	kResult.m[2][2] = m[2][0]*kOther.m[0][2] + m[2][1]*kOther.m[1][2] + m[2][2]*kOther.m[2][2] + m[2][3]*kOther.m[3][2];
	kResult.m[3][2] = m[3][0]*kOther.m[0][2] + m[3][1]*kOther.m[1][2] + m[3][2]*kOther.m[2][2] + m[3][3]*kOther.m[3][2];
	//
	kResult.m[0][3] = m[0][0]*kOther.m[0][3] + m[0][1]*kOther.m[1][3] + m[0][2]*kOther.m[2][3] + m[0][3]*kOther.m[3][3];
	kResult.m[1][3] = m[1][0]*kOther.m[0][3] + m[1][1]*kOther.m[1][3] + m[1][2]*kOther.m[2][3] + m[1][3]*kOther.m[3][3];
	kResult.m[2][3] = m[2][0]*kOther.m[0][3] + m[2][1]*kOther.m[1][3] + m[2][2]*kOther.m[2][3] + m[2][3]*kOther.m[3][3];
	kResult.m[3][3] = m[3][0]*kOther.m[0][3] + m[3][1]*kOther.m[1][3] + m[3][2]*kOther.m[2][3] + m[3][3]*kOther.m[3][3];
	return kResult;
#else
    SoMathMatrix4 kResult;
    kResult.m[0][0] = m[0][0]*kOther.m[0][0] + m[1][0]*kOther.m[0][1] + m[2][0]*kOther.m[0][2] + m[3][0]*kOther.m[0][3];
    kResult.m[0][1] = m[0][1]*kOther.m[0][0] + m[1][1]*kOther.m[0][1] + m[2][1]*kOther.m[0][2] + m[3][1]*kOther.m[0][3];
    kResult.m[0][2] = m[0][2]*kOther.m[0][0] + m[1][2]*kOther.m[0][1] + m[2][2]*kOther.m[0][2] + m[3][2]*kOther.m[0][3];
    kResult.m[0][3] = m[0][3]*kOther.m[0][0] + m[1][3]*kOther.m[0][1] + m[2][3]*kOther.m[0][2] + m[3][3]*kOther.m[0][3];
    //
    kResult.m[1][0] = m[0][0]*kOther.m[1][0] + m[1][0]*kOther.m[1][1] + m[2][0]*kOther.m[1][2] + m[3][0]*kOther.m[1][3];
    kResult.m[1][1] = m[0][1]*kOther.m[1][0] + m[1][1]*kOther.m[1][1] + m[2][1]*kOther.m[1][2] + m[3][1]*kOther.m[1][3];
    kResult.m[1][2] = m[0][2]*kOther.m[1][0] + m[1][2]*kOther.m[1][1] + m[2][2]*kOther.m[1][2] + m[3][2]*kOther.m[1][3];
    kResult.m[1][3] = m[0][3]*kOther.m[1][0] + m[1][3]*kOther.m[1][1] + m[2][3]*kOther.m[1][2] + m[3][3]*kOther.m[1][3];
    //
    kResult.m[2][0] = m[0][0]*kOther.m[2][0] + m[1][0]*kOther.m[2][1] + m[2][0]*kOther.m[2][2] + m[3][0]*kOther.m[2][3];
    kResult.m[2][1] = m[0][1]*kOther.m[2][0] + m[1][1]*kOther.m[2][1] + m[2][1]*kOther.m[2][2] + m[3][1]*kOther.m[2][3];
    kResult.m[2][2] = m[0][2]*kOther.m[2][0] + m[1][2]*kOther.m[2][1] + m[2][2]*kOther.m[2][2] + m[3][2]*kOther.m[2][3];
    kResult.m[2][3] = m[0][3]*kOther.m[2][0] + m[1][3]*kOther.m[2][1] + m[2][3]*kOther.m[2][2] + m[3][3]*kOther.m[2][3];
    //
    kResult.m[3][0] = m[0][0]*kOther.m[3][0] + m[1][0]*kOther.m[3][1] + m[2][0]*kOther.m[3][2] + m[3][0]*kOther.m[3][3];
    kResult.m[3][1] = m[0][1]*kOther.m[3][0] + m[1][1]*kOther.m[3][1] + m[2][1]*kOther.m[3][2] + m[3][1]*kOther.m[3][3];
    kResult.m[3][2] = m[0][2]*kOther.m[3][0] + m[1][2]*kOther.m[3][1] + m[2][2]*kOther.m[3][2] + m[3][2]*kOther.m[3][3];
    kResult.m[3][3] = m[0][3]*kOther.m[3][0] + m[1][3]*kOther.m[3][1] + m[2][3]*kOther.m[3][2] + m[3][3]*kOther.m[3][3];
    return kResult;
#endif
}
//----------------------------------------------------------------
void SoMathMatrix4::operator *= (const SoMathMatrix4& kOther)
{
#ifdef SoMath_Matrix_RowMajor_DirectX
	SoMathMatrix4 kResult;
	kResult.m[0][0] = m[0][0]*kOther.m[0][0] + m[0][1]*kOther.m[1][0] + m[0][2]*kOther.m[2][0] + m[0][3]*kOther.m[3][0];
	kResult.m[1][0] = m[1][0]*kOther.m[0][0] + m[1][1]*kOther.m[1][0] + m[1][2]*kOther.m[2][0] + m[1][3]*kOther.m[3][0];
	kResult.m[2][0] = m[2][0]*kOther.m[0][0] + m[2][1]*kOther.m[1][0] + m[2][2]*kOther.m[2][0] + m[2][3]*kOther.m[3][0];
	kResult.m[3][0] = m[3][0]*kOther.m[0][0] + m[3][1]*kOther.m[1][0] + m[3][2]*kOther.m[2][0] + m[3][3]*kOther.m[3][0];
	//
	kResult.m[0][1] = m[0][0]*kOther.m[0][1] + m[0][1]*kOther.m[1][1] + m[0][2]*kOther.m[2][1] + m[0][3]*kOther.m[3][1];
	kResult.m[1][1] = m[1][0]*kOther.m[0][1] + m[1][1]*kOther.m[1][1] + m[1][2]*kOther.m[2][1] + m[1][3]*kOther.m[3][1];
	kResult.m[2][1] = m[2][0]*kOther.m[0][1] + m[2][1]*kOther.m[1][1] + m[2][2]*kOther.m[2][1] + m[2][3]*kOther.m[3][1];
	kResult.m[3][1] = m[3][0]*kOther.m[0][1] + m[3][1]*kOther.m[1][1] + m[3][2]*kOther.m[2][1] + m[3][3]*kOther.m[3][1];
	//
	kResult.m[0][2] = m[0][0]*kOther.m[0][2] + m[0][1]*kOther.m[1][2] + m[0][2]*kOther.m[2][2] + m[0][3]*kOther.m[3][2];
	kResult.m[1][2] = m[1][0]*kOther.m[0][2] + m[1][1]*kOther.m[1][2] + m[1][2]*kOther.m[2][2] + m[1][3]*kOther.m[3][2];
	kResult.m[2][2] = m[2][0]*kOther.m[0][2] + m[2][1]*kOther.m[1][2] + m[2][2]*kOther.m[2][2] + m[2][3]*kOther.m[3][2];
	kResult.m[3][2] = m[3][0]*kOther.m[0][2] + m[3][1]*kOther.m[1][2] + m[3][2]*kOther.m[2][2] + m[3][3]*kOther.m[3][2];
	//
	kResult.m[0][3] = m[0][0]*kOther.m[0][3] + m[0][1]*kOther.m[1][3] + m[0][2]*kOther.m[2][3] + m[0][3]*kOther.m[3][3];
	kResult.m[1][3] = m[1][0]*kOther.m[0][3] + m[1][1]*kOther.m[1][3] + m[1][2]*kOther.m[2][3] + m[1][3]*kOther.m[3][3];
	kResult.m[2][3] = m[2][0]*kOther.m[0][3] + m[2][1]*kOther.m[1][3] + m[2][2]*kOther.m[2][3] + m[2][3]*kOther.m[3][3];
	kResult.m[3][3] = m[3][0]*kOther.m[0][3] + m[3][1]*kOther.m[1][3] + m[3][2]*kOther.m[2][3] + m[3][3]*kOther.m[3][3];
	//
	*this = kResult;
#else
    SoMathMatrix4 kResult;
    kResult.m[0][0] = m[0][0]*kOther.m[0][0] + m[1][0]*kOther.m[0][1] + m[2][0]*kOther.m[0][2] + m[3][0]*kOther.m[0][3];
    kResult.m[0][1] = m[0][1]*kOther.m[0][0] + m[1][1]*kOther.m[0][1] + m[2][1]*kOther.m[0][2] + m[3][1]*kOther.m[0][3];
    kResult.m[0][2] = m[0][2]*kOther.m[0][0] + m[1][2]*kOther.m[0][1] + m[2][2]*kOther.m[0][2] + m[3][2]*kOther.m[0][3];
    kResult.m[0][3] = m[0][3]*kOther.m[0][0] + m[1][3]*kOther.m[0][1] + m[2][3]*kOther.m[0][2] + m[3][3]*kOther.m[0][3];
    //
    kResult.m[1][0] = m[0][0]*kOther.m[1][0] + m[1][0]*kOther.m[1][1] + m[2][0]*kOther.m[1][2] + m[3][0]*kOther.m[1][3];
    kResult.m[1][1] = m[0][1]*kOther.m[1][0] + m[1][1]*kOther.m[1][1] + m[2][1]*kOther.m[1][2] + m[3][1]*kOther.m[1][3];
    kResult.m[1][2] = m[0][2]*kOther.m[1][0] + m[1][2]*kOther.m[1][1] + m[2][2]*kOther.m[1][2] + m[3][2]*kOther.m[1][3];
    kResult.m[1][3] = m[0][3]*kOther.m[1][0] + m[1][3]*kOther.m[1][1] + m[2][3]*kOther.m[1][2] + m[3][3]*kOther.m[1][3];
    //
    kResult.m[2][0] = m[0][0]*kOther.m[2][0] + m[1][0]*kOther.m[2][1] + m[2][0]*kOther.m[2][2] + m[3][0]*kOther.m[2][3];
    kResult.m[2][1] = m[0][1]*kOther.m[2][0] + m[1][1]*kOther.m[2][1] + m[2][1]*kOther.m[2][2] + m[3][1]*kOther.m[2][3];
    kResult.m[2][2] = m[0][2]*kOther.m[2][0] + m[1][2]*kOther.m[2][1] + m[2][2]*kOther.m[2][2] + m[3][2]*kOther.m[2][3];
    kResult.m[2][3] = m[0][3]*kOther.m[2][0] + m[1][3]*kOther.m[2][1] + m[2][3]*kOther.m[2][2] + m[3][3]*kOther.m[2][3];
    //
    kResult.m[3][0] = m[0][0]*kOther.m[3][0] + m[1][0]*kOther.m[3][1] + m[2][0]*kOther.m[3][2] + m[3][0]*kOther.m[3][3];
    kResult.m[3][1] = m[0][1]*kOther.m[3][0] + m[1][1]*kOther.m[3][1] + m[2][1]*kOther.m[3][2] + m[3][1]*kOther.m[3][3];
    kResult.m[3][2] = m[0][2]*kOther.m[3][0] + m[1][2]*kOther.m[3][1] + m[2][2]*kOther.m[3][2] + m[3][2]*kOther.m[3][3];
    kResult.m[3][3] = m[0][3]*kOther.m[3][0] + m[1][3]*kOther.m[3][1] + m[2][3]*kOther.m[3][2] + m[3][3]*kOther.m[3][3];
    //
    *this = kResult;
#endif
}
//----------------------------------------------------------------
