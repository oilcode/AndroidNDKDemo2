# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Android
             src/main/cpp/AnCpp2JavaLibNative.cpp
             src/main/cpp/AndroidAdepter.cpp
			 src/main/cpp/AnFileAsset.cpp
			 src/main/cpp/AnFileExternal.cpp
			 src/main/cpp/AnFileInternal.cpp
			 src/main/cpp/AnJava2CppStaticFunction.cpp
			 src/main/cpp/AnInputMsgDefine.cpp
			 src/main/cpp/AnInputMsgDispatch.cpp

             # GLcode
             src/main/cpp/GLBaseInclude.cpp
             src/main/cpp/GLCamera.cpp
             src/main/cpp/GLCameraBase.cpp
			 src/main/cpp/GLCameraUI.cpp
             src/main/cpp/GLLogicFlowHelp.cpp
             src/main/cpp/GLManager.cpp
             src/main/cpp/GLModelCube.cpp
			 src/main/cpp/GLModelRect.cpp
             src/main/cpp/GLShaderBase.cpp
			 src/main/cpp/GLShaderGGUI.cpp
             src/main/cpp/GLShaderManager.cpp
             src/main/cpp/GLShaderStandard.cpp
             src/main/cpp/GLTexture.cpp
             src/main/cpp/GLTextureManager.cpp

             # SoBase
             src/main/cpp/SoArray.cpp
             src/main/cpp/SoArrayUID.cpp
             src/main/cpp/SoFile.cpp
			 src/main/cpp/SoFileHelp.cpp
			 src/main/cpp/SoImageDefine.cpp
			 src/main/cpp/SoImageHelp.cpp
			 src/main/cpp/SoImagePNG.cpp
			 src/main/cpp/SoMath.cpp
			 src/main/cpp/SoMathFloat2.cpp
			 src/main/cpp/SoMathFloat3.cpp
			 src/main/cpp/SoMathFloat4.cpp
			 src/main/cpp/SoMathInt2.cpp
			 src/main/cpp/SoMathInt3.cpp
			 src/main/cpp/SoMathMatrix3.cpp
			 src/main/cpp/SoMathMatrix4.cpp
			 src/main/cpp/SoString.cpp
			 src/main/cpp/SoTinyString.cpp
			 src/main/cpp/SoStringHelp.cpp
			 src/main/cpp/SoCmdLineHelp.cpp

            )


add_library( png
             STATIC
             src/main/thirdparty/02_png/png.c
             src/main/thirdparty/02_png/pngerror.c
             src/main/thirdparty/02_png/pngget.c
             src/main/thirdparty/02_png/pngmem.c
             src/main/thirdparty/02_png/pngpread.c
             src/main/thirdparty/02_png/pngread.c
             src/main/thirdparty/02_png/pngrio.c
             src/main/thirdparty/02_png/pngrtran.c
             src/main/thirdparty/02_png/pngrutil.c
             src/main/thirdparty/02_png/pngset.c
             src/main/thirdparty/02_png/pngtest.c
             src/main/thirdparty/02_png/pngtrans.c
             src/main/thirdparty/02_png/pngwio.c
             src/main/thirdparty/02_png/pngwrite.c
             src/main/thirdparty/02_png/pngwtran.c
             src/main/thirdparty/02_png/pngwutil.c
            )

add_library( GGUI
             STATIC
             src/main/cpp/GGUIAnimation.cpp
             src/main/cpp/GGUIBaseInclude.cpp
             src/main/cpp/GGUIColor.cpp
             src/main/cpp/GGUIComponentText.cpp
             src/main/cpp/GGUIEvent.cpp
             src/main/cpp/GGUIFileGGM.cpp
             src/main/cpp/GGUIFuncHelp.cpp
             src/main/cpp/GGUIImageset.cpp
             src/main/cpp/GGUIImagesetIO.cpp
             src/main/cpp/GGUIImagesetManager.cpp
             src/main/cpp/GGUIInputMsg.cpp
             src/main/cpp/GGUIInputState.cpp
             src/main/cpp/GGUILogHelp.cpp
             src/main/cpp/GGUILogicFlowHelp.cpp
             src/main/cpp/GGUIPanelManager.cpp
             src/main/cpp/GGUIPoint.cpp
             src/main/cpp/GGUIRect.cpp
             src/main/cpp/GGUIRenderHelp.cpp
             src/main/cpp/GGUIRenderManager.cpp
             src/main/cpp/GGUIRichTextDefine.cpp
             src/main/cpp/GGUIUserDefine.cpp
             src/main/cpp/GGUIWindowBase.cpp
             src/main/cpp/GGUIWindowButton.cpp
             src/main/cpp/GGUIWindowComboBox.cpp
             src/main/cpp/GGUIWindowContainer.cpp
             src/main/cpp/GGUIWindowFactory.cpp
             src/main/cpp/GGUIWindowImage.cpp
             src/main/cpp/GGUIWindowListBox.cpp
             src/main/cpp/GGUIWindowPanel.cpp
             src/main/cpp/GGUIWindowProcessBar.cpp
             src/main/cpp/GGUIWindowRichText.cpp
             src/main/cpp/GGUIWindowScrollBar.cpp
             src/main/cpp/GGUIWindowText.cpp
           )

add_library( NwCode
             STATIC
             src/main/cpp/NwBaseInclude.cpp
             src/main/cpp/NwLogicFlowHelp.cpp
             src/main/cpp/NwSPKLogic.cpp
             src/main/cpp/NwSPKProcedure.cpp
             src/main/cpp/NwUIMain.cpp
             src/main/cpp/NwUISPK.cpp
           )


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # 这里奇怪的参数，是让PNG这个库直接拷贝到NativeLib里面。
                       "-Wl,--whole-archive"
                       png
                       GGUI
                       NwCode
                       "-Wl,--no-whole-archive"


                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       android
                       GLESv2
                       z           # zlib
                      )
