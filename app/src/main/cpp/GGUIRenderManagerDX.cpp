//----------------------------------------------------------------
#include "GGUIRenderManagerDX.h"
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
//----------------------------------------------------------------
#include "SoD3DSystem.h"
#include "SoD3DShaderManager.h"
#include "GGUIUserDefine.h"
//----------------------------------------------------------------
//每个DrawCall最多绘制多少个UI窗口。
//每个UI窗口占用4个顶点。
#define MaxWindowCountPerDrawCall 200
//每个DrawCall最多使用多少张贴图。
//DX11规定的上限是 D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT=128 。
#define MaxSRVCountPerDrawCall 50
//----------------------------------------------------------------
GGUIRenderManagerDX* GGUIRenderManagerDX::ms_pInstance = NULL;
//----------------------------------------------------------------
bool GGUIRenderManagerDX::CreateUIRenderManagerDX()
{
	bool br = true;
	if (ms_pInstance == NULL)
	{
		ms_pInstance = new GGUIRenderManagerDX;
		if (ms_pInstance && ms_pInstance->InitUIRenderManagerDX())
		{
			//初始化成功，什么都不做
		}
		else
		{
			ReleaseUIRenderManagerDX();
			br = false;
		}
	}
	return br;
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::ReleaseUIRenderManagerDX()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = NULL;
	}
}
//----------------------------------------------------------------
GGUIRenderManagerDX::GGUIRenderManagerDX()
:m_pVertexList(NULL)
,m_pVertexBuffer(NULL)
,m_pIndexBuffer(NULL)
,m_pSRVList(NULL)
,m_pShader(NULL)
,m_nMaxWindowCount(0)
,m_nCurWindowCount(0)
,m_nMaxSRVCount(0)
,m_nCurSRVCount(0)
,m_nLastTextureIndex(-1)
,m_fCurrentRenderOrder(GGUI_RenderOrder_Max)
{

}
//----------------------------------------------------------------
GGUIRenderManagerDX::~GGUIRenderManagerDX()
{
	ClearUIRenderManagerDX();
}
//----------------------------------------------------------------
bool GGUIRenderManagerDX::InitUIRenderManagerDX()
{
	if (CreateSRVList() == false)
	{
		return false;
	}
	//注意，先执行CreateVertexList()，再执行CreateVertexBuffer()
	if (CreateVertexList() == false)
	{
		return false;
	}
	if (CreateVertexBuffer() == false)
	{
		return false;
	}
	if (CreateIndexBuffer() == false)
	{
		return false;
	}
	m_pShader = SoD3DShaderManager::Get()->GetShader(SoD3DShaderType_GGUI);
	if (m_pShader == NULL)
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::ClearUIRenderManagerDX()
{
	ReleaseVertexList();
	ReleaseVertexBuffer();
	ReleaseIndexBuffer();
	ReleaseSRVList();
	m_pShader = NULL;
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::AddRnederUnit(const stUIRenderUnit* pUIRenderUnit)
{
	if (m_nCurWindowCount >= m_nMaxWindowCount)
	{
		SoIDEOutputLog("GGUIRenderManagerDX::AddRnederUnit : m_pVertexList is full!");
#ifdef SoMessageBoxEnable
		SoMessageBox("", "GGUIRenderManagerDX::AddRnederUnit : m_pVertexList is full!");
#endif
        return;
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//计算贴图序号
	float fTextureIndex = -1.0f;
	ID3D11ShaderResourceView* pNewSRV = (ID3D11ShaderResourceView*)(pUIRenderUnit->uiTexResource);
	if (m_nLastTextureIndex >= 0 && m_pSRVList[m_nLastTextureIndex] == pNewSRV)
	{
		fTextureIndex = (float)m_nLastTextureIndex;
	}
	else
	{
		for (int i = 0; i < m_nCurSRVCount; ++i)
		{
			if (m_pSRVList[i] == pNewSRV)
			{
				fTextureIndex = (float)i;
				m_nLastTextureIndex = i;
				break;
			}
		}
	}
	if (fTextureIndex < 0.0f)
	{
		if (m_nCurSRVCount < m_nMaxSRVCount)
		{
			m_pSRVList[m_nCurSRVCount] = pNewSRV;
			fTextureIndex = (float)m_nCurSRVCount;
			m_nLastTextureIndex = m_nCurSRVCount;
			++m_nCurSRVCount;
		}
		else
		{
			SoIDEOutputLog("GGUIRenderManagerDX::AddRnederUnit : m_pSRVList is full!");
#ifdef SoMessageBoxEnable
			SoMessageBox("", "GGUIRenderManagerDX::AddRnederUnit : m_pSRVList is full!");
#endif
			return;
		}
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//填充顶点数据
	stVertexType* pVertex = m_pVertexList + (m_nCurWindowCount * 4 + 0);
	pVertex->kPosition.x = floorf(pUIRenderUnit->fRectLeft + 0.5f);
	pVertex->kPosition.y = floorf(pUIRenderUnit->fRectTop + 0.5f);
	pVertex->kPosition.z = m_fCurrentRenderOrder;
	pVertex->kTexCoordAndTexIndex.x = pUIRenderUnit->fTexCoordLeft;
	pVertex->kTexCoordAndTexIndex.y = pUIRenderUnit->fTexCoordTop;
	pVertex->kTexCoordAndTexIndex.z = fTextureIndex;
	pVertex->kColorRGBA.x = pUIRenderUnit->fColorR;
	pVertex->kColorRGBA.y = pUIRenderUnit->fColorG;
	pVertex->kColorRGBA.z = pUIRenderUnit->fColorB;
	pVertex->kColorRGBA.w = pUIRenderUnit->fColorA;

	pVertex = pVertex + 1;
	pVertex->kPosition.x = floorf(pUIRenderUnit->fRectRight + 0.5f);
	pVertex->kPosition.y = floorf(pUIRenderUnit->fRectTop + 0.5f);
	pVertex->kPosition.z = m_fCurrentRenderOrder;
	pVertex->kTexCoordAndTexIndex.x = pUIRenderUnit->fTexCoordRight;
	pVertex->kTexCoordAndTexIndex.y = pUIRenderUnit->fTexCoordTop;
	pVertex->kTexCoordAndTexIndex.z = fTextureIndex;
	pVertex->kColorRGBA.x = pUIRenderUnit->fColorR;
	pVertex->kColorRGBA.y = pUIRenderUnit->fColorG;
	pVertex->kColorRGBA.z = pUIRenderUnit->fColorB;
	pVertex->kColorRGBA.w = pUIRenderUnit->fColorA;

	pVertex = pVertex + 1;
	pVertex->kPosition.x = floorf(pUIRenderUnit->fRectRight + 0.5f);
	pVertex->kPosition.y = floorf(pUIRenderUnit->fRectBottom + 0.5f);
	pVertex->kPosition.z = m_fCurrentRenderOrder;
	pVertex->kTexCoordAndTexIndex.x = pUIRenderUnit->fTexCoordRight;
	pVertex->kTexCoordAndTexIndex.y = pUIRenderUnit->fTexCoordBottom;
	pVertex->kTexCoordAndTexIndex.z = fTextureIndex;
	pVertex->kColorRGBA.x = pUIRenderUnit->fColorR;
	pVertex->kColorRGBA.y = pUIRenderUnit->fColorG;
	pVertex->kColorRGBA.z = pUIRenderUnit->fColorB;
	pVertex->kColorRGBA.w = pUIRenderUnit->fColorA;

	pVertex = pVertex + 1;
	pVertex->kPosition.x = floorf(pUIRenderUnit->fRectLeft + 0.5f);
	pVertex->kPosition.y = floorf(pUIRenderUnit->fRectBottom + 0.5f);
	pVertex->kPosition.z = m_fCurrentRenderOrder;
	pVertex->kTexCoordAndTexIndex.x = pUIRenderUnit->fTexCoordLeft;
	pVertex->kTexCoordAndTexIndex.y = pUIRenderUnit->fTexCoordBottom;
	pVertex->kTexCoordAndTexIndex.z = fTextureIndex;
	pVertex->kColorRGBA.x = pUIRenderUnit->fColorR;
	pVertex->kColorRGBA.y = pUIRenderUnit->fColorG;
	pVertex->kColorRGBA.z = pUIRenderUnit->fColorB;
	pVertex->kColorRGBA.w = pUIRenderUnit->fColorA;
	//
	++m_nCurWindowCount;
	m_fCurrentRenderOrder += GGUI_RenderOrder_Step;
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::RenderUIRenderManagerDX()
{
	if (m_nCurWindowCount == 0)
	{
		return;
	}
	ID3D11DeviceContext* pD3DDeviceContext = SoD3DSystem::Get()->GetD3DDeviceContext();
	////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//把顶点数据从CPU内存拷贝到GPU内存中
	D3D11_MAPPED_SUBRESOURCE kMappedResource;
	memset(&kMappedResource, 0, sizeof(kMappedResource));
	HRESULT hr = pD3DDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &kMappedResource);
	if (FAILED(hr))
	{
		SoIDEOutputLog("GGUIRenderManagerDX::RenderUIRenderManagerDX : Map fail!");
#ifdef SoMessageBoxEnable
		SoMessageBox("", "GGUIRenderManagerDX::RenderUIRenderManagerDX : Map fail!");
#endif
		return;
	}

	memcpy(kMappedResource.pData, m_pVertexList, sizeof(stVertexType)*m_nCurWindowCount*4);
	pD3DDeviceContext->Unmap(m_pVertexBuffer, 0);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//绘制
	stShaderGGUIParam kShaderParam;
	kShaderParam.pVB = m_pVertexBuffer;
	kShaderParam.pIB = m_pIndexBuffer;
	kShaderParam.uiIndexCount = m_nCurWindowCount * 6;
	kShaderParam.uiSizeofVertexType = sizeof(stVertexType);
	kShaderParam.pSRVList = m_pSRVList;
	kShaderParam.nSRVCount = m_nCurSRVCount;
	m_pShader->ProcessRender(&kShaderParam);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//绘制完毕，执行清除操作。
	m_nCurWindowCount = 0;
	m_nCurSRVCount = 0;
	m_nLastTextureIndex = -1;
	m_fCurrentRenderOrder = GGUI_RenderOrder_Max;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
//----------------------------------------------------------------
bool GGUIRenderManagerDX::CreateVertexList()
{
	const int nVertexCount = MaxWindowCountPerDrawCall * 4;
	m_pVertexList = new stVertexType[nVertexCount];
	if (m_pVertexList == NULL)
	{
		return false;
	}

	m_nMaxWindowCount = MaxWindowCountPerDrawCall;
	m_nCurWindowCount = 0;
	return true;
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::ReleaseVertexList()
{
	if (m_pVertexList)
	{
		delete [] m_pVertexList;
		m_pVertexList = NULL;
	}
	m_nMaxWindowCount = 0;
	m_nCurWindowCount = 0;
}
//----------------------------------------------------------------
bool GGUIRenderManagerDX::CreateVertexBuffer()
{
	if (m_pVertexList == NULL)
	{
		return false;
	}

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(stVertexType) * (MaxWindowCountPerDrawCall * 4);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = m_pVertexList;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	ID3D11Device* pD3DDevice = SoD3DSystem::Get()->GetD3DDevice();
	HRESULT hr = pD3DDevice->CreateBuffer(&vertexBufferDesc, &vertexData, &m_pVertexBuffer);
	return SUCCEEDED(hr);
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::ReleaseVertexBuffer()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
}
//----------------------------------------------------------------
bool GGUIRenderManagerDX::CreateIndexBuffer()
{
	const int nIndexCount = MaxWindowCountPerDrawCall * 6;
	unsigned int* pIndex = new unsigned int[nIndexCount];
	if (pIndex == 0)
	{
		return false;
	}

	for (int i=0; i<MaxWindowCountPerDrawCall; ++i)
	{
		int nIndex = i * 6;
		pIndex[nIndex+0] = i*4+0;
		pIndex[nIndex+1] = i*4+1;
		pIndex[nIndex+2] = i*4+2;
		pIndex[nIndex+3] = i*4+0;
		pIndex[nIndex+4] = i*4+2;
		pIndex[nIndex+5] = i*4+3;
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * nIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = pIndex;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	ID3D11Device* pD3DDevice = SoD3DSystem::Get()->GetD3DDevice();
	HRESULT hr = pD3DDevice->CreateBuffer(&indexBufferDesc, &indexData, &m_pIndexBuffer);

	delete [] pIndex;
	pIndex = 0;

	return SUCCEEDED(hr);
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::ReleaseIndexBuffer()
{
	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = NULL;
	}
}
//----------------------------------------------------------------
bool GGUIRenderManagerDX::CreateSRVList()
{
	const int nMaxSRVCount = MaxSRVCountPerDrawCall;
	m_pSRVList = new ID3D11ShaderResourceView*[nMaxSRVCount];
	if (m_pSRVList == NULL)
	{
		return false;
	}

	m_nMaxSRVCount = nMaxSRVCount;
	m_nCurSRVCount = 0;
	m_nLastTextureIndex = -1;
	return true;
}
//----------------------------------------------------------------
void GGUIRenderManagerDX::ReleaseSRVList()
{
	if (m_pSRVList)
	{
		delete [] m_pSRVList;
		m_pSRVList = NULL;
	}
	m_nMaxSRVCount = 0;
	m_nCurSRVCount = 0;
	m_nLastTextureIndex = -1;
}
//----------------------------------------------------------------
#endif //(SoTargetPlatform == SoPlatform_Windows)
//----------------------------------------------------------------
