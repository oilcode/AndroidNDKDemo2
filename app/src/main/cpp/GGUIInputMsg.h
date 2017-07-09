//--------------------------------------------------------------------------------------------------
#ifndef _GGUIInputMsg_h_
#define _GGUIInputMsg_h_
//--------------------------------------------------------------------------------------------------
enum GGUIInputMsgType
{
    GGUIInputMsg_TouchDown,
    GGUIInputMsg_TouchMove,
    GGUIInputMsg_TouchUp,
    GGUIInputMsg_Max,
};
//--------------------------------------------------------------------------------------------------
struct GGUIInputMsg
{
    GGUIInputMsgType theType;
    float fPosX;
    float fPosY;
    float fDeltaX;
    float fDeltaY;
    //值为true，表示本消息已经被吞噬了，排在响应队列后面的模块将不能收到本消息。
    bool bSwallowed;

    GGUIInputMsg();
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIInputMsg_h_
//--------------------------------------------------------------------------------------------------
