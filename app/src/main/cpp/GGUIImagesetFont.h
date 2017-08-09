//----------------------------------------------------------------
#ifndef _GGUIImagesetFont_h_
#define _GGUIImagesetFont_h_
//----------------------------------------------------------------
#include "GGUIImagesetBase.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
struct stImagesetFontParam
{
	//Imageset的名字。
	SoTinyString kName;
	//贴图对象。
	GLTexture* pTexture;
	//预分配多少个Rect。
	int nInitRectCount;
	float fFontSize;
	float fFontHeight;

	stImagesetFontParam() : pTexture(NULL), nInitRectCount(4), fFontSize(24.0f), fFontHeight(32.0f)
	{

	}
};
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
	bool InitImagesetFont(const stImagesetFontParam* pParam);
	void ClearImagesetFont();
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
	float m_fFontSize;
	float m_fFontHeight;
};
//----------------------------------------------------------------
#endif //_GGUIImagesetFont_h_
//----------------------------------------------------------------
