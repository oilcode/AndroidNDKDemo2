//--------------------------------------------------------------------------------------------------
#ifndef _NwSPKJudge_h_
#define _NwSPKJudge_h_
//--------------------------------------------------------------------------------------------------
#include "NwSPKDefine.h"
//--------------------------------------------------------------------------------------------------
class NwSPKJudge
{
public:
    NwSPKJudge();
    ~NwSPKJudge();

    const NwSPKResultRound* StartJudgeRound(NwSPKHeroData* pLeftHeroData, const NwSPKSelectedCmd* pLeftCmd, NwSPKHeroData* pRightHeroData, const NwSPKSelectedCmd* pRightCmd);
    const NwSPKResultRound* StartJudgeTouch(int nTouchIndex, NwSPKHeroData* pLeftHeroData, NwSPKHeroData* pRightHeroData, NwSPKCmdType theLeftCmd, NwSPKCmdType theRightCmd);
    const NwSPKResultRound* GetResultRound() const;

private:
    void JudgeTouch(int nTouchIndex, NwSPKCmdType theLeftCmd, NwSPKCmdType theRightCmd);
    void AttackXuanYun(const NwSPKHeroData* pWinnerHero, NwSPKCmdType theCmd, NwSPKResultSingle* pWinnerResultSingle, NwSPKResultSingle* pOtherResultSingle);
    void SameCmd(NwSPKResultSingle* pLeftSingle, NwSPKResultSingle* pRightSingle);
    void DrawCmd(NwSPKResultSingle* pLeftSingle, NwSPKResultSingle* pRightSingle);
    void WinnerAttack(NwSPKCmdType theWinnerCmd, NwSPKCmdType theOtherCmd, const NwSPKHeroData* pWinnerHero, const NwSPKHeroData* pOtherHero, NwSPKResultSingle* pWinnerSingle, NwSPKResultSingle* pOtherSingle);
    int CalculateNormalDamage(const NwSPKHeroData* pWinnerHero);
    int CalculateXuanFengDamage(const NwSPKHeroData* pWinnerHero);
    int ReduceDamageByZhaoJia(const NwSPKHeroData* pLoserHero, int nDamage);
    int CalculateMP();
    bool CheckRoundFinished() const;
    NwSPKTouchResult CmdCompare(NwSPKCmdType theCmd, NwSPKCmdType theOther);

private:
    NwSPKResultRound m_kResult;
    NwSPKHeroData* m_pHeroDataList[NwSPKSide_Max];
};
//--------------------------------------------------------------------------------------------------
inline const NwSPKResultRound* NwSPKJudge::GetResultRound() const
{
    return &m_kResult;
}
//--------------------------------------------------------------------------------------------------
#endif //_NwSPKJudge_h_
//--------------------------------------------------------------------------------------------------
