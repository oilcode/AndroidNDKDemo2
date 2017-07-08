//--------------------------------------------------------------------------------------------------
#include "AnInputMsgDispatch.h"
#include "GLLogicFlowHelp.h"
#include "GGUILogicFlowHelp.h"
//--------------------------------------------------------------------------------------------------
AnInputMsgDispatch::stInputState AnInputMsgDispatch::m_kOldState;
AnInputMsgDispatch::stInputState AnInputMsgDispatch::m_kNewState;
//--------------------------------------------------------------------------------------------------
void AnInputMsgDispatch::DispatchInputMsg(AnInputMsgType theType, float fPosX, float fPosY)
{
    m_kOldState = m_kNewState;
    //
    m_kNewState.theMsgType = theType;
    m_kNewState.fPosX = fPosX;
    m_kNewState.fPosY = fPosY;
    //
    AnInputMsgInfo kInfo;
    kInfo.theType = m_kNewState.theMsgType;
    kInfo.fPosX = m_kNewState.fPosX;
    kInfo.fPosY = m_kNewState.fPosY;
    kInfo.fDeltaX = m_kNewState.fPosX - m_kOldState.fPosX;
    kInfo.fDeltaY = m_kNewState.fPosY - m_kOldState.fPosY;
    kInfo.bSwallowed = false;
    //-------------------------------------------------------------
    //
    GGUILogicFlowHelp_DispatchInputMsg(&kInfo);
    if (kInfo.bSwallowed)
    {
        return;
    }
    //
    GLLogicFlowHelpDispatchInputMsg(&kInfo);
    if (kInfo.bSwallowed)
    {
        return;
    }
}
//--------------------------------------------------------------------------------------------------
