//----------------------------------------------------------------
#ifndef _SoMath_h_
#define _SoMath_h_
//----------------------------------------------------------------
#include "SoMathBase.h"
#include "SoMathInt2.h"
#include "SoMathInt3.h"
#include "SoMathFloat2.h"
#include "SoMathFloat3.h"
#include "SoMathFloat4.h"
#include "SoMathMatrix3.h"
#include "SoMathMatrix4.h"
//----------------------------------------------------------------
//Quaternion = w + xi + yj + zk
struct SoMathQuaternion
{
	float x;
	float y;
	float z;
	float w;
};
//----------------------------------------------------------------
void SoMath_QuaternionRotate(const SoMathFloat3* pAxis, float fRadian, const SoMathFloat3* pSrcVector, SoMathFloat3* pResultVector, bool bNormalize);
//----------------------------------------------------------------
#endif //_SoMath_h_
//----------------------------------------------------------------
