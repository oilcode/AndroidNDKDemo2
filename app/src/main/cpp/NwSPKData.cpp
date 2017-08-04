//--------------------------------------------------------------------------------------------------
#include "NwSPKData.h"
#include "NwSPKLogic.h"
#include "NwSceneSPK.h"
//--------------------------------------------------------------------
const int g_nCmdCount_Normal = 2;
//--------------------------------------------------------------------------------------------------
NwSPKData::NwSPKData()
{
    ResetSPKData();
}
//--------------------------------------------------------------------------------------------------
NwSPKData::~NwSPKData()
{

}
//--------------------------------------------------------------------------------------------------
void NwSPKData::ResetSPKData()
{
    m_kLeftHeroData.ClearHeroData();
    m_kRightHeroData.ClearHeroData();
    m_kLeftSelectedCmd.ClearSelectedCmd();
    m_kRightSelectedCmd.ClearSelectedCmd();
    m_nRoundCount = 0;
    m_nTouchIndex = 0;
    //
    m_kLeftHeroData.nWuLi = 80;
    m_kLeftHeroData.nMaxHP = 1000;
    m_kLeftHeroData.nCurHP = 1000;
    m_kLeftHeroData.nMaxEnergy = 100;
    m_kLeftHeroData.nCurEnergy = 0;
    //
    m_kRightHeroData.nWuLi = 80;
    m_kRightHeroData.nMaxHP = 1000;
    m_kRightHeroData.nCurHP = 1000;
    m_kRightHeroData.nMaxEnergy = 100;
    m_kRightHeroData.nCurEnergy = 0;
}
//--------------------------------------------------------------------------------------------------
NwSPKHeroData* NwSPKData::GetLeftHeroData()
{
    return &m_kLeftHeroData;
}
//--------------------------------------------------------------------------------------------------
NwSPKHeroData* NwSPKData::GetRightHeroData()
{
    return &m_kRightHeroData;
}
//--------------------------------------------------------------------------------------------------
const NwSPKSelectedCmd* NwSPKData::GetLeftSelectedCmd()
{
    return &m_kLeftSelectedCmd;
}
//--------------------------------------------------------------------------------------------------
const NwSPKSelectedCmd* NwSPKData::GetRightSelectedCmd()
{
    return &m_kRightSelectedCmd;
}
//--------------------------------------------------------------------------------------------------
NwSPKCmdType NwSPKData::GetLeftCmd_CurrentTouch()
{
    NwSPKCmdType theType = NwSPKCmd_Invalid;
    if (m_nTouchIndex >= 0 && m_nTouchIndex < NwSPKTouch_Max)
    {
        theType = m_kLeftSelectedCmd.kCmdList[m_nTouchIndex];
    }
    return theType;
}
//--------------------------------------------------------------------------------------------------
NwSPKCmdType NwSPKData::GetRightCmd_CurrentTouch()
{
    NwSPKCmdType theType = NwSPKCmd_Invalid;
    if (m_nTouchIndex >= 0 && m_nTouchIndex < NwSPKTouch_Max)
    {
        theType = m_kRightSelectedCmd.kCmdList[m_nTouchIndex];
    }
    return theType;
}
//--------------------------------------------------------------------------------------------------
void NwSPKData::PrepareCmdListForNewRound()
{
    m_kLeftHeroData.kCmdCountList[NwSPKCmd_Up] = g_nCmdCount_Normal;
    m_kLeftHeroData.kCmdCountList[NwSPKCmd_Middle] = g_nCmdCount_Normal;
    m_kLeftHeroData.kCmdCountList[NwSPKCmd_Down] = g_nCmdCount_Normal;
    m_kLeftHeroData.kCmdCountList[NwSPKCmd_ZhaoJia] = g_nCmdCount_Normal;
    //
    m_kRightHeroData.kCmdCountList[NwSPKCmd_Up] = g_nCmdCount_Normal;
    m_kRightHeroData.kCmdCountList[NwSPKCmd_Middle] = g_nCmdCount_Normal;
    m_kRightHeroData.kCmdCountList[NwSPKCmd_Down] = g_nCmdCount_Normal;
    m_kRightHeroData.kCmdCountList[NwSPKCmd_ZhaoJia] = g_nCmdCount_Normal;
}
//--------------------------------------------------------------------------------------------------
void NwSPKData::SetLeftSelectedCmd(NwSPKCmdType cmd0, NwSPKCmdType cmd1, NwSPKCmdType cmd2)
{
    m_kLeftSelectedCmd.kCmdList[0] = cmd0;
    m_kLeftSelectedCmd.kCmdList[1] = cmd1;
    m_kLeftSelectedCmd.kCmdList[2] = cmd2;
    //
    if (cmd0 == NwSPKCmd_XuanFeng || cmd0 == NwSPKCmd_FanSha)
    {
        m_kLeftHeroData.kCmdCountList[cmd0] -= 1;
    }
    else
    {
        m_kLeftHeroData.kCmdCountList[cmd0] -= 1;
        m_kLeftHeroData.kCmdCountList[cmd1] -= 1;
        m_kLeftHeroData.kCmdCountList[cmd2] -= 1;
    }
}
//--------------------------------------------------------------------------------------------------
void NwSPKData::GenerateCmdForAI()
{
    NwSPKLogic* pSPKLogic = NwSceneSPK::Get()->GetSPKLogic();
    pSPKLogic->GenerateCmdForAI(&m_kRightHeroData, &m_kLeftHeroData, &m_kRightSelectedCmd);
    //
    NwSPKCmdType cmd0 = m_kRightSelectedCmd.kCmdList[0];
    if (cmd0 == NwSPKCmd_XuanFeng || cmd0 == NwSPKCmd_FanSha)
    {
        m_kRightHeroData.kCmdCountList[cmd0] -= 1;
    }
    else
    {
        m_kRightHeroData.kCmdCountList[cmd0] -= 1;
        m_kRightHeroData.kCmdCountList[m_kRightSelectedCmd.kCmdList[1]] -= 1;
        m_kRightHeroData.kCmdCountList[m_kRightSelectedCmd.kCmdList[2]] -= 1;
    }
}
//--------------------------------------------------------------------------------------------------
void NwSPKData::OnRoundStart()
{
    ++m_nRoundCount;
    m_nTouchIndex = 0;
    m_kLeftSelectedCmd.ClearSelectedCmd();
    m_kRightSelectedCmd.ClearSelectedCmd();
}
//--------------------------------------------------------------------------------------------------
bool NwSPKData::OnTouchFinished()
{
    NwSPKCmdType curLeftCmd = m_kLeftSelectedCmd.kCmdList[m_nTouchIndex];
    NwSPKCmdType curRightCmd = m_kRightSelectedCmd.kCmdList[m_nTouchIndex];

    m_kLeftHeroData.ProcessTouchFinished();
    m_kRightHeroData.ProcessTouchFinished();

    ++m_nTouchIndex;

    if (m_nTouchIndex >= NwSPKTouch_Max)
    {
        return true;
    }

    //如果是旋风斩，则一次交锋就结束
    if (curLeftCmd == NwSPKCmd_XuanFeng || curRightCmd == NwSPKCmd_XuanFeng)
    {
        return true;
    }

    //如果有人死亡，则战斗结束
    return IsAnySideHPEmpty();
}
//--------------------------------------------------------------------------------------------------
int NwSPKData::GetTouchIndex()
{
   return m_nTouchIndex;
}
//--------------------------------------------------------------------------------------------------
bool NwSPKData::IsAnySideHPEmpty()
{
    if (m_kLeftHeroData.nCurHP <= 0)
    {
        return true;
    }
    if (m_kRightHeroData.nCurHP <= 0)
    {
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------------
bool NwSPKData::IsLeftSideWin()
{
    return (m_kLeftHeroData.nCurHP > 0);
}
//--------------------------------------------------------------------------------------------------
