package com.ggui.swoosh.fidemo;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

public class MainActivity extends Activity
{
    private MainGLSurfaceView m_GLView;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        Log.i("Android", "MainActivity.onCreate : begin");
        super.onCreate(savedInstanceState);
        //
        Cpp2JavaLoadAllLib.LoadAllLib();
        //
        m_GLView = new MainGLSurfaceView(this);
        setContentView(m_GLView);
        //
        Cpp2JavaLibNative.AndroidAdepterSetAssetManager(getAssets());

        String internalPath = getFilesDir().getAbsolutePath();
        internalPath += "/";
        Log.i("Android", "InternalPath : " + internalPath);
        Cpp2JavaLibNative.AndroidAdepterSetInternalPath(internalPath);

        if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED))
        {
            String externalPath = Environment.getExternalStorageDirectory().getAbsolutePath();
            externalPath += "/";
            Log.i("Android", "ExternalPath : " + externalPath);
            Cpp2JavaLibNative.AndroidAdepterSetExternalPath(externalPath);
        }
        else
        {
            Log.i("Android", "ExternalPath : none");
        }

        Cpp2JavaLibNative.AndroidAdepterOnActivityCreate();
        Log.i("Android", "MainActivity.onCreate : end");
    }

    @Override
    protected void onPause()
    {
        Log.i("Android", "MainActivity.onPause : begin");
        super.onPause();
        m_GLView.onPause();
        Cpp2JavaLibNative.AndroidAdepterOnActivityPause();
        Log.i("Android", "MainActivity.onPause : end");
    }

    @Override
    protected void onResume()
    {
        Log.i("Android", "MainActivity.onResume : begin");
        super.onResume();
        m_GLView.onResume();
        Cpp2JavaLibNative.AndroidAdepterOnActivityResume();
        Log.i("Android", "MainActivity.onResume : end");
    }
}
