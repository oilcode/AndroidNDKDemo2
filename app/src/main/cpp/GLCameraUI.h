//-----------------------------------------------------------------------
#ifndef _GLCameraUI_h_
#define _GLCameraUI_h_
//-----------------------------------------------------------------------
#include "GLBaseInclude.h"
//-----------------------------------------------------------------------
class GLCameraUI
{
public:
	static bool CreateCameraUI();
	static void ReleaseCameraUI();
	static GLCameraUI* Get();

	const SoMathMatrix4& GetMatProjView() const;

private:
	GLCameraUI();
	~GLCameraUI();
	bool InitCameraUI();
	void ClearCameraUI();

private:
	static GLCameraUI* ms_pInstance;
	SoMathMatrix4 m_matProjView;
};
//-----------------------------------------------------------------------
inline GLCameraUI* GLCameraUI::Get()
{
	return ms_pInstance;
}
//-----------------------------------------------------------------------
inline const SoMathMatrix4& GLCameraUI::GetMatProjView() const
{
	return m_matProjView;
}
//-----------------------------------------------------------------------
#endif //_GLCameraUI_h_
//-----------------------------------------------------------------------
