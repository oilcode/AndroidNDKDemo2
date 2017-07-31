//------------------------------------------------------------
#include "GLTextureManager.h"
//------------------------------------------------------------
GLTextureManager* GLTextureManager::ms_pInstance = 0;
//------------------------------------------------------------
bool GLTextureManager::CreateTextureManager()
{
    bool br = true;
    if (ms_pInstance == 0)
    {
        ms_pInstance = new GLTextureManager;
        if (ms_pInstance && ms_pInstance->InitTextureManager())
        {
            br = true;
        }
        else
        {
            ReleaseTextureManager();
            br = false;
        }
    }
    else
    {
        ms_pInstance->ReCreateGLResource();
    }
	return br;
}
//------------------------------------------------------------
void GLTextureManager::ReleaseTextureManager()
{
	if (ms_pInstance)
	{
		delete ms_pInstance;
		ms_pInstance = 0;
	}
}
//------------------------------------------------------------
GLTextureManager::GLTextureManager()
{

}
//------------------------------------------------------------
GLTextureManager::~GLTextureManager()
{
    ClearTextureManager();
}
//------------------------------------------------------------
bool GLTextureManager::InitTextureManager()
{
    if (m_kUITextureArray.InitArray(sizeof(GLTexture*), 10, 10) == false)
    {
        return false;
    }
    if (m_kModelTextureArray.InitArray(sizeof(GLTexture*), 10, 10) == false)
    {
        return false;
    }
    return true;
}
//------------------------------------------------------------
void GLTextureManager::ClearTextureManager()
{
    const int nUITexCount = m_kUITextureArray.GetCapacity();
    GLTexture* pTexture = NULL;
    for (int i = 0; i < nUITexCount; ++i)
    {
        pTexture = GetUITextureByID(i);
        if (pTexture)
        {
            pTexture->ClearTexture();
            delete pTexture;
        }
    }
    m_kUITextureArray.ClearArray();
    m_kUITexName2ID.clear();
    //---------------
    const int nModelTexCount = m_kModelTextureArray.GetCapacity();
    pTexture = NULL;
    for (int i = 0; i < nModelTexCount; ++i)
    {
        pTexture = GetModelTextureByID(i);
        if (pTexture)
        {
            pTexture->ClearTexture();
            delete pTexture;
        }
    }
    m_kModelTextureArray.ClearArray();
    m_kModelTexName2ID.clear();
}
//------------------------------------------------------------
void GLTextureManager::ReCreateGLResource()
{
    const int nUITexCount = m_kUITextureArray.GetCapacity();
    GLTexture* pTexture = NULL;
    for (int i = 0; i < nUITexCount; ++i)
    {
        pTexture = GetUITextureByID(i);
        if (pTexture)
        {
            pTexture->ReCreateGLResource();
        }
    }
    //---------------
    const int nModelTexCount = m_kModelTextureArray.GetCapacity();
    pTexture = NULL;
    for (int i = 0; i < nModelTexCount; ++i)
    {
        pTexture = GetModelTextureByID(i);
        if (pTexture)
        {
            pTexture->ReCreateGLResource();
        }
    }
}
//------------------------------------------------------------
GLTexture* GLTextureManager::CreateUITextureFromFile(const char* pszFileName)
{
    GLTexture* pTexture = NULL;
    if (pszFileName == 0 || pszFileName[0] == 0)
    {
        return pTexture;
    }

    pTexture = SoNew GLTexture;
    const int nTextureID = m_kUITextureArray.FillAt(-1, &pTexture);

    std::pair<mapName2TextureID::iterator, bool> insertResult = m_kUITexName2ID.insert(std::make_pair(std::string(pszFileName), nTextureID));
    if (insertResult.second == false)
    {
        m_kUITextureArray.ClearAt(nTextureID);
        SoDelete pTexture;
        pTexture = NULL;
        return pTexture;
    }

    mapName2TextureID::iterator& it = insertResult.first;
    const char* fileName = it->first.c_str();
    if (pTexture->InitTexture(nTextureID, fileName, false) == false)
    {
        m_kModelTexName2ID.erase(it);
        m_kModelTextureArray.ClearAt(nTextureID);
        SoDelete pTexture;
        pTexture = NULL;
        return pTexture;
    }

    return pTexture;
}
//------------------------------------------------------------
GLTexture* GLTextureManager::CreateModelTextureFromFile(const char* pszFileName)
{
    GLTexture* pTexture = NULL;
    if (pszFileName == 0 || pszFileName[0] == 0)
    {
        return pTexture;
    }

    pTexture = SoNew GLTexture;
    const int nTextureID = m_kModelTextureArray.FillAt(-1, &pTexture);

    std::pair<mapName2TextureID::iterator, bool> insertResult = m_kModelTexName2ID.insert(std::make_pair(std::string(pszFileName), nTextureID));
    if (insertResult.second == false)
    {
        m_kModelTextureArray.ClearAt(nTextureID);
        SoDelete pTexture;
        pTexture = NULL;
        return pTexture;
    }

    mapName2TextureID::iterator& it = insertResult.first;
    const char* fileName = it->first.c_str();
    if (pTexture->InitTexture(nTextureID, fileName, true) == false)
    {
        m_kModelTexName2ID.erase(it);
        m_kModelTextureArray.ClearAt(nTextureID);
        SoDelete pTexture;
        pTexture = NULL;
        return pTexture;
    }

    return pTexture;
}
//------------------------------------------------------------
GLTexture* GLTextureManager::GetUITextureByID(int nTextureID)
{
    void* pElement = m_kUITextureArray.GetAt(nTextureID);
    if (pElement)
    {
        return (*((GLTexture**)pElement));
    }
    else
    {
        return NULL;
    }
}
//------------------------------------------------------------
GLTexture* GLTextureManager::GetModelTextureByID(int nTextureID)
{
    void* pElement = m_kModelTextureArray.GetAt(nTextureID);
    if (pElement)
    {
        return (*((GLTexture**)pElement));
    }
    else
    {
        return NULL;
    }
}
//------------------------------------------------------------

