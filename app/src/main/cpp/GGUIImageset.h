//----------------------------------------------------------------
#ifndef _GGUIImageset_h_
#define _GGUIImageset_h_
//----------------------------------------------------------------
#include "GGUIImagesetBase.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
struct stImagesetParam
{
	//Imageset的名字。
	SoTinyString kName;
	//贴图对象。
	GLTexture* pTexture;
	//预分配多少个GGUIRect。
	int nInitRectCount;

	stImagesetParam() : pTexture(NULL), nInitRectCount(4)
	{

	}
};
//----------------------------------------------------------------
class GGUIImageset : public GGUIImagesetBase
{
public:
	void AddRect(const SoTinyString& kName, const stImageRect& kRect);
	int GetRectID(const SoTinyString& kName) const;
	const stImageRect* GetRectByID(int nID) const;
	const stImageRect* GetRectByName(const SoTinyString& kName) const;

	souint32 GetTexResourceID() const;
	float GetTextureWidth() const;
	float GetTextureHeight() const;

protected:
	friend class GGUIImagesetManager;
	GGUIImageset();
	~GGUIImageset();
	bool InitImageset(const stImagesetParam* pParam);
	void ClearImageset();

private:
	typedef std::map<SoTinyString, int> mapName2ID;

private:
	//数组，存储的元素是GGUIRect。
	SoArrayUID m_kRectArray;
	//GGUIRect名字到GGUIRect序号的映射。
	mapName2ID m_kName2IDMap;
	//贴图对象指针。
	GLTexture* m_pTexture;
};
//----------------------------------------------------------------
#endif //_GGUIImageset_h_
//----------------------------------------------------------------
