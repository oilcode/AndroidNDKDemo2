//--------------------------------------------------------------------------------------------------
#include "GGUIActionFactory.h"
#include "GGUIActionGroup.h"
#include "GGUIActionLine.h"
#include "GGUIActionMove.h"
#include "GGUIActionScale.h"
#include "GGUIActionEvent.h"
//--------------------------------------------------------------------------------------------------
#define UnusedIndex_TryToFindUnused -1
#define UnusedIndex_CreateNewOne -2
//--------------------------------------------------------------------------------------------------
GGUIActionFactory* GGUIActionFactory::ms_pInstance = NULL;
//--------------------------------------------------------------------------------------------------
bool GGUIActionFactory::CreateUIActionFactory()
{
    bool br = true;
    if (ms_pInstance == NULL)
    {
        ms_pInstance = SoNew GGUIActionFactory;
        if (ms_pInstance && ms_pInstance->InitUIActionFactory())
        {
            br = true;
        }
        else
        {
            ReleaseUIActionFactory();
            br = false;
        }
    }
    return br;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionFactory::ReleaseUIActionFactory()
{
    if (ms_pInstance)
    {
        SoDelete ms_pInstance;
        ms_pInstance = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
GGUIActionFactory::GGUIActionFactory()
{

}
//--------------------------------------------------------------------------------------------------
GGUIActionFactory::~GGUIActionFactory()
{
    ClearUIActionFactory();
}
//--------------------------------------------------------------------------------------------------
bool GGUIActionFactory::InitUIActionFactory()
{
    if (m_kActionArray.InitArray(sizeof(GGUIActionBase*), 100, 100) == false)
    {
        return false;
    }
    //
    for (int i = 0; i < GGUIAction_Max; ++i)
    {
        m_nUnusedObjectIndex[i] = UnusedIndex_CreateNewOne;
    }
    //
    m_kEventArray.InitArray(sizeof(int), 10, 10);
    return true;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionFactory::ClearUIActionFactory()
{
    GGUIActionBase* pAction = 0;
    const int nCount = m_kActionArray.GetCapacity();
    for (int i = 0; i < nCount; ++i)
    {
        pAction = GetUIAction(i);
        if (pAction)
        {
            pAction->ClearAction();
            SoDelete pAction;
        }
    }
    m_kActionArray.ClearArray();
    //
    for (int i = 0; i < GGUIAction_Max; ++i)
    {
        m_nUnusedObjectIndex[i] = UnusedIndex_CreateNewOne;
    }
    //
    m_kEventArray.ClearArray();
}
//--------------------------------------------------------------------------------------------------
GGUIActionBase* GGUIActionFactory::CreateUIAction(GGUIActionType eType)
{
    int nIndex = -1;
    //
    if (m_nUnusedObjectIndex[eType] >= 0)
    {
        nIndex = m_nUnusedObjectIndex[eType];
        m_nUnusedObjectIndex[eType] = UnusedIndex_TryToFindUnused;
        return GetUIAction(nIndex);
    }
    //
    if (m_nUnusedObjectIndex[eType] == UnusedIndex_TryToFindUnused)
    {
        //try to find an unused object
        nIndex = FindUnusedAction(eType);
        if (nIndex != -1)
        {
            return GetUIAction(nIndex);
        }
    }
    //
    m_nUnusedObjectIndex[eType] = UnusedIndex_CreateNewOne;
    GGUIActionBase* pAction = 0;
    switch (eType)
    {
        case GGUIAction_Group:
        {
            pAction = new GGUIActionGroup;
        } break;
        case GGUIAction_Line:
        {
            pAction = new GGUIActionLine;
        } break;
        case GGUIAction_Move:
        {
            pAction = new GGUIActionMove;
        } break;
        case GGUIAction_Scale:
        {
            pAction = new GGUIActionScale;
        } break;
        case GGUIAction_Event:
        {
            pAction = new GGUIActionEvent;
        } break;
        default:
        {
            GGUILogf("GGUIActionFactory::CreateUIAction : Unknown ActionType [%d]", eType);
        } break;
    }
    if (pAction)
    {
        pAction->SetActionID(m_kActionArray.FillAt(-1, &pAction));
    }
    return pAction;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionFactory::DeleteUIAction(int nActionID)
{
    GGUIActionBase* pAction = GetUIAction(nActionID);
    if (pAction == NULL)
    {
        return;
    }
    //
    pAction->ClearAction();
    m_nUnusedObjectIndex[pAction->GetActionType()] = nActionID;
}
//--------------------------------------------------------------------------------------------------
GGUIActionBase* GGUIActionFactory::GetUIAction(int nActionID)
{
    void* pElement = m_kActionArray.GetAt(nActionID);
    if (pElement)
    {
        return *((GGUIActionBase**)pElement);
    }
    else
    {
        return NULL;
    }
}
//--------------------------------------------------------------------------------------------------
int GGUIActionFactory::FindUnusedAction(GGUIActionType eType)
{
    int nID = -1;
    GGUIActionBase* pAction = 0;
    const int nCount = m_kActionArray.GetCapacity();
    for (int i = 0; i < nCount; ++i)
    {
        //被回收的Action，其ActionLine都是NULL。
        pAction = GetUIAction(i);
        if (pAction && pAction->GetActionLine() == NULL && pAction->GetActionType() == eType)
        {
            nID = i;
            break;
        }
    }
    return nID;
}
//--------------------------------------------------------------------------------------------------
void GGUIActionFactory::DispatchActionEvent(GGUIWindowBase* pDestWindow)
{
    if (m_kEventArray.GetSize() == 0)
    {
        return;
    }

    const int nEventCount = m_kEventArray.GetSize();
    for (int i = 0; i < nEventCount; ++i)
    {
        int nEventId = *(int*)m_kEventArray.GetAt(i);
        pDestWindow->ProcessActionEvent(nEventId);
    }
    m_kEventArray.ClearArray();
}
//--------------------------------------------------------------------------------------------------
