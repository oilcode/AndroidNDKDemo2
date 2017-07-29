//--------------------------------------------------------------------------------------------------
#include "NwSPKDefine.h"
//--------------------------------------------------------------------------------------------------
SPKHeroData::SPKHeroData()
{
    nWuLi = 0;
    nMaxHP = 0;
    nCurHP = 0;
    nMaxEnergy = 0;
    nCurEnergy = 0;
    nCmdUp = 0;
    nCmdMiddle = 0;
    nCmdDown = 0;
    nCmdDefend = 0;
    nCmdDodge = 0;
    nCmdInsight = 0;
    nCmdSwoosh = 0;
    nCmdRevenge = 0;
    nDodgeCountInBag = 0;
    nInsightCountInBag = 0;
    nSwooshCountInBag = 0;
    nRevengeCountInBag = 0;
    bDizzy = false;
}
//--------------------------------------------------------------------------------------------------
void SPKHeroData::IncreaseCmdCount(NwSPKCmdType theCmd, int nDelta)
{
    const int nCmdType = theCmd;
    switch (nCmdType)
    {
        case NwSPKCmd_Up:
        {
            nCmdUp += nDelta;
            break;
        }
        case NwSPKCmd_Middle:
        {
            nCmdMiddle += nDelta;
            break;
        }
        case NwSPKCmd_Down:
        {
            nCmdDown += nDelta;
            break;
        }
        case NwSPKCmd_ZhaoJia:
        {
            nCmdDefend += nDelta;
            break;
        }
        case NwSPKCmd_ShanBi:
        {
            nCmdDodge += nDelta;
            break;
        }
        case NwSPKCmd_DongCha:
        {
            nCmdInsight += nDelta;
            break;
        }
        case NwSPKCmd_XuanFeng:
        {
            nCmdSwoosh += nDelta;
            break;
        }
        case NwSPKCmd_FanSha:
        {
            nCmdRevenge += nDelta;
            break;
        }
    }
}
//--------------------------------------------------------------------------------------------------
