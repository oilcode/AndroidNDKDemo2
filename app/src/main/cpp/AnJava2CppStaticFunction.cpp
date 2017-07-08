//--------------------------------------------------------------------------------------------------
#include "AnJava2CppStaticFunction.h"
//--------------------------------------------------------------------------------------------------
JavaVM* AnJava2CppStaticFunction::ms_pJavaVM = 0;
int AnJava2CppStaticFunction::ms_nJNIVersion = JNI_VERSION_1_4;
//--------------------------------------------------------------------------------------------------
void AnJava2CppStaticFunction::InitJava2CppStaticFunction(JavaVM* pJavaVM)
{
    ms_pJavaVM = pJavaVM;
}
//--------------------------------------------------------------------------------------------------
int AnJava2CppStaticFunction::GetMyJNIVersion()
{
    return ms_nJNIVersion;
}
//--------------------------------------------------------------------------------------------------
void AnJava2CppStaticFunction::ShowMessageBox(const char* szTitle, const char* szMessage)
{
    JNIEnv* pJniEnv = 0;
    ms_pJavaVM->GetEnv((void**)&pJniEnv, ms_nJNIVersion);

    jclass kJavaClass = pJniEnv->FindClass("com/ggui/swoosh/fidemo/Java2CppStaticFunction");
    if (kJavaClass == 0)
    {
        return;
    }

    jmethodID kMethodID = pJniEnv->GetStaticMethodID(kJavaClass, "ShowMessageBox", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (kMethodID == 0)
    {
        return;
    }

    jstring strTitle = pJniEnv->NewStringUTF(szTitle);
    jstring strMessage = pJniEnv->NewStringUTF(szMessage);
    pJniEnv->CallStaticVoidMethod(kJavaClass, kMethodID, strTitle, strMessage);

    pJniEnv->DeleteLocalRef(kJavaClass);
    pJniEnv->DeleteLocalRef(strTitle);
    pJniEnv->DeleteLocalRef(strMessage);
}
//--------------------------------------------------------------------------------------------------
