//----------------------------------------------------------------
#ifndef _NwUIMain_h_
#define _NwUIMain_h_
//----------------------------------------------------------------
#include "NwBaseInclude.h"
//----------------------------------------------------------------
class NwUIMain : public GGUIWindowPanel
{
public:
	static bool CreateUIMain();
	static void ReleaseUIMain();
	static NwUIMain* Get();

	void UpdateUIMain(float fDeltaTime);

private:
	NwUIMain();
	~NwUIMain();
	bool InitUIMain();
	void ClearUIMain();
	void ProcessUIEvent(int nEventType, void* pParam);

private:
	static NwUIMain* ms_pInstance;
	int m_nButtonID;
};
//----------------------------------------------------------------
inline NwUIMain* NwUIMain::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_NwUIMain_h_
//----------------------------------------------------------------
