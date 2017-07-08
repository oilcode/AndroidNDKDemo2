//--------------------------------------------------------------------------------------------------
#ifndef _AnJava2CppStaticFunction_h_
#define _AnJava2CppStaticFunction_h_
//--------------------------------------------------------------------------------------------------
#include <jni.h>
//--------------------------------------------------------------------------------------------------
class AnJava2CppStaticFunction
{
public:
    static void InitJava2CppStaticFunction(JavaVM* pJavaVM);
    static int GetMyJNIVersion();

    static void ShowMessageBox(const char* szTitle, const char* szMessage);

private:
    static JavaVM* ms_pJavaVM;
    static int ms_nJNIVersion;
};
//--------------------------------------------------------------------------------------------------
#endif //_AnJava2CppStaticFunction_h_
//--------------------------------------------------------------------------------------------------
