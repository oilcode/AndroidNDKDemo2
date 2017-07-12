//----------------------------------------------------------------
#ifndef _GGUIImageset_h_
#define _GGUIImageset_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
class GGUIImageset
{
public:
	void AddRect(const SoTinyString& kName, const GGUIRect& kRect);
	int GetRectID(const SoTinyString& kName) const;
	const GGUIRect& GetRect(int nID) const;
	int GetRectCount() const;
	souint32 GetTexResourceID() const;
	float GetTextureWidth() const;
	float GetTextureHeight() const;

protected:
	friend class GGUIImagesetManager;
	GGUIImageset();
	~GGUIImageset();
	//初始化函数。
	//--nInitRectCount 预分配多少个GGUIRect。
	bool InitImageset(int nInitRectCount);
	void ClearImageset();
	void SetTexture(GLTexture* pTexture);

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
