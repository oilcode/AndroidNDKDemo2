//----------------------------------------------------------------
#include "GGUIRichTextStruct.h"
//----------------------------------------------------------------
GGUIRichTextStruct::GGUIRichTextStruct()
:m_fMaxWidth(0.0f)
,m_fMaxHeight(0.0f)
{
	//初始时没有为 m_kTextChunkArray 分配内存，外界要主动调用 ResizeTextChunkArray() 。
	m_kTextChunkArray.InitArray(sizeof(GGUITextChunk), 0, GGUI_ComponentText_TextChunkAddCount);
}
//----------------------------------------------------------------
GGUIRichTextStruct::~GGUIRichTextStruct()
{
	ClearRichTextStruct();
}
//----------------------------------------------------------------
void GGUIRichTextStruct::ClearRichTextStruct()
{
	m_kTextChunkArray.ClearArray();
    m_fMaxWidth = 0.0f;
    m_fMaxHeight = 0.0f;
}
//----------------------------------------------------------------
void GGUIRichTextStruct::ResizeTextChunkArray(int nCount)
{
	m_kTextChunkArray.ResizeArray(nCount);
}
//----------------------------------------------------------------
void GGUIRichTextStruct::AddTextChunk(const GGUITextChunk* pChunk)
{
	m_kTextChunkArray.PushBack(pChunk);
}
//----------------------------------------------------------------
void GGUIRichTextStruct::ClearTextChunk()
{
	m_kTextChunkArray.ClearArray();
}
//----------------------------------------------------------------
int GGUIRichTextStruct::GetTextChunkCount() const
{
	return m_kTextChunkArray.GetSize();
}
//----------------------------------------------------------------
const GGUITextChunk* GGUIRichTextStruct::GetTextChunk(int nIndex) const
{
	return (GGUITextChunk*)(m_kTextChunkArray.GetAt(nIndex));
}
//----------------------------------------------------------------
