//--------------------------------------------------------------------------------------------------
#include "GLShaderStandard.h"
#include "SoFileHelp.h"
//--------------------------------------------------------------------------------------------------
GLShaderStandard::GLShaderStandard()
:m_uiProgramID(0)
,m_uiVertexID(0)
,m_uiUVID(0)
,m_uiMatWorldID(0)
,m_uiMatProjectViewID(0)
,m_uiTexSamplerID(0)
{
    const char* VertexShader = "";
    SoFile* pVSFile = SoFileHelp::CreateFileAsset("shader/standard_vs.txt");
    if (pVSFile)
    {
        VertexShader = (char*)pVSFile->GetFileData();
    }

    const char* FragmentShader = "";
    SoFile* pPSFile = SoFileHelp::CreateFileAsset("shader/standard_ps.txt");
    if (pPSFile)
    {
        FragmentShader = (char*)pPSFile->GetFileData();
    }

    m_uiProgramID = CreateProgram(VertexShader, FragmentShader);

    if (pVSFile)
    {
        SoFileHelp::DeleteFile(pVSFile);
    }
    if (pPSFile)
    {
        SoFileHelp::DeleteFile(pPSFile);
    }

    if (m_uiProgramID)
    {
        m_uiVertexID = glGetAttribLocation(m_uiProgramID, "myVertex");
        m_uiUVID = glGetAttribLocation(m_uiProgramID, "myUV");
        m_uiMatWorldID = glGetUniformLocation(m_uiProgramID, "g_matWorld");
        m_uiMatProjectViewID = glGetUniformLocation(m_uiProgramID, "g_matProjectView");
        m_uiTexSamplerID = glGetUniformLocation(m_uiProgramID, "g_Texture");
    }
}
//--------------------------------------------------------------------------------------------------
GLShaderStandard::~GLShaderStandard()
{
    if (m_uiProgramID)
    {
        glDeleteProgram(m_uiProgramID);
        m_uiProgramID = 0;
    }
}
//--------------------------------------------------------------------------------------------------
void GLShaderStandard::ProcessRender(void* pParam) const
{
    if (m_uiProgramID == 0)
    {
        return;
    }

    GLShaderStandardParam* pStandardParam = (GLShaderStandardParam*)pParam;

    glUseProgram(m_uiProgramID);

    glVertexAttribPointer(m_uiVertexID, 3, GL_FLOAT, GL_FALSE, pStandardParam->nSizeofVertexStruct, pStandardParam->pVertexArray);
    glEnableVertexAttribArray(m_uiVertexID);
    glVertexAttribPointer(m_uiUVID, 2, GL_FLOAT, GL_FALSE, pStandardParam->nSizeofVertexStruct, pStandardParam->pVertexArray+10);
    glEnableVertexAttribArray(m_uiUVID);

    glUniformMatrix4fv(m_uiMatWorldID, 1, GL_FALSE, (float*)(pStandardParam->pMatWorld->m));
    glUniformMatrix4fv(m_uiMatProjectViewID, 1, GL_FALSE, (float*)(pStandardParam->pMatProjectView->m));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pStandardParam->uiTextureID);
    // Set the sampler to texture unit 0
    glUniform1i(m_uiTexSamplerID, 0);

    glDrawElements(GL_TRIANGLES, pStandardParam->nIndexCount, GL_UNSIGNED_SHORT, pStandardParam->pIndexArray);
}
//--------------------------------------------------------------------------------------------------
