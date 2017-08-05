//--------------------------------------------------------------------------------------------------
#ifndef _NwSPKDefine_h_
#define _NwSPKDefine_h_
//--------------------------------------------------------------------------------------------------
//多少个撞衫点数能够兑换一个闪避
#define NwSPK_SamePointPerShanBi 3
//多少能量激活一个旋风斩
#define NwSPK_MPCountPerXuanFeng 100
//中了闪避之后，眩晕几个交锋
//值为2表示眩晕1个交锋，值为3表示眩晕2个交锋
#define NwSPK_XuanYunTouchCount 2
//--------------------------------------------------------------------------------------------------
//指令
enum NwSPKCmdType
{
    NwSPKCmd_Invalid = -1,
    NwSPKCmd_Up, //上劈
    NwSPKCmd_Middle, //中砍
    NwSPKCmd_Down, //下刺
    NwSPKCmd_ZhaoJia, //招架
    NwSPKCmd_ShanBi, //闪避
    NwSPKCmd_DongCha, //洞察
    NwSPKCmd_XuanFeng, //旋风斩
    NwSPKCmd_FanSha, //反杀
    NwSPKCmd_Max,
};
//--------------------------------------------------------------------------------------------------
//每个回合有三次交锋
enum NwSPKTouchType
{
    NwSPKTouch_0,
    NwSPKTouch_1,
    NwSPKTouch_2,
    NwSPKTouch_Max,
};
//--------------------------------------------------------------------------------------------------
//一次交锋中的胜负值
enum NwSPKTouchResult
{
    NwSPKTouchResult_Win, //客户端主角赢了
    NwSPKTouchResult_Lose, //客户端主角输了
    NwSPKTouchResult_Draw, //平手
};
//--------------------------------------------------------------------------------------------------
enum NwSPKBuffType
{
    NwSPKBuff_Invalid = -1,
    NwSPKBuff_XuanYun, //眩晕
    NwSPKBuff_Max,
};
//--------------------------------------------------------------------------------------------------
enum NwSPKSideType
{
    NwSPKSide_Invalid = -1,
    NwSPKSide_Left,
    NwSPKSide_Right,
    NwSPKSide_Max,
};
//--------------------------------------------------------------------------------------------------
struct NwSPKBuffData
{
    NwSPKBuffType theType; //buff类型
    int nRemainTouchCount; //还剩多少个交锋，buff就结束

    NwSPKBuffData() : theType(NwSPKBuff_Invalid), nRemainTouchCount(0)
    {

    }

    bool IsEnable() const
    {
        return (nRemainTouchCount > 0);
    }
};
//--------------------------------------------------------------------------------------------------
struct NwSPKResultSingle;
struct NwSPKHeroData
{
    int nWuLi; //武力值
    int nMaxHP; //最大血量
    int nCurHP; //当前血量
    int nMaxMP; //最大斗志
    int nCurMP; //当前斗志
    int nAccSamePoint; //当前累积的撞衫点数
    int kCmdCountList[NwSPKCmd_Max]; //当前拥有的指令的个数
    NwSPKBuffData kBuffList[NwSPKBuff_Max]; //Buff列表

    NwSPKHeroData();
    void ClearHeroData();
    int GetCmdCount(NwSPKCmdType theCmd) const;
    bool IsBuffEnable(NwSPKBuffType theBuff) const;
    //把一次交锋的结果应用到结构体中
    void ProcessSPKResult(const NwSPKResultSingle* pResult);
    //处理一次交锋结束的事件
    void ProcessTouchFinished();
};
//--------------------------------------------------------------------------------------------------
struct NwSPKSelectedCmd
{
    NwSPKCmdType kCmdList[NwSPKTouch_Max];

    NwSPKSelectedCmd();
    void ClearSelectedCmd();
};
//--------------------------------------------------------------------------------------------------
struct NwSPKResultCmdChange
{
    int nCmdType;
    int nDeltaCount;
};
//--------------------------------------------------------------------------------------------------
struct NwSPKResultBuffChange
{
    int nBuffType;
    int nDeltaTouchCount;
};
//--------------------------------------------------------------------------------------------------
#define NwSPKResult_MaxCmdChange 4
#define NwSPKResult_MaxBuffChange 4
//--------------------------------------------------------------------------------------------------
struct NwSPKResultSingle
{
    NwSPKTouchResult theResult;
    int nDeltaHP;
    int nDeltaMP;
    int nDeltaSamePoint;
    NwSPKResultCmdChange kCmdChangeList[NwSPKResult_MaxCmdChange];
    NwSPKResultBuffChange kBuffChangeList[NwSPKResult_MaxBuffChange];

    NwSPKResultSingle();
    void ClearResultSingle();
    void AddBuff(int nBuffType, int nDeltaTouchCount);
};
//--------------------------------------------------------------------------------------------------
struct NwSPKResultTouch
{
    NwSPKResultSingle kSideList[NwSPKSide_Max];

    NwSPKResultTouch();
    void ClearResultTouch();
};
//--------------------------------------------------------------------------------------------------
struct NwSPKResultRound
{
    NwSPKResultTouch kTouchList[NwSPKTouch_Max];

    NwSPKResultRound();
    void ClearResultRound();
};
//--------------------------------------------------------------------------------------------------
#endif //_NwSPKDefine_h_
//--------------------------------------------------------------------------------------------------
