//----------------------------------------------------------------
#include "GGUIAnimation.h"
//----------------------------------------------------------------
const GGUIAnimFrame GGUIAnimFrame::ms_Empty;
//----------------------------------------------------------------
GGUIAnimFrame::GGUIAnimFrame()
:nImagesetId(-1)
,nImageRectId(-1)
{

}
//----------------------------------------------------------------
GGUIAnimFrameset::GGUIAnimFrameset()
:nAnimId(-1)
{
    kFrameIDList.InitArray(sizeof(int), 10, 10);
}
//----------------------------------------------------------------
void GGUIAnimFrameset::SetAnimID(int _AnimId)
{
    nAnimId = _AnimId;
}
//----------------------------------------------------------------
int GGUIAnimFrameset::GetAnimID() const
{
    return nAnimId;
}
//----------------------------------------------------------------
void GGUIAnimFrameset::AddFrameID(int nFrameId)
{
    kFrameIDList.PushBack(&nFrameId);
}
//----------------------------------------------------------------
int GGUIAnimFrameset::GetFrameCount() const
{
    return kFrameIDList.GetSize();
}
//----------------------------------------------------------------
int GGUIAnimFrameset::GetFrameID(int nIndex) const
{
    int* pElement = (int*)kFrameIDList.GetAt(nIndex);
    if (pElement)
    {
        return *pElement;
    }
    else
    {
        return -1;
    }
}
//----------------------------------------------------------------
GGUIAnimation::GGUIAnimation()
{

}
//----------------------------------------------------------------
GGUIAnimation::~GGUIAnimation()
{
	ClearAnimation();
}
//----------------------------------------------------------------
bool GGUIAnimation::InitAnimation(int nInitFrameCount, int nInitFramesetCount)
{
	if (m_kFrameArray.InitArray(sizeof(GGUIAnimFrame), nInitFrameCount, 10) == false)
	{
		return false;
	}
    if (m_kFramesetArray.InitArray(sizeof(GGUIAnimFrameset*), nInitFramesetCount, 10) == false)
    {
        return false;
    }
	return true;
}
//----------------------------------------------------------------
void GGUIAnimation::ClearAnimation()
{
    m_kFrameArray.ClearArray();
    //
    const int nCount = m_kFramesetArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        GGUIAnimFrameset* pFrameset = *(GGUIAnimFrameset**)m_kFramesetArray.GetAt(i);
        SoDelete pFrameset;
    }
    m_kFramesetArray.ClearArray();
}
//----------------------------------------------------------------
void GGUIAnimation::AddAnimFrame(const char* szImage)
{
    GGUIAnimFrame kFrame;
    GGUIFunc_GetImagesetIndexRectIndex(szImage, &(kFrame.nImagesetId), &(kFrame.nImageRectId));
    m_kFrameArray.FillAt(-1, &kFrame);
}
//----------------------------------------------------------------
const GGUIAnimFrame* GGUIAnimation::GetAnimFrameByID(int nFrameId)
{
    GGUIAnimFrame* pElement = (GGUIAnimFrame*)m_kFrameArray.GetAt(nFrameId);
    if (pElement)
    {
        return pElement;
    }
    else
    {
        return &(GGUIAnimFrame::ms_Empty);
    }
}
//----------------------------------------------------------------
GGUIAnimFrameset* GGUIAnimation::CreateFrameset(int nAnimId, int nInitFrameCount)
{
    GGUIAnimFrameset* pSet = NULL;

    pSet = GetFrameset(nAnimId);
    if (pSet != NULL)
    {
        GGUILogf("GGUIAnimation::CreateFrameset : AnimId[%s] is already exist!", nAnimId);
        return pSet;
    }

    pSet = SoNew GGUIAnimFrameset;
    if (pSet == NULL)
    {
        return pSet;
    }

    pSet->nAnimId = nAnimId;
    pSet->kFrameIDList.InitArray(sizeof(int), nInitFrameCount, 10);
    m_kFramesetArray.PushBack(pSet);
    return pSet;
}
//----------------------------------------------------------------
GGUIAnimFrameset* GGUIAnimation::GetFrameset(int nAnimId)
{
    const int nCount = m_kFramesetArray.GetSize();
    for (int i = 0; i < nCount; ++i)
    {
        GGUIAnimFrameset* pSet = *(GGUIAnimFrameset**)m_kFramesetArray.GetAt(i);
        if (pSet->nAnimId == nAnimId)
        {
            return pSet;
        }
    }
    return NULL;
}
//----------------------------------------------------------------
