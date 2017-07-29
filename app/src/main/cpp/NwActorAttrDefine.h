//--------------------------------------------------------------------------------------------------
#ifndef _NwActorAttrDefine_h_
#define _NwActorAttrDefine_h_
//--------------------------------------------------------------------------------------------------
enum NwActorAttrType
{
    //武力，影响攻击力，影响看破对方招数的洞察力
    ActorAttr_WuLi,
    //护甲，护甲高，意味着穿的铠甲重，会导致敏捷变低
    ActorAttr_HuJia,
    //敏捷，会影响触发闪避的概率
    ActorAttr_MinJie,
    //耐力，影响最大生命值
    ActorAttr_NaiLi,
    //统率
    ActorAttr_TongShuai,
    //智力
    ActorAttr_ZhiLi,
    //政治
    ActorAttr_ZhengZhi,
    //魅力
    ActorAttr_MeiLi,
    //
    ActorAttr_Max,
};
//--------------------------------------------------------------------------------------------------
enum NwSPKSlotType
{
    SPKSlot_WuLi,
    SPKSlot_HuJia,
    SPKSlot_MinJie,

    SPKSlot_MaxHP,
    SPKSlot_CurHP,
    SPKSlot_KanPo,

    SPKSlot_CmdUpCount,
    SPKSlot_CmdMiddleCount,
    SPKSlot_CmdDownCount,
    SPKSlot_CmdZhaoJiaCount,
    SPKSlot_CmdShanBiCount,
    SPKSlot_CmdDongChaCount,
    SPKSlot_CmdXuanFengCount,
    SPKSlot_CmdFanShaCount,
    SPKSlot_ShanBiCountInBag, //背包中有多少个闪避
    SPKSlot_DongChaCountInBag, //背包中有多少个洞察
    SPKSlot_XuanFengCountInBag, //背包中有多少个旋风斩
    SPKSlot_FanShaCountInBag, //背包中有多少个反杀

    SPKSlot_XuanYun, //是否眩晕了
};
//--------------------------------------------------------------------------------------------------
#endif //_NwActorAttrDefine_h_
//--------------------------------------------------------------------------------------------------
