//----------------------------------------------------------------
#ifndef _GGUIWindowFactory_h_
#define _GGUIWindowFactory_h_
//----------------------------------------------------------------
#include "GGUIWindowBase.h"
//----------------------------------------------------------------
class GGUIWindowFactory
{
public:
	static bool CreateUIWindowFactory();
	static void ReleaseUIWindowFactory();
	static GGUIWindowFactory* Get();

	GGUIWindowBase* CreateUIWindow(GGUIWindowType eType);
	void DeleteUIWindow(int nWindowID);
	GGUIWindowBase* GetUIWindow(int nWindowID);

private:
	GGUIWindowFactory();
	~GGUIWindowFactory();
	bool InitUIWindowFactory();
	void ClearUIWindowFactory();
	int FindUnusedWindow(GGUIWindowType eType);

private:
	static GGUIWindowFactory* ms_pInstance;
	SoArrayUID m_kWindowArray;
	int m_nUnusedObjectIndex[GGUIWindow_Max];
};
//----------------------------------------------------------------
inline GGUIWindowFactory* GGUIWindowFactory::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIWindowFactory_h_
//----------------------------------------------------------------
