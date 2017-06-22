package com.ggui.swoosh.fidemo;

import android.opengl.GLSurfaceView;
import android.content.Context;
import android.view.MotionEvent;

public class MainGLSurfaceView extends GLSurfaceView
{
    private MainGLRenderer m_Renderer;

    public MainGLSurfaceView(Context context)
    {
        super(context);

        // Create an OpenGL ES 2.0 context
        setEGLContextClientVersion(2);

        m_Renderer = new MainGLRenderer();

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(m_Renderer);

        // Render the view only when there is a change in the drawing data
        //setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    @Override
    public boolean onTouchEvent(final MotionEvent pMotionEvent)
    {
        int nActionType = pMotionEvent.getAction() & MotionEvent.ACTION_MASK;
        switch (nActionType)
        {
            case MotionEvent.ACTION_DOWN:
            {
                float fx = pMotionEvent.getX();
                float fy = pMotionEvent.getY();
                Cpp2JavaLibNative.AndroidAdepterOnViewTouchDown(fx, fy);
            }
            break;
            case MotionEvent.ACTION_MOVE:
            {
                float fx = pMotionEvent.getX();
                float fy = pMotionEvent.getY();
                Cpp2JavaLibNative.AndroidAdepterOnViewTouchMove(fx, fy);
            }
            break;
            case MotionEvent.ACTION_UP:
            {
                float fx = pMotionEvent.getX();
                float fy = pMotionEvent.getY();
                Cpp2JavaLibNative.AndroidAdepterOnViewTouchUp(fx, fy);
            }
            break;
        }

        return true;
    }
}
