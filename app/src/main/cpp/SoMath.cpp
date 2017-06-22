//----------------------------------------------------------------
#include "SoMath.h"
//----------------------------------------------------------------
void SoMath_QuaternionRotate(const SoMathFloat3* pAxis, float fRadian, const SoMathFloat3* pSrcVector, SoMathFloat3* pResultVector, bool bNormalize)
{
	//Q = w + xi + yj + zk
	const float fHalfRadian = fRadian * 0.5f;
	float fCos, fSin, fCosT, fSinT;
	SoMath_Cos(fHalfRadian, fCos);
	SoMath_Sin(fHalfRadian, fSin);
	fCosT = fCos; //SoMath_Cos(-fHalfRadian, fCosT);
	fSinT = -fSin; //SoMath_Sin(-fHalfRadian, fSinT);
	//QuaA
	float fQuaA_w = fCos;
	float fQuaA_x = fSin * pAxis->x;
	float fQuaA_y = fSin * pAxis->y;
	float fQuaA_z = fSin * pAxis->z;
	//QuaB
	float fQuaB_w = fCosT;
	float fQuaB_x = fSinT * pAxis->x;
	float fQuaB_y = fSinT * pAxis->y;
	float fQuaB_z = fSinT * pAxis->z;
	//
	//QuaP = (0.0f, Src.x, Src.y, Src.z)
	//
	//QuaB * QuaP
	float fQuaBP_w = - fQuaB_x*pSrcVector->x - fQuaB_y*pSrcVector->y - fQuaB_z*pSrcVector->z;
	float fQuaBP_x =   fQuaB_w*pSrcVector->x + fQuaB_y*pSrcVector->z - fQuaB_z*pSrcVector->y;
	float fQuaBP_y =   fQuaB_w*pSrcVector->y - fQuaB_x*pSrcVector->z + fQuaB_z*pSrcVector->x;
	float fQuaBP_z =   fQuaB_w*pSrcVector->z + fQuaB_x*pSrcVector->y - fQuaB_y*pSrcVector->x;
	//
	//quaBP * QuaA
	float fResultX = fQuaBP_w*fQuaA_x + fQuaBP_x*fQuaA_w + fQuaBP_y*fQuaA_z - fQuaBP_z*fQuaA_y;
	float fResultY = fQuaBP_w*fQuaA_y - fQuaBP_x*fQuaA_z + fQuaBP_y*fQuaA_w + fQuaBP_z*fQuaA_x;
	float fResultZ = fQuaBP_w*fQuaA_z + fQuaBP_x*fQuaA_y - fQuaBP_y*fQuaA_x + fQuaBP_z*fQuaA_w;
	//
	if (bNormalize)
	{
		float f1 = fResultX*fResultX + fResultY*fResultY + fResultZ*fResultZ;
		float f2;
		SoMath_InvSqrt(f1, f2);
		fResultX *= f2;
		fResultY *= f2;
		fResultZ *= f2;
	}
	//
	pResultVector->x = fResultX;
	pResultVector->y = fResultY;
	pResultVector->z = fResultZ;
}
//----------------------------------------------------------------
