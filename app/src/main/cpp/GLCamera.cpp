//-----------------------------------------------------------------------
#include "GLCamera.h"
#include "GLManager.h"
//-----------------------------------------------------------------------
GLCamera* GLCamera::ms_pInstance = NULL;
//-----------------------------------------------------------------------
bool GLCamera::CreateCamera()
{
	bool br = true;
	if (ms_pInstance == NULL)
	{
		ms_pInstance = new GLCamera;
		if (ms_pInstance && ms_pInstance->InitCamera())
		{
			br = true;
		}
		else
		{
			ReleaseCamera();
			br = false;
		}
	}
	return false;
}
//-----------------------------------------------------------------------
void GLCamera::ReleaseCamera()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = NULL;
	}
}
//-----------------------------------------------------------------------
GLCamera::GLCamera()
:m_CameraMode(CameraMode_Free)
,m_nMouseRightKeyDown(0)
,m_nLastCursorPosX(0)
,m_nLastCursorPosY(0)
,m_nLastMousePosX(0)
,m_nLastMousePosY(0)
,m_kFocusPos(0.0f, 0.0f, 0.0f)
,m_fFocusDistance(800.0f)
{

}
//-----------------------------------------------------------------------
GLCamera::~GLCamera()
{
	ClearCamera();
}
//-----------------------------------------------------------------------
bool GLCamera::InitCamera()
{
	int nWidth = 0;
	int nHeight = 0;
	GLManager::Get()->GetResolution(&nWidth, &nHeight);
	const float width = (float)nWidth;
	const float height = (float)nHeight;
	SetFrustumFov(SoMath_PI*0.25f, width/height, 1.0f, 1000000.0f);
	//
	SetPosition(-70.0f, -70.0f, -70.0f);
	SetPitchYaw(0.7f, -0.7f);
	return true;
}
//-----------------------------------------------------------------------
void GLCamera::ClearCamera()
{
	// do nothing
}
//-----------------------------------------------------------------------
void GLCamera::ProcessInputEvent(stInputEvent* pInputEvent)
{

}
//-----------------------------------------------------------------------
void GLCamera::UpdateFreeMove(float fDeltaTime)
{

}
//-----------------------------------------------------------------------
void GLCamera::SetFocusPos(float x, float y, float z)
{
	if (m_CameraMode == CameraMode_Focus)
	{
		m_kFocusPos.x = x;
		m_kFocusPos.y = y;
		m_kFocusPos.z = z;

		//m_kPosition = m_kFocusPos - m_kLook * m_fFocusDistance
		float newPosX = x - m_kLook.x * m_fFocusDistance;
		float newPosY = y - m_kLook.y * m_fFocusDistance;
		float newPosZ = z - m_kLook.z * m_fFocusDistance;
		SetPosition(newPosX, newPosY, newPosZ);
	}
}
//-----------------------------------------------------------------------
void GLCamera::SetFocusDistance(float fDistance)
{
	if (m_CameraMode == CameraMode_Focus)
	{
		SetFocusDeltaDistance(fDistance - m_fFocusDistance);
	}
}
//-----------------------------------------------------------------------
void GLCamera::SetFocusDeltaDistance(float deltaDistance)
{
	if (m_CameraMode == CameraMode_Focus)
	{
		if (SoMath_IsFloatZero(deltaDistance) == false)
		{
			m_fFocusDistance += deltaDistance;

			//m_kPosition = m_kFocusPos - m_kLook * m_fFocusDistance
			float newPosX = m_kFocusPos.x - m_kLook.x * m_fFocusDistance;
			float newPosY = m_kFocusPos.y - m_kLook.y * m_fFocusDistance;
			float newPosZ = m_kFocusPos.z - m_kLook.z * m_fFocusDistance;
			SetPosition(newPosX, newPosY, newPosZ);
		}
	}
}
//-----------------------------------------------------------------------
