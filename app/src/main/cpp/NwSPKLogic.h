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

    //为AI生成战斗指令
    void GenerateCmdForAI(const NwSPKHeroData* pAIHeroData, const NwSPKHeroData* pOtherHeroData, NwSPKSelectedCmd* pSelectedCmd);
    
private:
    //为AI生成战斗指令前，获取有哪些待选的指令
    void PrepareAIWaitingCmd(const NwSPKHeroData* pHeroData);
    //获取攻击类的待选指令
    void PrepareAIWaitingCmd_Attack();
    //从待选指令数组中删除某个指令
    void RemoveFromAIWaitingCmd(NwSPKCmdType theCmd);
    NwSPKCmdType PickOneFromWaitingCmd();
    NwSPKCmdType PickOneFromWaitingCmd_Attack();
    
private:
    //为AI生成战斗指令时，存储可以待选的指令
    std::vector<NwSPKCmdType> m_vecAIWaitingCmd;
    //存储攻击类的待选指令，本集合是 m_vecAIWaitingCmd 的一个子集
    std::vector<NwSPKCmdType> m_vecAIWaitingCmd_Attack;
};
//--------------------------------------------------------------------
#endif //_NwSPKLogic_h_
//--------------------------------------------------------------------
