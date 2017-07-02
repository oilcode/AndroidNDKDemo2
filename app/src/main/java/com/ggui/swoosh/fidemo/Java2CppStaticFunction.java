package com.ggui.swoosh.fidemo;

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;

public class Java2CppStaticFunction
{
    public static Context myActivity;

    static void showMessageBox(String title, String message)
    {
        Dialog myDialog = new AlertDialog.Builder(myActivity).
                setTitle(title).
                setMessage(message).
                create();
        myDialog.show();
    }
}
