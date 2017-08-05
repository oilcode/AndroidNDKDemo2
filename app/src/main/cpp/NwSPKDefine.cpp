//--------------------------------------------------------------------------------------------------
#include "NwSPKDefine.h"
#include "SoCodeBaseInclude.h"
//--------------------------------------------------------------------------------------------------
NwSPKHeroData::NwSPKHeroData()
{
    ClearHeroData();
}
//--------------------------------------------------------------------------------------------------
void NwSPKHeroData::ClearHeroData()
{
    nWuLi = 0;
    nMaxHP = 0;
    nCurHP = 0;
    nMaxMP = 0;
    nCurMP = 0;
    nAccSamePoint = 0;
    for (int i = 0; i < NwSPKCmd_Max; ++i)
    {
        kCmdCountList[i] = 0;
    }
    for (int i = 0; i < NwSPKBuff_Max; ++i)
    {
        kBuffList[i].theType = (NwSPKBuffType)i;
        kBuffList[i].nRemainTouchCount = 0;
    }
}
//--------------------------------------------------------------------------------------------------
int NwSPKHeroData::GetCmdCount(NwSPKCmdType theCmd) const
{
    int nCount = 0;
    if (theCmd >= 0 && theCmd < NwSPKCmd_Max)
    {
        nCount = kCmdCountList[theCmd];
    }
    return nCount;
}
//--------------------------------------------------------------------------------------------------
bool NwSPKHeroData::IsBuffEnable(NwSPKBuffType theBuff) const
{
    bool bEnable = false;
    if (theBuff >= 0 && theBuff < NwSPKBuff_Max)
    {
        bEnable = kBuffList[theBuff].IsEnable();
    }
    return bEnable;
}
//--------------------------------------------------------------------------------------------------
void NwSPKHeroData::ProcessSPKResult(const NwSPKResultSingle* pResult)
{
    if (pResult == NULL)
    {
        return;
    }

    nCurHP += pResult->nDeltaHP;
    if (nCurHP < 0)
    {
        nCurHP = 0;
    }
    else if (nCurHP > nMaxHP)
    {
        nCurHP = nMaxHP;
    }

    nCurMP += pResult->nDeltaMP;
    if (nCurMP < 0)
    {
        nCurMP = 0;
    }
    else if (nCurMP > nMaxMP)
    {
        nCurMP = nMaxMP;
    }

    nAccSamePoint += pResult->nDeltaSamePoint;

    for (int i = 0; i < NwSPKResult_MaxCmdChange; ++i)
    {
        const NwSPKResultCmdChange& kChange = pResult->kCmdChangeList[i];
        if (kChange.nCmdType >= 0 && kChange.nCmdType < NwSPKCmd_Max)
        {
            kCmdCountList[kChange.nCmdType] += kChange.nDeltaCount;
        }
    }

    for (int i = 0; i < NwSPKResult_MaxBuffChange; ++i)
    {
        const NwSPKResultBuffChange& kChange = pResult->kBuffChangeList[i];
        if (kChange.nBuffType >= 0 && kChange.nBuffType < NwSPKBuff_Max)
        {
            kBuffList[kChange.nBuffType].nRemainTouchCount += kChange.nDeltaTouchCount;
        }
    }

    //判断撞衫点数能否兑换成闪避
    if (nAccSamePoint >= NwSPK_SamePointPerShanBi)
    {
        nAccSamePoint -= NwSPK_SamePointPerShanBi;
        kCmdCountList[NwSPKCmd_ShanBi] += 1;
    }

    //判断旋风斩是否被激活
    kCmdCountList[NwSPKCmd_XuanFeng] = nCurMP / NwSPK_MPCountPerXuanFeng;
}
//--------------------------------------------------------------------------------------------------
void NwSPKHeroData::ProcessTouchFinished()
{
    for (int i = 0; i < NwSPKBuff_Max; ++i)
    {
        if (kBuffList[i].nRemainTouchCount > 0)
        {
            --(kBuffList[i].nRemainTouchCount);
        }
    }
}
//--------------------------------------------------------------------------------------------------
NwSPKSelectedCmd::NwSPKSelectedCmd()
{
    ClearSelectedCmd();
}
//--------------------------------------------------------------------------------------------------
void NwSPKSelectedCmd::ClearSelectedCmd()
{
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        kCmdList[i] = NwSPKCmd_Invalid;
    }
}
//--------------------------------------------------------------------------------------------------
NwSPKResultSingle::NwSPKResultSingle()
{
    ClearResultSingle();
}
//--------------------------------------------------------------------------------------------------
void NwSPKResultSingle::ClearResultSingle()
{
    theResult = NwSPKTouchResult_Draw;
    nDeltaHP = 0;
    nDeltaMP = 0;
    nDeltaSamePoint = 0;
    for (int i = 0; i < NwSPKResult_MaxCmdChange; ++i)
    {
        kCmdChangeList[i].nCmdType = NwSPKCmd_Invalid;
        kCmdChangeList[i].nDeltaCount = 0;
    }
    for (int i = 0; i < NwSPKResult_MaxBuffChange; ++i)
    {
        kBuffChangeList[i].nBuffType = NwSPKBuff_Invalid;
        kBuffChangeList[i].nDeltaTouchCount = 0;
    }
}
//--------------------------------------------------------------------------------------------------
void NwSPKResultSingle::AddBuff(int nBuffType, int nDeltaTouchCount)
{
    for (int i = 0; i < NwSPKResult_MaxBuffChange; ++i)
    {
        if (kBuffChangeList[i].nBuffType == NwSPKBuff_Invalid)
        {
            kBuffChangeList[i].nBuffType = nBuffType;
            kBuffChangeList[i].nDeltaTouchCount = nDeltaTouchCount;
            break;
        }
    }
}
//--------------------------------------------------------------------------------------------------
NwSPKResultTouch::NwSPKResultTouch()
{
    ClearResultTouch();
}
//--------------------------------------------------------------------------------------------------
void NwSPKResultTouch::ClearResultTouch()
{
    for (int i = 0; i < NwSPKSide_Max; ++i)
    {
        kSideList[i].ClearResultSingle();
    }
}
//--------------------------------------------------------------------------------------------------
NwSPKResultRound::NwSPKResultRound()
{
    ClearResultRound();
}
//--------------------------------------------------------------------------------------------------
void NwSPKResultRound::ClearResultRound()
{
    for (int i = 0; i < NwSPKTouch_Max; ++i)
    {
        kTouchList[i].ClearResultTouch();
    }
}
//--------------------------------------------------------------------------------------------------
