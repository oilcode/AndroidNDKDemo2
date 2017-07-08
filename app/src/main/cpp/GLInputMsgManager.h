//--------------------------------------------------------------------------------------------------
#ifndef _GLInputMsgManager_h_
#define _GLInputMsgManager_h_
//--------------------------------------------------------------------------------------------------
enum eInputMsgType
{
    InputMsg_Invalid = -1,
    InputMsg_TouchDown,
    InputMsg_TouchMove,
    InputMsg_TouchUp,
};
//--------------------------------------------------------------------------------------------------
struct stInputMsgInfo
{
    eInputMsgType theType;
    float fPosX;
    float fPosY;
    float fDeltaX;
    float fDeltaY;
    bool bSwallowed; //值为true，表示本消息已经被吞噬了，排在响应队列后面的模块将不能收到本消息。

    stInputMsgInfo()
    :theType(InputMsg_Invalid), fPosX(0.0f), fPosY(0.0f)
    ,fDeltaX(0.0f), fDeltaY(0.0f), bSwallowed(false)
    {

    }
};
//--------------------------------------------------------------------------------------------------
class GLInputMsgManager
{
public:
    static bool CreateInputMsgManager();
    static void ReleaseInputMsgManager();
    static GLInputMsgManager* Get();

    void ReceiveInputMsg(eInputMsgType theType, float fPosX, float fPosY);

private:
    GLInputMsgManager();
    ~GLInputMsgManager();
    bool InitInputMsgManager();
    void ClearInputMsgManager();
    void DispatchInputMsg();

private:
    struct stInputState
    {
        eInputMsgType theMsgType;
        float fPosX;
        float fPosY;
    };

private:
    static GLInputMsgManager* ms_pInstance;
    stInputState m_kOldState;
    stInputState m_kNewState;
};
//--------------------------------------------------------------------------------------------------
inline GLInputMsgManager* GLInputMsgManager::Get()
{
    return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
#endif //_GLInputMsgManager_h_
//--------------------------------------------------------------------------------------------------
