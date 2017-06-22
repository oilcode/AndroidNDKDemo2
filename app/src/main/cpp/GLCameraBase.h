//-----------------------------------------------------------------------
#ifndef _GLCameraBase_h_
#define _GLCameraBase_h_
//-----------------------------------------------------------------------
#include "GLBaseInclude.h"
//-----------------------------------------------------------------------
class GLCameraBase
{
public:
	GLCameraBase();
	~GLCameraBase();

	void SetPosition(float x, float y, float z);
	void SetPitch(float fPitch);
	void SetYaw(float fYaw);
	void SetPitchYaw(float fPitch, float fYaw);

	void SetDeltaMove(float fDeltaByRightDir, float fDeltaByLookDir);
	void SetDeltaPitch(float deltaPitch);
	void SetDeltaYaw(float deltaYaw);
	void SetDeltaPitchYaw(float deltaPitch, float deltaYaw);

	void SetFrustum(float fWidth, float fHeight, float fNearZ, float fFarZ);

	void UpdateViewMatrix();

	const SoMathFloat3& GetPosition() const;
	float GetPitch() const;
	float GetYaw() const;
	const SoMathFloat3& GetRight() const;
	const SoMathFloat3& GetUp() const;
	const SoMathFloat3& GetLook() const;
	const SoMathMatrix4& GetMatView() const;
	const SoMathMatrix4& GetMatProj() const;
	const SoMathMatrix4& GetMatProjView() const;

protected:
	void MakeRotate();

protected:
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    SoMathFloat3 m_kPosition;
	float m_fPitch;
	float m_fYaw;
	bool m_bShouldUpdateViewMatrix;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    SoMathFloat3 m_kRight;
    SoMathFloat3 m_kUp;
    SoMathFloat3 m_kLook;
	SoMathMatrix4 m_matView;
    SoMathMatrix4 m_matProjection;
    SoMathMatrix4 m_matProjView;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
//-----------------------------------------------------------------------
inline const SoMathFloat3& GLCameraBase::GetPosition() const
{
	return m_kPosition;
}
//-----------------------------------------------------------------------
inline float GLCameraBase::GetPitch() const
{
	return m_fPitch;
}
//-----------------------------------------------------------------------
inline float GLCameraBase::GetYaw() const
{
	return m_fYaw;
}
//-----------------------------------------------------------------------
inline const SoMathFloat3& GLCameraBase::GetRight() const
{
	return m_kRight;
}
//-----------------------------------------------------------------------
inline const SoMathFloat3& GLCameraBase::GetUp() const
{
	return m_kUp;
}
//-----------------------------------------------------------------------
inline const SoMathFloat3& GLCameraBase::GetLook() const
{
	return m_kLook;
}
//-----------------------------------------------------------------------
inline const SoMathMatrix4& GLCameraBase::GetMatView() const
{
	return m_matView;
}
//-----------------------------------------------------------------------
inline const SoMathMatrix4& GLCameraBase::GetMatProj() const
{
	return m_matProjection;
}
//-----------------------------------------------------------------------
inline const SoMathMatrix4& GLCameraBase::GetMatProjView() const
{
	return m_matProjView;
}
//-----------------------------------------------------------------------
#endif //_GLCameraBase_h_
//-----------------------------------------------------------------------
