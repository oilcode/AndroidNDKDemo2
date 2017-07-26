//----------------------------------------------------------------
#ifndef _GGUIImagesetFont_h_
#define _GGUIImagesetFont_h_
//----------------------------------------------------------------
#include "GGUIImagesetBase.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
class GGUIImagesetFont : public GGUIImagesetBase
{
public:
	void AddRect(const char* szChar, const stImageFontRect& kRect);
	const stImageFontRect* GetRect(const char* szChar) const;
	void CalculateStringGlyphSize(const char* szString, int nCharCount, float* pStringWidth, float* pStringHeight) const;
	//
	souint32 GetTexResourceID() const;
    float GetTextureWidth() const;
    float GetTextureHeight() const;

protected:
	friend class GGUIImagesetManager;
	GGUIImagesetFont();
	~GGUIImagesetFont();
	//初始化函数。
	//--nInitRectCount 预分配多少个Rect。
	bool InitImagesetFont(int nInitRectCount);
	void ClearImagesetFont();
	void SetTexture(GLTexture* pTexture);
	souint32 GenerateCharNumber(const souint8* szChar) const;
	int GetIndexByCharNumber(souint32 Number) const;

private:
	typedef std::map<souint32, int> mapCharNumber2ID;

private:
	//数组，存储的元素是 stImageFontRect 。
	SoArrayUID m_kRectArray;
	//字符数字到 stImageFontRect 序号的映射。
	mapCharNumber2ID m_kIDMap;
	//贴图对象指针。
	GLTexture* m_pTexture;
};
//----------------------------------------------------------------
#endif //_GGUIImagesetFont_h_
//----------------------------------------------------------------
