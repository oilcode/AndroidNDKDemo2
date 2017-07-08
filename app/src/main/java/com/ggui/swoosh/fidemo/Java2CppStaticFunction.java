package com.ggui.swoosh.fidemo;


public class Java2CppStaticFunction
{
    public static MainActivity myActivity;


    public static void ShowMessageBox(String title, String message)
    {
        myActivity.ShowMessageBox(title, message);
    }
}
