//--------------------------------------------------------------------------------------------------
#ifndef _AnInputMsgDefine_h_
#define _AnInputMsgDefine_h_
//--------------------------------------------------------------------------------------------------
enum AnInputMsgType
{
    AnInputMsg_Invalid = -1,
    AnInputMsg_TouchDown,
    AnInputMsg_TouchMove,
    AnInputMsg_TouchUp,
};
//--------------------------------------------------------------------------------------------------
struct AnInputMsgInfo
{
    AnInputMsgType theType;
    float fPosX;
    float fPosY;
    float fDeltaX;
    float fDeltaY;
    //值为true，表示本消息已经被吞噬了，排在响应队列后面的模块将不能收到本消息。
    bool bSwallowed;

    AnInputMsgInfo();
};
//--------------------------------------------------------------------------------------------------
#endif //_AnInputMsgDefine_h_
//--------------------------------------------------------------------------------------------------
