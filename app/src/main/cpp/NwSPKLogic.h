//--------------------------------------------------------------------
#ifndef _NwSPKLogic_h_
#define _NwSPKLogic_h_
//--------------------------------------------------------------------
#include <vector>
#include <string>
//--------------------------------------------------------------------
//指令
enum eCmdButton
{
    CmdBtn_Up,
    CmdBtn_Middle,
    CmdBtn_Down,
    CmdBtn_Defend, //招架，格挡
    CmdBtn_Dodge, //闪避
    CmdBtn_Insight, //洞察
    CmdBtn_Swoosh, //旋风斩
    CmdBtn_Revenge, //反杀
    CmdBtn_Max,
};
//指令名字
extern std::string g_strCmdNameList[CmdBtn_Max];
extern std::string g_strDizzyName;
//每个回合有三次交锋
enum eTouchButton
{
    TouchBtn_0,
    TouchBtn_1,
    TouchBtn_2,
    TouchBtn_Max,
};
//一次交锋中的胜负值
enum eTouchResult
{
    TouchResult_Win, //玩家赢了AI
    TouchResult_Lose, //玩家输给了AI
    TouchResult_Draw, //平手
};
//
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
    void IncreaseCmdCount(eCmdButton theCmd, int nDelta);
};
//--------------------------------------------------------------------
class NwSPKLogic
{
public:
    NwSPKLogic();
    ~NwSPKLogic();
    
    const SPKHeroData* GetMyHeroData();
    const SPKHeroData* GetAIHeroData();

    //一个回合即将开始，为我方武将准备可选的指令
    void PrepareForRound_MyHero();
    //一个回合即将开始，为AI武将准备可选的指令
    void PrepareForRound_AIHero();
    
    //设置玩家选择了哪三个战斗指令
    void SetPlayerOption(eCmdButton nCmd_Touch0, eCmdButton nCmd_Touch1, eCmdButton nCmd_Touch2);
    //为AI生成战斗指令
    void GenerateCmdForAI();
    //增加回合的数目
    void IncreaseRoundCount();
    
    //计算当前交锋的结果
    void GenerateCurrentTouchResult();
    //把本次交锋的结果应用到玩家数据上
    void ApplyTouchResult();
    
    eTouchResult GetTouchResult();
    //获取AI的某个作战指令
    eCmdButton GetAITouchCmd(int theTouchIndex);
    //
    int GetTouchAttackDamage();
    //交锋结束，处理交锋结束的逻辑
    void TouchFinished();
    //判断本回合是否结束了
    bool IsRoundFinish();
    //判断战斗是否结束了，有人血量为0了
    bool IsFightFinish();
    //
    const char* GetMyFinalCmdName();
    const char* GetAIFinalCmdName();
    
private:
    void InitSPKLogic();
    //判断两个指令的大小
    void JudgeCmd(int CmdA, int CmdB);
    //计算攻击伤害
    void CalculateDamage();
    //获取玩家武将的本次攻击伤害
    int GetMyAttackDamage();
    //获取AI武将的本次攻击伤害
    int GetAIAttackDamage();
    //为AI生成战斗指令前，获取有哪些待选的指令
    void PrepareAIWaitingCmd();
    //获取攻击类的待选指令
    void PrepareAIWaitingCmd_Attack();
    //从待选指令数组中删除某个指令
    void RemoveFromAIWaitingCmd(eCmdButton theCmd);
    
private:
    SPKHeroData m_kMyHeroData;
    SPKHeroData m_kAIHeroData;

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //本次回合相关的数据
    //记录玩家已经选择好的指令
    eCmdButton m_kMyCmdList[TouchBtn_Max];
    //记录AI已经选择好的指令
    eCmdButton m_kAICmdList[TouchBtn_Max];
    //为AI生成战斗指令时，存储可以待选的指令
    std::vector<eCmdButton> m_vecAIWaitingCmd;
    //存储攻击类的待选指令，本集合是 m_vecAIWaitingCmd 的一个子集
    std::vector<eCmdButton> m_vecAIWaitingCmd_Attack;
    //记录当前是第几回合，回合计数从1开始，没有第0回合
    int m_nRoundCount;
    //记录当前正在处理第几次交锋，取值范围[0,TouchBtn_Max)
    int m_nCurrentTouchIndex;
    //记录交锋中平局的累积次数。
    int m_nTouchDrawCount;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //本次交锋相关的数据
    //本次交锋玩家使用的指令
    eCmdButton m_nMyCmd;
    const char* m_szMyFinalCmdName;
    //本次交锋AI使用的指令
    eCmdButton m_nAICmd;
    const char* m_szAIFinalCmdName;
    //记录本次交锋的结果
    eTouchResult m_eTouchResult;
    //记录攻击伤害
    int m_nAttackDamage;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
//--------------------------------------------------------------------
#endif //_NwSPKLogic_h_
//--------------------------------------------------------------------















