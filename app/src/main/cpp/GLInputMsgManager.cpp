//--------------------------------------------------------------------------------------------------
#include "GLBaseInclude.h"
#include "GLInputMsgManager.h"
#include "GLModelCube.h"
#include "GLModelRect.h"
//--------------------------------------------------------------------------------------------------
GLInputMsgManager* GLInputMsgManager::ms_pInstance = NULL;
//--------------------------------------------------------------------------------------------------
bool GLInputMsgManager::CreateInputMsgManager()
{
    bool br = true;
    if (ms_pInstance == NULL)
    {
        ms_pInstance = SoNew GLInputMsgManager;
        if (ms_pInstance && ms_pInstance->InitInputMsgManager())
        {
            br = true;
        }
        else
        {
            ReleaseInputMsgManager();
            br = false;
        }
    }
    return br;
}
//--------------------------------------------------------------------------------------------------
void GLInputMsgManager::ReleaseInputMsgManager()
{
    if (ms_pInstance)
    {
        SoDelete ms_pInstance;
        ms_pInstance = NULL;
    }
}
//--------------------------------------------------------------------------------------------------
GLInputMsgManager::GLInputMsgManager()
{

}
//--------------------------------------------------------------------------------------------------
GLInputMsgManager::~GLInputMsgManager()
{
    ClearInputMsgManager();
}
//--------------------------------------------------------------------------------------------------
bool GLInputMsgManager::InitInputMsgManager()
{
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLInputMsgManager::ClearInputMsgManager()
{

}
//--------------------------------------------------------------------------------------------------
void GLInputMsgManager::ReceiveInputMsg(eInputMsgType theType, float fPosX, float fPosY)
{
    m_kOldState = m_kNewState;
    //
    m_kNewState.theMsgType = theType;
    m_kNewState.fPosX = fPosX;
    m_kNewState.fPosY = fPosY;
    //
    DispatchInputMsg();
}
//--------------------------------------------------------------------------------------------------
extern GLModelCube* g_pModelCube;
extern GLModelRect* g_pModelRect;
void GLInputMsgManager::DispatchInputMsg()
{
    stInputMsgInfo kInfo;
    kInfo.theType = m_kNewState.theMsgType;
    kInfo.fPosX = m_kNewState.fPosX;
    kInfo.fPosY = m_kNewState.fPosY;
    kInfo.fDeltaX = m_kNewState.fPosX - m_kOldState.fPosX;
    kInfo.fDeltaY = m_kNewState.fPosY - m_kOldState.fPosY;

    if (g_pModelCube)
    {
        g_pModelCube->ModelProcessInputMsg(&kInfo);
        if (kInfo.bSwallowed)
        {
            //  return;
        }
    }


    if (g_pModelRect)
    {
        g_pModelRect->ModelProcessInputMsg(&kInfo);
        if (kInfo.bSwallowed)
        {
            return;
        }
    }
}
//--------------------------------------------------------------------------------------------------
