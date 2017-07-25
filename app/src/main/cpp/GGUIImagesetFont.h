//----------------------------------------------------------------
#ifndef _GGUIImagesetFont_h_
#define _GGUIImagesetFont_h_
//----------------------------------------------------------------
#include "GGUIImagesetBase.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
struct stImagesetFontRect
{
	float x;
	float y;
	float w;
	float h;
	float offsetX;
	float offsetY;
	float advanceX;

	stImagesetFontRect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f), offsetX(0.0f), offsetY(0.0f), advanceX(0.0f)
	{

	}
};
extern stImagesetFontRect ImagesetFontRect_Empty;
//----------------------------------------------------------------
class GGUIImagesetFont : public GGUIImagesetBase
{
public:
	void AddRect(const char* szChar, const stImagesetFontRect& kRect);
	const stImagesetFontRect& GetRect(const char* szChar);
	const stImagesetFontRect* GetRectP(const char* szChar);
	//
	souint32 GetTexResourceID() const;

protected:
	friend class GGUIImagesetManager;
	GGUIImagesetFont();
	~GGUIImagesetFont();
	//初始化函数。
	//--nInitRectCount 预分配多少个Rect。
	bool InitImagesetFont(int nInitRectCount);
	void ClearImagesetFont();
	void SetTexture(GLTexture* pTexture);
	souint32 GenerateCharNumber(const souint8* szChar);
	int GetIndexByCharNumber(souint32 Number) const;

private:
	typedef std::map<souint32, int> mapCharNumber2ID;

private:
	//数组，存储的元素是 stImagesetFontRect 。
	SoArrayUID m_kRectArray;
	//字符数字到 stImagesetFontRect 序号的映射。
	mapCharNumber2ID m_kIDMap;
	//贴图对象指针。
	GLTexture* m_pTexture;
};
//----------------------------------------------------------------
#endif //_GGUIImagesetFont_h_
//----------------------------------------------------------------
