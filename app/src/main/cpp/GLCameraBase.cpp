//-----------------------------------------------------------------------
#include "GLCameraBase.h"
//-----------------------------------------------------------------------
GLCameraBase::GLCameraBase()
:m_kPosition(0.0f, 0.0f, 0.0f)
,m_fPitch(0.0f)
,m_fYaw(0.0f)
,m_kRight(1.0f, 0.0f, 0.0f)
,m_kUp(0.0f, 0.0f, 1.0f)
,m_kLook(0.0f, 1.0f, 0.0f)
,m_bShouldUpdateViewMatrix(true)
{
	m_matView.MakeIdentity();
	m_matProjection.MakeIdentity();
	m_matProjView.MakeIdentity();
}
//-----------------------------------------------------------------------
GLCameraBase::~GLCameraBase()
{

}
//-----------------------------------------------------------------------
void GLCameraBase::SetPosition(float x, float y, float z)
{
	m_kPosition.x = x;
	m_kPosition.y = y;
	m_kPosition.z = z;
	m_bShouldUpdateViewMatrix = true;
}
//-----------------------------------------------------------------------
void GLCameraBase::SetPitch(float fPitch)
{
	SetDeltaPitch(fPitch - m_fPitch);
}
//-----------------------------------------------------------------------
void GLCameraBase::SetYaw(float fYaw)
{
	SetDeltaYaw(fYaw - m_fYaw);
}
//-----------------------------------------------------------------------
void GLCameraBase::SetPitchYaw(float fPitch, float fYaw)
{
	SetDeltaPitchYaw(fPitch - m_fPitch, fYaw - m_fYaw);
}
//-----------------------------------------------------------------------
void GLCameraBase::SetDeltaMove(float fDeltaByRightDir, float fDeltaByLookDir)
{
	if (SoMath_IsFloatZero(fDeltaByRightDir) == false)
	{
		m_kPosition += m_kRight * fDeltaByRightDir;
		m_bShouldUpdateViewMatrix = true;
	}
	if (SoMath_IsFloatZero(fDeltaByLookDir) == false)
	{
		m_kPosition += m_kLook * fDeltaByLookDir;
		m_bShouldUpdateViewMatrix = true;
	}
}
//-----------------------------------------------------------------------
void GLCameraBase::SetDeltaPitch(float deltaPitch)
{
	if (SoMath_IsFloatZero(deltaPitch) == false)
	{
		m_fPitch += deltaPitch;
		MakeRotate();
	}
}
//-----------------------------------------------------------------------
void GLCameraBase::SetDeltaYaw(float deltaYaw)
{
	if (SoMath_IsFloatZero(deltaYaw) == false)
	{
		m_fYaw += deltaYaw;
		MakeRotate();
	}
}
//-----------------------------------------------------------------------
void GLCameraBase::SetDeltaPitchYaw(float deltaPitch, float deltaYaw)
{
	if (SoMath_IsFloatZero(deltaPitch) == false || SoMath_IsFloatZero(deltaYaw) == false)
	{
		m_fPitch += deltaPitch;
		m_fYaw += deltaYaw;
		MakeRotate();
	}
}
//-----------------------------------------------------------------------
void GLCameraBase::SetFrustum(float fWidth, float fHeight, float fNearZ, float fFarZ)
{
    m_matProjection.MakePerspective(fWidth, fHeight, fNearZ, fFarZ);
}
//-----------------------------------------------------------------------
void GLCameraBase::UpdateViewMatrix()
{
	if (m_bShouldUpdateViewMatrix)
	{
		m_bShouldUpdateViewMatrix = false;
		//
        m_matView.MakeLookTo(m_kPosition, m_kLook, m_kRight, m_kUp);
        m_matProjView = m_matProjection * m_matView;
	}
}
//-----------------------------------------------------------------------
void GLCameraBase::MakeRotate()
{
    SoMathMatrix4 kRotatePitch;
    kRotatePitch.MakeXRotate(m_fPitch);
    SoMathMatrix4 kRotateYaw;
    kRotateYaw.MakeZRotate(m_fYaw);

	SoMathFloat4 vecRight(1.0f, 0.0f, 0.0f, 0.0f);
    SoMathFloat4 vecUp(0.0f, 0.0f, 1.0f, 0.0f);

    vecRight = vecRight * kRotateYaw;
    vecUp = vecUp * kRotatePitch;
    vecUp = vecUp * kRotateYaw;

    m_kRight = vecRight.GetFloat3();
    m_kUp = vecUp.GetFloat3();
    m_kLook = m_kUp.Cross(m_kRight);

	m_bShouldUpdateViewMatrix = true;
}
//-----------------------------------------------------------------------
