//--------------------------------------------------------------------------------------------------
#ifndef _NwActorData_h_
#define _NwActorData_h_
//--------------------------------------------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//--------------------------------------------------------------------------------------------------
class NwActorData
{
protected:
    friend class NwActorDataManager;
    NwActorData();
    ~NwActorData();
    void ClearAll();

public:
    //值为-1，表示无效值
    int m_nActorId;
    //武力，影响攻击力，影响看破对方招数的洞察力
    int m_nWuLi;
    //护甲，护甲高，意味着穿的铠甲重，会导致敏捷变低
    int m_nHuJia;
    //敏捷，会影响触发闪避的概率
    int m_nMinJie;
    //耐力，影响最大生命值
    int m_nNaiLi;
    //统率
    int m_nTongShuai;
    //智力
    int m_nZhiLi;
    //政治
    int m_nZhengZhi;
    //魅力
    int m_nMeiLi;
};
//--------------------------------------------------------------------------------------------------
class NwActorSPKData
{
protected:
    friend class NwActorDataManager;
    NwActorSPKData();
    ~NwActorSPKData();
    void ClearAll();

public:
    //值为-1，表示无效值
    int m_nActorId;
    int m_nWuLi;
    int m_nHuJia;
    int m_nMinJie;

    int m_nMaxHP;
    int m_nCurHP;
    int m_nKanPo;

    int nCmdUpCount;
    int nCmdMiddleCount;
    int nCmdDownCount;
    int nCmdZhaoJiaCount;
    int nCmdShanBiCount;
    int nCmdDongChaCount;
    int nCmdXuanFengCount;
    int nCmdFanShaCount;
    int nShanBiCountInBag; //背包中有多少个闪避
    int nDongChaCountInBag; //背包中有多少个洞察
    int nXuanFengCountInBag; //背包中有多少个旋风斩
    int nFanShaCountInBag; //背包中有多少个反杀

    bool bXuanYun; //是否眩晕了
};
//--------------------------------------------------------------------------------------------------
#endif //_NwActorData_h_
//--------------------------------------------------------------------------------------------------
