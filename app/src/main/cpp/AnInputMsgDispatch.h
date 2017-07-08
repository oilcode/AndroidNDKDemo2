//--------------------------------------------------------------------------------------------------
#ifndef _AnInputMsgDispatch_h_
#define _AnInputMsgDispatch_h_
//--------------------------------------------------------------------------------------------------
#include "AnInputMsgDefine.h"
//--------------------------------------------------------------------------------------------------
class AnInputMsgDispatch
{
public:
    static void DispatchInputMsg(AnInputMsgType theType, float fPosX, float fPosY);

private:
    struct stInputState
    {
        AnInputMsgType theMsgType;
        float fPosX;
        float fPosY;

        stInputState() : theMsgType(AnInputMsg_Invalid), fPosX(0.0f), fPosY(0.0f)
        {

        }
    };

private:
    static stInputState m_kOldState;
    static stInputState m_kNewState;
};
//--------------------------------------------------------------------------------------------------
#endif //_AnInputMsgDispatch_h_
//--------------------------------------------------------------------------------------------------
