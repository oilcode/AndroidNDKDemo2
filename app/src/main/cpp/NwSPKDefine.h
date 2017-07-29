//--------------------------------------------------------------------------------------------------
#ifndef _NwSPKDefine_h_
#define _NwSPKDefine_h_
//--------------------------------------------------------------------------------------------------
//指令
enum NwSPKCmdType
{
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
struct SPKHeroData
{
    int nWuLi; //武力值
    int nMaxHP; //最大血量
    int nCurHP; //当前血量
    int nMaxEnergy; //最大斗志
    int nCurEnergy; //当前斗志
    int nCmdUp; //当前有多少个指令
    int nCmdMiddle;
    int nCmdDown;
    int nCmdDefend;
    int nCmdDodge; //当前一共有多少个该指令，包括背包中的道具。
    int nCmdInsight;
    int nCmdSwoosh;
    int nCmdRevenge;
    int nDodgeCountInBag; //背包中有多少个闪避
    int nInsightCountInBag; //背包中有多少个洞察
    int nSwooshCountInBag; //背包中有多少个旋风斩
    int nRevengeCountInBag; //背包中有多少个反杀
    bool bDizzy; //是否眩晕了

    SPKHeroData();
    void IncreaseCmdCount(NwSPKCmdType theCmd, int nDelta);
};
//--------------------------------------------------------------------------------------------------
#endif //_NwSPKDefine_h_
//--------------------------------------------------------------------------------------------------
