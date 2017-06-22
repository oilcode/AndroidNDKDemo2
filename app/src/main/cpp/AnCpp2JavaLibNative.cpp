//--------------------------------------------------------------------------------------------------
#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include "AndroidAdepter.h"
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnActivityCreate(JNIEnv *env, jobject obj)
{
    AndroidAdepter::onActivityCreate();
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnActivityPause(JNIEnv *env, jobject obj)
{
    AndroidAdepter::onActivityPause();
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnActivityResume(JNIEnv *env, jobject obj)
{
    AndroidAdepter::onActivityResume();
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnViewTouchDown(JNIEnv *env, jobject obj, float fx, float fy)
{
    AndroidAdepter::onViewTouchDown(fx, fy);
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnViewTouchMove(JNIEnv *env, jobject obj, float fx, float fy)
{
    AndroidAdepter::onViewTouchMove(fx, fy);
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnViewTouchUp(JNIEnv *env, jobject obj, float fx, float fy)
{
    AndroidAdepter::onViewTouchUp(fx, fy);
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnRenderSurfaceCreated(JNIEnv *env, jobject obj)
{
    AndroidAdepter::onRenderSurfaceCreated();
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnRenderSurfaceChanged(JNIEnv *env, jobject obj, jint width, jint height)
{
    AndroidAdepter::onRenderSurfaceChanged(width, height);
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterOnRenderDrawFrame(JNIEnv *env, jobject obj)
{
    AndroidAdepter::onRenderDrawFrame();
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterSetAssetManager(JNIEnv *env, jobject obj, jobject assetManager)
{
    AndroidAdepter::setAssetManager(AAssetManager_fromJava(env, assetManager));
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterSetInternalPath(JNIEnv *env, jobject obj, jstring path)
{
    const char* szPath = env->GetStringUTFChars(path, 0);
    AndroidAdepter::setInternalPath(szPath);
}
//--------------------------------------------------------------------------------------------------
extern "C"
JNIEXPORT void JNICALL
Java_com_ggui_swoosh_fidemo_Cpp2JavaLibNative_AndroidAdepterSetExternalPath(JNIEnv *env, jobject obj, jstring path)
{
    const char* szPath = env->GetStringUTFChars(path, 0);
    AndroidAdepter::setExternalPath(szPath);
}
//--------------------------------------------------------------------------------------------------

