package com.ggui.swoosh.fidemo;

import android.content.res.AssetManager;

public class Cpp2JavaLibNative
{
    public static void LoadLib()
    {
        System.loadLibrary("native-lib");
    }

    public static native void AndroidAdepterOnActivityCreate();
    public static native void AndroidAdepterOnActivityPause();
    public static native void AndroidAdepterOnActivityResume();
    public static native void AndroidAdepterOnViewTouchDown(float fx, float fy);
    public static native void AndroidAdepterOnViewTouchMove(float fx, float fy);
    public static native void AndroidAdepterOnViewTouchUp(float fx, float fy);
    public static native void AndroidAdepterOnRenderSurfaceCreated();
    public static native void AndroidAdepterOnRenderSurfaceChanged(int width, int height);
    public static native void AndroidAdepterOnRenderDrawFrame();
    public static native void AndroidAdepterSetAssetManager(final AssetManager assetManager);
    public static native void AndroidAdepterSetInternalPath(String strPath);
    public static native void AndroidAdepterSetExternalPath(String strPath);
}
