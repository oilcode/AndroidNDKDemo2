//----------------------------------------------------------------
#ifndef _GGUIAnimation_h_
#define _GGUIAnimation_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
//动画的一帧
struct GGUIAnimFrame
{
    int nImagesetId;
    int nImageRectId;

    static const GGUIAnimFrame ms_Empty;
    GGUIAnimFrame();
};
//----------------------------------------------------------------
//动画序列，一个完整的动画
struct GGUIAnimFrameset
{
    //动画序列ID
    int nAnimId;
    //里面存储的是FrameID
    SoArray kFrameIDList;

	GGUIAnimFrameset();
    void SetAnimID(int nAnimId);
    int GetAnimID() const;
    void AddFrameID(int nFrameId);
    int GetFrameCount() const;
    int GetFrameID(int nIndex) const;
};
//----------------------------------------------------------------
class GGUIAnimation
{
public:
    void AddAnimFrame(const char* szImage);
    //此函数不会返回NULL
    const GGUIAnimFrame* GetAnimFrameByID(int nFrameId);

    GGUIAnimFrameset* CreateFrameset(int nAnimId, int nInitFrameCount);
    GGUIAnimFrameset* GetFrameset(int nAnimId);

protected:
	friend class GGUIImagesetManager;
	GGUIAnimation();
	~GGUIAnimation();
	//初始化函数。
	//--nInitFrameCount 预分配多少个GGUIAnimFrame。
    //--nInitFramesetCount 预分配多少个GGUIAnimFrameset。
	bool InitAnimation(int nInitFrameCount, int nInitFramesetCount);
	void ClearAnimation();

private:
    //存储动画帧 GGUIAnimFrame ，存储序号就是 FrameID 。
    SoArrayUID m_kFrameArray;
    SoArray m_kFramesetArray;
};
//----------------------------------------------------------------
#endif //_GGUIAnimation_h_
//----------------------------------------------------------------
