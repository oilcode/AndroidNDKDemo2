package com.ggui.swoosh.fidemo;

import android.app.AlertDialog;
import android.os.Handler;
import android.os.Message;

import java.lang.ref.WeakReference;

public class MainActivityHandler extends Handler
{
    public final static int MessageType_ShowDialog = 1;

    private WeakReference<MainActivity> m_myActivity;

    public MainActivityHandler(MainActivity myActivity)
    {
        m_myActivity = new WeakReference<MainActivity>(myActivity);
    }

    @Override
    public void handleMessage(Message msg)
    {
        switch (msg.what)
        {
            case MessageType_ShowDialog:
                MessageParam param = (MessageParam)msg.obj;
                doShowMessageBox(param.strTitle, param.strMessage);
                break;
        }
    }

    public void doShowMessageBox(String title, String message)
    {
        new AlertDialog.Builder(m_myActivity.get()).
                setTitle(title).
                setMessage(message).
                create().
                show();
    }

    public static class MessageParam
    {
        public String strTitle;
        public String strMessage;

        public MessageParam(String title, String message)
        {
            strTitle = title;
            strMessage = message;
        }
    }
}
