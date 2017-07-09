//--------------------------------------------------------------------------------------------------
#include "AnInputMsgDispatch.h"
#include "GLLogicFlowHelp.h"
#include "GGUILogicFlowHelp.h"
#include "GGUIInputMsg.h"
//--------------------------------------------------------------------------------------------------
AnInputMsgDispatch::stInputState AnInputMsgDispatch::m_kOldState;
AnInputMsgDispatch::stInputState AnInputMsgDispatch::m_kNewState;
//--------------------------------------------------------------------------------------------------
GGUIInputMsgType g_eAnInputMsgType2GGUI[AnInputMsg_Max];
//--------------------------------------------------------------------------------------------------
void AnInputMsgDispatch::InitInputMsgDispatch()
{
    g_eAnInputMsgType2GGUI[AnInputMsg_TouchDown] = GGUIInputMsg_TouchDown;
    g_eAnInputMsgType2GGUI[AnInputMsg_TouchMove] = GGUIInputMsg_TouchMove;
    g_eAnInputMsgType2GGUI[AnInputMsg_TouchUp] = GGUIInputMsg_TouchUp;
    g_eAnInputMsgType2GGUI[AnInputMsg_Max] = GGUIInputMsg_Max;
}
//--------------------------------------------------------------------------------------------------
void AnInputMsgDispatch::ClearInputMsgDispatch()
{
    //do nothing
}
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

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    GGUIInputMsg kGGUIMsg;
    kGGUIMsg.theType = g_eAnInputMsgType2GGUI[kInfo.theType];
    kGGUIMsg.fPosX = kInfo.fPosX;
    kGGUIMsg.fPosY = kInfo.fPosY;
    kGGUIMsg.fDeltaX = kInfo.fDeltaX;
    kGGUIMsg.fDeltaY = kInfo.fDeltaY;
    kGGUIMsg.bSwallowed = false;
    GGUILogicFlowHelp_DispatchInputMsg(&kGGUIMsg);
    if (kGGUIMsg.bSwallowed)
    {
        return;
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    //
    GLLogicFlowHelpDispatchInputMsg(&kInfo);
    if (kInfo.bSwallowed)
    {
        return;
    }
}
//--------------------------------------------------------------------------------------------------
