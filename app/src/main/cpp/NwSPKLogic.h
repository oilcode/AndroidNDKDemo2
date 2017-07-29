//--------------------------------------------------------------------
#ifndef _NwSPKLogic_h_
#define _NwSPKLogic_h_
//--------------------------------------------------------------------
#include "SoCodeBaseInclude.h"
#include "NwSPKDefine.h"
//--------------------------------------------------------------------
class NwSPKLogic
{
public:
    NwSPKLogic();
    ~NwSPKLogic();
    void ResetSPKLogic();

    const SPKHeroData* GetMyHeroData();
    const SPKHeroData* GetAIHeroData();

    //一个回合即将开始，为我方武将准备可选的指令
    void PrepareForRound_MyHero();
    //一个回合即将开始，为AI武将准备可选的指令
    void PrepareForRound_AIHero();

    //设置玩家选择了哪三个战斗指令
    void SetPlayerOption(NwSPKCmdType nCmd_Touch0, NwSPKCmdType nCmd_Touch1, NwSPKCmdType nCmd_Touch2);
    //为AI生成战斗指令
    void GenerateCmdForAI();
    //增加回合的数目
    void IncreaseRoundCount();

    int GetCurrentTouchIndex();
    //计算当前交锋的结果
    void GenerateCurrentTouchResult();
    //把本次交锋的结果应用到玩家数据上
    void ApplyTouchResult();
    
    NwSPKTouchResult GetTouchResult();
    //获取AI的某个作战指令
    NwSPKCmdType GetAITouchCmd(int theTouchIndex);
    //
    int GetTouchAttackDamage();
    //交锋结束，处理交锋结束的逻辑
    void TouchFinished();
    //判断本回合是否结束了
    bool IsRoundFinish();
    //判断战斗是否结束了，有人血量为0了
    bool IsFightFinish();
    //战斗结束，判断客户端主角是否赢了
    bool IsMainPlayerWin();
    
private:
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
    void RemoveFromAIWaitingCmd(NwSPKCmdType theCmd);
    
private:
    SPKHeroData m_kMyHeroData;
    SPKHeroData m_kAIHeroData;

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //本次回合相关的数据
    //记录玩家已经选择好的指令
    NwSPKCmdType m_kMyCmdList[NwSPKTouch_Max];
    //记录AI已经选择好的指令
    NwSPKCmdType m_kAICmdList[NwSPKTouch_Max];
    //为AI生成战斗指令时，存储可以待选的指令
    std::vector<NwSPKCmdType> m_vecAIWaitingCmd;
    //存储攻击类的待选指令，本集合是 m_vecAIWaitingCmd 的一个子集
    std::vector<NwSPKCmdType> m_vecAIWaitingCmd_Attack;
    //记录当前是第几回合，回合计数从1开始，没有第0回合
    int m_nRoundCount;
    //记录当前正在处理第几次交锋，取值范围[0,NwSPKTouch_Max)
    int m_nCurrentTouchIndex;
    //记录交锋中平局的累积次数。
    int m_nTouchDrawCount;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //本次交锋相关的数据
    //本次交锋玩家使用的指令
    NwSPKCmdType m_nMyCmd;
    //本次交锋AI使用的指令
    NwSPKCmdType m_nAICmd;
    //记录本次交锋的结果
    NwSPKTouchResult m_NwSPKTouchResult;
    //记录攻击伤害
    int m_nAttackDamage;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
//--------------------------------------------------------------------
#endif //_NwSPKLogic_h_
//--------------------------------------------------------------------















