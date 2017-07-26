//----------------------------------------------------------------
#ifndef _GGUIRenderManager_h_
#define _GGUIRenderManager_h_
//----------------------------------------------------------------
#include "GLBaseInclude.h"
//----------------------------------------------------------------
class GLShaderBase;
//----------------------------------------------------------------
struct stUIRenderUnit
{
	float fRectLeft;
	float fRectRight;
	float fRectTop;
	float fRectBottom;
	float fTexCoordLeft;
	float fTexCoordRight;
	float fTexCoordTop;
	float fTexCoordBottom;
	float fColorR;
	float fColorG;
	float fColorB;
	float fColorA;
    GLuint uiTexResourceId;
};
//----------------------------------------------------------------
class GGUIRenderManager
{
public:
	static bool CreateUIRenderManager();
	static void ReleaseUIRenderManager();
	static GGUIRenderManager* Get();

	void AddRnederUnit(const stUIRenderUnit* pUIRenderUnit);
	void RenderUIRenderManager();

private:
	GGUIRenderManager();
	~GGUIRenderManager();
	bool InitUIRenderManager();
	void ClearUIRenderManager();
	//
	bool CreateVertexList();
	void ReleaseVertexList();
	bool CreateIndexList();
	void ReleaseIndexList();
	bool CreateSRVList();
	void ReleaseSRVList();

private:
	struct stVertexType
	{
		SoMathFloat3 kPosition;
        SoMathFloat3 kTexCoordAndTexIndex;
        SoMathFloat4 kColorRGBA;
	};

private:
	static GGUIRenderManager* ms_pInstance;
	stVertexType* m_pVertexList;
    unsigned short* m_pIndexList;
    GLuint* m_pSRVList;
	const GLShaderBase* m_pShader;
	//记录 m_pVertexList 中的元素个数
	int m_nMaxWindowCount;
	int m_nCurWindowCount;
	//记录 m_pTexResourceList 中的元素个数
	int m_nMaxSRVCount;
	int m_nCurSRVCount;
	//最近一次执行AddRnederUnit时，贴图序号是多少。
	//本次执行AddRnederUnit时，贴图序号极有可能与上次的贴图序号相同。
	//这样做的目的是提高命中率，减少遍历。
	int m_nLastTextureIndex;
	//绘制当前的 stUIRenderUnit 时，使用的ZValue的值是多少。
	float m_fCurrentRenderOrder;
    float m_fScreenHeight;
};
//----------------------------------------------------------------
inline GGUIRenderManager* GGUIRenderManager::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIRenderManager_h_
//----------------------------------------------------------------
