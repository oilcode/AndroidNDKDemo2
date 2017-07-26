//----------------------------------------------------------------
#include "GGUIRenderManager.h"
#include "GLManager.h"
#include "GLShaderManager.h"
#include "GGUIUserDefine.h"
//----------------------------------------------------------------
//每个DrawCall最多绘制多少个UI窗口。
//每个UI窗口占用4个顶点。
#define MaxWindowCountPerDrawCall 200
//每个DrawCall最多使用多少张贴图。
//DX11规定的上限是 D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT=128 。
#define MaxSRVCountPerDrawCall 8
//----------------------------------------------------------------
GGUIRenderManager* GGUIRenderManager::ms_pInstance = NULL;
//----------------------------------------------------------------
bool GGUIRenderManager::CreateUIRenderManager()
{
	bool br = true;
	if (ms_pInstance == NULL)
	{
		ms_pInstance = new GGUIRenderManager;
		if (ms_pInstance && ms_pInstance->InitUIRenderManager())
		{
            br = true;
		}
		else
		{
			ReleaseUIRenderManager();
			br = false;
		}
	}
	return br;
}
//----------------------------------------------------------------
void GGUIRenderManager::ReleaseUIRenderManager()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = NULL;
	}
}
//----------------------------------------------------------------
GGUIRenderManager::GGUIRenderManager()
:m_pVertexList(NULL)
,m_pIndexList(NULL)
,m_pSRVList(NULL)
,m_pShader(NULL)
,m_nMaxWindowCount(0)
,m_nCurWindowCount(0)
,m_nMaxSRVCount(0)
,m_nCurSRVCount(0)
,m_nLastTextureIndex(-1)
,m_fCurrentRenderOrder(GGUI_RenderOrder_Max)
,m_fScreenHeight(0.0f)
{

}
//----------------------------------------------------------------
GGUIRenderManager::~GGUIRenderManager()
{
	ClearUIRenderManager();
}
//----------------------------------------------------------------
bool GGUIRenderManager::InitUIRenderManager()
{
	if (CreateVertexList() == false)
	{
		return false;
	}
	if (CreateIndexList() == false)
	{
		return false;
	}
    if (CreateSRVList() == false)
    {
        return false;
    }
	m_pShader = GLShaderManager::Get()->GetShader(GLShader_GGUI);
	if (m_pShader == NULL)
	{
		return false;
	}

    int nScreenW = 0;
    int nScreenH = 0;
    GLManager::Get()->GetResolution(&nScreenW, &nScreenH);
    m_fScreenHeight = (float)nScreenH;

	return true;
}
//----------------------------------------------------------------
void GGUIRenderManager::ClearUIRenderManager()
{
	ReleaseVertexList();
	ReleaseIndexList();
	ReleaseSRVList();
	m_pShader = NULL;
}
//----------------------------------------------------------------
void GGUIRenderManager::AddRnederUnit(const stUIRenderUnit* pUIRenderUnit)
{
	if (m_nCurWindowCount >= m_nMaxWindowCount)
	{
		SoIDEOutputLogError("GGUIRenderManager::AddRnederUnit : m_pVertexList is full!");
        SoMessageBox("", "GGUIRenderManager::AddRnederUnit : m_pVertexList is full!");
		return;
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//计算贴图序号
	float fTextureIndex = -1.0f;
	if (m_nLastTextureIndex >= 0 && m_pSRVList[m_nLastTextureIndex] == pUIRenderUnit->uiTexResourceId)
	{
		fTextureIndex = (float)m_nLastTextureIndex;
	}
	else
	{
		for (int i = 0; i < m_nCurSRVCount; ++i)
		{
			if (m_pSRVList[i] == pUIRenderUnit->uiTexResourceId)
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
			m_pSRVList[m_nCurSRVCount] = pUIRenderUnit->uiTexResourceId;
			fTextureIndex = (float)m_nCurSRVCount;
			m_nLastTextureIndex = m_nCurSRVCount;
			++m_nCurSRVCount;
		}
		else
		{
			SoIDEOutputLogError("GGUIRenderManager::AddRnederUnit : m_pSRVList is full!");
            SoMessageBox("", "GGUIRenderManager::AddRnederUnit : m_pSRVList is full!");
			return;
		}
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//填充顶点数据
    //左上
	stVertexType* pVertex = m_pVertexList + (m_nCurWindowCount * 4 + 0);
	pVertex->kPosition.x = floorf(pUIRenderUnit->fRectLeft + 0.5f);
	pVertex->kPosition.y = floorf(m_fScreenHeight - pUIRenderUnit->fRectTop - 0.5f);
	pVertex->kPosition.z = m_fCurrentRenderOrder;
	pVertex->kTexCoordAndTexIndex.x = pUIRenderUnit->fTexCoordLeft;
	pVertex->kTexCoordAndTexIndex.y = pUIRenderUnit->fTexCoordTop;
	pVertex->kTexCoordAndTexIndex.z = fTextureIndex;
	pVertex->kColorRGBA.x = pUIRenderUnit->fColorR;
	pVertex->kColorRGBA.y = pUIRenderUnit->fColorG;
	pVertex->kColorRGBA.z = pUIRenderUnit->fColorB;
	pVertex->kColorRGBA.w = pUIRenderUnit->fColorA;

    //右上
    pVertex = pVertex + 1;
    pVertex->kPosition.x = floorf(pUIRenderUnit->fRectRight + 0.5f);
    pVertex->kPosition.y = floorf(m_fScreenHeight - pUIRenderUnit->fRectTop - 0.5f);
    pVertex->kPosition.z = m_fCurrentRenderOrder;
    pVertex->kTexCoordAndTexIndex.x = pUIRenderUnit->fTexCoordRight;
    pVertex->kTexCoordAndTexIndex.y = pUIRenderUnit->fTexCoordTop;
    pVertex->kTexCoordAndTexIndex.z = fTextureIndex;
    pVertex->kColorRGBA.x = pUIRenderUnit->fColorR;
    pVertex->kColorRGBA.y = pUIRenderUnit->fColorG;
    pVertex->kColorRGBA.z = pUIRenderUnit->fColorB;
    pVertex->kColorRGBA.w = pUIRenderUnit->fColorA;

    //右下
	pVertex = pVertex + 1;
	pVertex->kPosition.x = floorf(pUIRenderUnit->fRectRight + 0.5f);
	pVertex->kPosition.y = floorf(m_fScreenHeight - pUIRenderUnit->fRectBottom - 0.5f);
	pVertex->kPosition.z = m_fCurrentRenderOrder;
	pVertex->kTexCoordAndTexIndex.x = pUIRenderUnit->fTexCoordRight;
	pVertex->kTexCoordAndTexIndex.y = pUIRenderUnit->fTexCoordBottom;
	pVertex->kTexCoordAndTexIndex.z = fTextureIndex;
	pVertex->kColorRGBA.x = pUIRenderUnit->fColorR;
	pVertex->kColorRGBA.y = pUIRenderUnit->fColorG;
	pVertex->kColorRGBA.z = pUIRenderUnit->fColorB;
	pVertex->kColorRGBA.w = pUIRenderUnit->fColorA;

    //左下
    pVertex = pVertex + 1;
    pVertex->kPosition.x = floorf(pUIRenderUnit->fRectLeft + 0.5f);
    pVertex->kPosition.y = floorf(m_fScreenHeight - pUIRenderUnit->fRectBottom - 0.5f);
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
void GGUIRenderManager::RenderUIRenderManager()
{
	if (m_nCurWindowCount == 0)
	{
		return;
	}

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//绘制
    GLShaderGGUIParam kShaderParam;
    kShaderParam.pVertexArray = (float*)m_pVertexList;
	kShaderParam.pIndexArray = m_pIndexList;
	kShaderParam.nIndexCount = m_nCurWindowCount * 6;
	kShaderParam.nSizeofVertexStruct = sizeof(stVertexType);
    kShaderParam.nVertexOffset = 0;
    kShaderParam.nUVOffset = 3;
    kShaderParam.nColorOffset = 6;
	kShaderParam.pTexIDList = m_pSRVList;
	kShaderParam.nTexIDCount = m_nCurSRVCount;
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
bool GGUIRenderManager::CreateVertexList()
{
	const int nVertexCount = MaxWindowCountPerDrawCall * 4;
	m_pVertexList = SoNew stVertexType[nVertexCount];
	if (m_pVertexList == NULL)
	{
		return false;
	}

	m_nMaxWindowCount = MaxWindowCountPerDrawCall;
	m_nCurWindowCount = 0;
	return true;
}
//----------------------------------------------------------------
void GGUIRenderManager::ReleaseVertexList()
{
	if (m_pVertexList)
	{
		SoDelete [] m_pVertexList;
		m_pVertexList = NULL;
	}
	m_nMaxWindowCount = 0;
	m_nCurWindowCount = 0;
}
//----------------------------------------------------------------
bool GGUIRenderManager::CreateIndexList()
{
	const int nIndexCount = MaxWindowCountPerDrawCall * 6;
	unsigned short* pIndex = SoNew unsigned short[nIndexCount];
	if (pIndex == 0)
	{
		return false;
	}

	for (int i=0; i<MaxWindowCountPerDrawCall; ++i)
	{
		int nIndex = i * 6;
		pIndex[nIndex+0] = i*4+0;
		pIndex[nIndex+1] = i*4+3;
		pIndex[nIndex+2] = i*4+2;
		pIndex[nIndex+3] = i*4+0;
		pIndex[nIndex+4] = i*4+2;
		pIndex[nIndex+5] = i*4+1;
	}

	m_pIndexList = pIndex;
	return true;
}
//----------------------------------------------------------------
void GGUIRenderManager::ReleaseIndexList()
{
	if (m_pIndexList)
	{
        SoDelete [] m_pIndexList;
        m_pIndexList = NULL;
	}
}
//----------------------------------------------------------------
bool GGUIRenderManager::CreateSRVList()
{
	const int nMaxSRVCount = GLShaderGGUI_MaxTexSamplerCount;
	m_pSRVList = SoNew GLuint[nMaxSRVCount];
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
void GGUIRenderManager::ReleaseSRVList()
{
	if (m_pSRVList)
	{
		SoDelete [] m_pSRVList;
		m_pSRVList = NULL;
	}
	m_nMaxSRVCount = 0;
	m_nCurSRVCount = 0;
	m_nLastTextureIndex = -1;
}
//----------------------------------------------------------------
