//----------------------------------------------------------------
#ifndef _GGUIRenderManagerDX_h_
#define _GGUIRenderManagerDX_h_
//----------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
//----------------------------------------------------------------
#include "SoD3DInclude.h"
#include "GGUIRenderDefine.h"
//----------------------------------------------------------------
class SoD3DShaderBase;
//----------------------------------------------------------------
class GGUIRenderManagerDX
{
public:
	static bool CreateUIRenderManagerDX();
	static void ReleaseUIRenderManagerDX();
	static GGUIRenderManagerDX* Get();

	void AddRnederUnit(const stUIRenderUnit* pUIRenderUnit);
	void RenderUIRenderManagerDX();

private:
	GGUIRenderManagerDX();
	~GGUIRenderManagerDX();
	bool InitUIRenderManagerDX();
	void ClearUIRenderManagerDX();
	//
	bool CreateVertexList();
	void ReleaseVertexList();
	bool CreateVertexBuffer();
	void ReleaseVertexBuffer();
	bool CreateIndexBuffer();
	void ReleaseIndexBuffer();
	bool CreateSRVList();
	void ReleaseSRVList();

private:
	struct stVertexType
	{
		XMFLOAT3 kPosition;
		XMFLOAT3 kTexCoordAndTexIndex;
		XMFLOAT4 kColorRGBA;
	};

private:
	static GGUIRenderManagerDX* ms_pInstance;
	stVertexType* m_pVertexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11ShaderResourceView** m_pSRVList;
	SoD3DShaderBase* m_pShader;
	//记录 m_pVertexList 中的元素个数
	int m_nMaxWindowCount;
	int m_nCurWindowCount;
	//记录 m_pSRVList 中的元素个数
	int m_nMaxSRVCount;
	int m_nCurSRVCount;
	//最近一次执行AddRnederUnit时，贴图序号是多少。
	//本次执行AddRnederUnit时，贴图序号极有可能与上次的贴图序号相同。
	//这样做的目的是提高命中率，减少遍历。
	int m_nLastTextureIndex;
	//绘制当前的 stUIRenderUnit 时，使用的ZValue的值是多少。
	float m_fCurrentRenderOrder;
};
//----------------------------------------------------------------
inline GGUIRenderManagerDX* GGUIRenderManagerDX::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //(SoTargetPlatform == SoPlatform_Windows)
//----------------------------------------------------------------
#endif //_GGUIRenderManagerDX_h_
//----------------------------------------------------------------
