//--------------------------------------------------------------------------------------------------
#include "NwActorData.h"
//--------------------------------------------------------------------------------------------------
NwActorData::NwActorData()
:m_nActorId(-1)
,m_nWuLi(0)
,m_nHuJia(0)
,m_nMinJie(0)
,m_nNaiLi(0)
,m_nTongShuai(0)
,m_nZhiLi(0)
,m_nZhengZhi(0)
,m_nMeiLi(0)
{

}
//--------------------------------------------------------------------------------------------------
NwActorData::~NwActorData()
{

}
//--------------------------------------------------------------------------------------------------
void NwActorData::ClearAll()
{
	m_nActorId = -1;
}
//--------------------------------------------------------------------------------------------------
NwActorSPKData::NwActorSPKData()
:m_nActorId(-1)
,m_nWuLi(0)
,m_nHuJia(0)
,m_nMinJie(0)
,m_nMaxHP(0)
,m_nCurHP(0)
,m_nKanPo(0)
,nCmdUpCount(0)
,nCmdMiddleCount(0)
,nCmdDownCount(0)
,nCmdZhaoJiaCount(0)
,nCmdShanBiCount(0)
,nCmdDongChaCount(0)
,nCmdXuanFengCount(0)
,nCmdFanShaCount(0)
,nShanBiCountInBag(0)
,nDongChaCountInBag(0)
,nXuanFengCountInBag(0)
,nFanShaCountInBag(0)
,bXuanYun(false)
{

}
//--------------------------------------------------------------------------------------------------
NwActorSPKData::~NwActorSPKData()
{

}
//--------------------------------------------------------------------------------------------------
void NwActorSPKData::ClearAll()
{
	m_nActorId = -1;
}
//--------------------------------------------------------------------------------------------------
