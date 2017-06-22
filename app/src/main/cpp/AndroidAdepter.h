//--------------------------------------------------------------------------------------------------
#ifndef _AndroidAdepter_h_
#define _AndroidAdepter_h_
//--------------------------------------------------------------------------------------------------
#include <android/asset_manager.h>
//--------------------------------------------------------------------------------------------------
class AndroidAdepter
{
public:
    static void onActivityCreate();
    static void onActivityPause();
    static void onActivityResume();

    static void onViewTouchDown(float fx, float fy);
    static void onViewTouchMove(float fx, float fy);
    static void onViewTouchUp(float fx, float fy);

    static void onRenderSurfaceCreated();
    static void onRenderSurfaceChanged(int width, int height);
    static void onRenderDrawFrame();

    static void setAssetManager(AAssetManager* pAssetMgr);
    static void setInternalPath(const char* szPath);
    static void setExternalPath(const char* szPath);
};
//--------------------------------------------------------------------------------------------------
#endif //_AndroidAdepter_h_
//--------------------------------------------------------------------------------------------------
