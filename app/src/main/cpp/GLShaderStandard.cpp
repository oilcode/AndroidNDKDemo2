//--------------------------------------------------------------------------------------------------
#include "GLShaderStandard.h"
#include "SoFileHelp.h"
#include "GLCamera.h"
//--------------------------------------------------------------------------------------------------
GLShaderStandard::GLShaderStandard()
:m_uiProgramID(0)
,m_uiVertexID(0)
,m_uiUVID(0)
,m_uiMatWorldID(0)
,m_uiMatProjectViewID(0)
,m_uiTexSamplerID(0)
{

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
void GLShaderStandard::ReCreateGLResource()
{
    m_uiProgramID = 0;
    m_uiVertexID = 0;
    m_uiUVID = 0;
    m_uiMatWorldID = 0;
    m_uiMatProjectViewID = 0;
    m_uiTexSamplerID = 0;

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
        m_uiVertexID = (GLuint)glGetAttribLocation(m_uiProgramID, "myVertex");
        m_uiUVID = (GLuint)glGetAttribLocation(m_uiProgramID, "myUV");
        m_uiMatWorldID = (GLuint)glGetUniformLocation(m_uiProgramID, "g_matWorld");
        m_uiMatProjectViewID = (GLuint)glGetUniformLocation(m_uiProgramID, "g_matProjectView");
        m_uiTexSamplerID = (GLuint)glGetUniformLocation(m_uiProgramID, "g_Texture");
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
    const SoMathMatrix4& kMatProjView = GLCamera::Get()->GetMatProjView();

    glUseProgram(m_uiProgramID);

    glVertexAttribPointer(m_uiVertexID, 3, GL_FLOAT, GL_FALSE, pStandardParam->nSizeofVertexStruct, pStandardParam->pVertexArray+pStandardParam->nVertexOffset);
    glEnableVertexAttribArray(m_uiVertexID);
    glVertexAttribPointer(m_uiUVID, 2, GL_FLOAT, GL_FALSE, pStandardParam->nSizeofVertexStruct, pStandardParam->pVertexArray+pStandardParam->nUVOffset);
    glEnableVertexAttribArray(m_uiUVID);

    glUniformMatrix4fv(m_uiMatWorldID, 1, GL_FALSE, (float*)(pStandardParam->pMatWorld->m));
    glUniformMatrix4fv(m_uiMatProjectViewID, 1, GL_FALSE, (float*)(kMatProjView.m));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pStandardParam->uiTextureID);
    // Set the sampler to texture unit 0
    glUniform1i(m_uiTexSamplerID, 0);

    glDrawElements(GL_TRIANGLES, pStandardParam->nIndexCount, GL_UNSIGNED_SHORT, pStandardParam->pIndexArray);
}
//--------------------------------------------------------------------------------------------------
