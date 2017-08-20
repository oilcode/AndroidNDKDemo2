//--------------------------------------------------------------------------------------------------
#ifndef _GGUIInputMsg_h_
#define _GGUIInputMsg_h_
//--------------------------------------------------------------------------------------------------
enum GGUIInputMsgType
{
    GGUIInputMsg_Invalid = -1,
    GGUIInputMsg_Down,
    GGUIInputMsg_Up,
    GGUIInputMsg_Move,
    GGUIInputMsg_MouseWheel,
    GGUIInputMsg_Max,
};
//--------------------------------------------------------------------------------------------------
struct GGUIInputMsg
{
    //消息类型。
    GGUIInputMsgType theType;
    //哪个键触发了本消息。
    int theKey;
    //当前的光标的位置。
    //如果是 GGUIInputMsg_MouseWheel 消息，则表示滚轮滚动的变化量。
    float fPosX;
    float fPosY;
    //值为true，表示本消息已经被吞噬了，排在响应队列后面的模块将不能收到本消息。
    bool bSwallowed;

    GGUIInputMsg()
    : theType(GGUIInputMsg_Invalid)
    , theKey(-1)
    , fPosX(0.0f)
    , fPosY(0.0f)
    , bSwallowed(false)
    {

    }
};
//--------------------------------------------------------------------------------------------------
#endif //_GGUIInputMsg_h_
//--------------------------------------------------------------------------------------------------
