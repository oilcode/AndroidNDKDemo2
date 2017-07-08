//-----------------------------------------------------------------------
#ifndef _SoD3DCamera_h_
#define _SoD3DCamera_h_
//-----------------------------------------------------------------------
#include "GLCameraBase.h"
//-----------------------------------------------------------------------
struct stInputEvent;
//-----------------------------------------------------------------------
class GLCamera : public GLCameraBase
{
public:
	enum eCameraMode
	{
		CameraMode_Free,
		CameraMode_Focus,
	};

public:
	static bool CreateCamera();
	static void ReleaseCamera();
	static GLCamera* Get();

	void SetCameraMode(eCameraMode newMode);
	eCameraMode GetCameraMode() const;

	void ProcessInputEvent(stInputEvent* pInputEvent);
	void UpdateFreeMove(float fDeltaTime);

	void SetFocusPos(float x, float y, float z);
	void SetFocusDistance(float fDistance);
	void SetFocusDeltaDistance(float deltaDistance);

private:
	GLCamera();
	~GLCamera();
	bool InitCamera();
	void ClearCamera();

private:
	static GLCamera* ms_pInstance;
	eCameraMode m_CameraMode;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	int m_nMouseRightKeyDown;
	int m_nLastCursorPosX;
	int m_nLastCursorPosY;
	int m_nLastMousePosX;
	int m_nLastMousePosY;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	SoMathFloat3 m_kFocusPos;
	float m_fFocusDistance;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
//-----------------------------------------------------------------------
inline GLCamera* GLCamera::Get()
{
	return ms_pInstance;
}
//-----------------------------------------------------------------------
inline void GLCamera::SetCameraMode(GLCamera::eCameraMode newMode)
{
	m_CameraMode = newMode;
}
//-----------------------------------------------------------------------
inline GLCamera::eCameraMode GLCamera::GetCameraMode() const
{
	return m_CameraMode;
}
//-----------------------------------------------------------------------
#endif //_SoD3DCamera_h_
//-----------------------------------------------------------------------
