package com.ggui.swoosh.fidemo;

import android.opengl.GLSurfaceView;
import android.util.Log;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainGLRenderer implements GLSurfaceView.Renderer
{

    public void onSurfaceCreated(GL10 unused, EGLConfig config)
    {
        Log.i("android", "MainGLRenderer.onSurfaceCreated : begin");
        Cpp2JavaLibNative.AndroidAdepterOnRenderSurfaceCreated();
        Log.i("android", "MainGLRenderer.onSurfaceCreated : end");
    }

    public void onSurfaceChanged(GL10 unused, int width, int height)
    {
        Log.i("android", "MainGLRenderer.onSurfaceChanged : begin");
        Cpp2JavaLibNative.AndroidAdepterOnRenderSurfaceChanged(width, height);
        Log.i("android", "MainGLRenderer.onSurfaceChanged : end");
    }

    public void onDrawFrame(GL10 unused)
    {
        Cpp2JavaLibNative.AndroidAdepterOnRenderDrawFrame();
    }

}
