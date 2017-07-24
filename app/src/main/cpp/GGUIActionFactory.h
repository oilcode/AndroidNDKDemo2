//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionFactory_h_
#define _GGUIActionFactory_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionFactory
{
public:
	static bool CreateUIActionFactory();
	static void ReleaseUIActionFactory();
	static GGUIActionFactory* Get();

    GGUIActionBase* CreateUIAction(GGUIActionType eType);
	void DeleteUIAction(int nActionID);
    GGUIActionBase* GetUIAction(int nActionID);

    void AddActionEvent(int nEventId);
    void DispatchActionEvent(GGUIWindowBase* pDestWindow);

private:
	GGUIActionFactory();
	~GGUIActionFactory();
    bool InitUIActionFactory();
    void ClearUIActionFactory();
    int FindUnusedAction(GGUIActionType eType);

private:
    static GGUIActionFactory* ms_pInstance;
    SoArrayUID m_kActionArray;
    int m_nUnusedObjectIndex[GGUIAction_Max];
    //wait for dispatch
    SoArray m_kEventArray;
};
//--------------------------------------------------------------------------------------------------
inline GGUIActionFactory* GGUIActionFactory::Get()
{
    return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
inline void GGUIActionFactory::AddActionEvent(int nEventId)
{
    m_kEventArray.PushBack(&nEventId);
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionFactory_h_
//--------------------------------------------------------------------------------------------------
