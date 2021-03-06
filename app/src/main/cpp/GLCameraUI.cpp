//-----------------------------------------------------------------------
#include "GLCameraUI.h"
#include "GLFuncHelp.h"
//-----------------------------------------------------------------------
GLCameraUI* GLCameraUI::ms_pInstance = NULL;
//-----------------------------------------------------------------------
bool GLCameraUI::CreateCameraUI()
{
	bool br = true;
	if (ms_pInstance == NULL)
	{
		ms_pInstance = SoNew GLCameraUI;
		if (ms_pInstance && ms_pInstance->InitCameraUI())
		{
			br = true;
		}
		else
		{
			ReleaseCameraUI();
			br = false;
		}
	}
	return br;
}
//-----------------------------------------------------------------------
void GLCameraUI::ReleaseCameraUI()
{
	if (ms_pInstance)
	{
		SoDelete ms_pInstance;
		ms_pInstance = NULL;
	}
}
//-----------------------------------------------------------------------
GLCameraUI::GLCameraUI()
{
	//do nothing
}
//-----------------------------------------------------------------------
GLCameraUI::~GLCameraUI()
{
	ClearCameraUI();
}
//-----------------------------------------------------------------------
bool GLCameraUI::InitCameraUI()
{
	SoMathFloat3 kPos(0.0f, 0.0f, 0.0f);
    SoMathFloat3 kRight(1.0f, 0.0f, 0.0f);
    SoMathFloat3 kForward(0.0f, 0.0f, -1.0f);
    SoMathFloat3 kUp(0.0f, 1.0f, 0.0f);
	SoMathMatrix4 kMatView;
	kMatView.MakeLookTo(kPos, kForward, kRight, kUp);

	float fWidth = 0;
	float fHeight = 0;
	GLFunc_GetResolution(&fWidth, &fHeight);
    float fnear = 0.0f;
    float ffar = 10000.0f;
	SoMathMatrix4 kMatProj;
	kMatProj.MakeOrtho2DOpenGL(0.0f, fWidth, 0.0f, fHeight, fnear, ffar);

	m_matProjView = kMatProj * kMatView;
	return true;
}
//-----------------------------------------------------------------------
void GLCameraUI::ClearCameraUI()
{
	//do nothing
}
//-----------------------------------------------------------------------
