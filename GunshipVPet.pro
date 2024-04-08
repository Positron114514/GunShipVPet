QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    live2d/LAppAllocator.cpp \
    live2d/LAppDefine.cpp \
    live2d/LAppDelegate.cpp \
    live2d/LAppLive2DManager.cpp \
    live2d/LAppModel.cpp \
    live2d/LAppPal.cpp \
    live2d/LAppSprite.cpp \
    live2d/LAppTextureManager.cpp \
    live2d/LAppView.cpp \
    live2d/LAppWavFileHandler.cpp \
    live2d/TouchManager.cpp \
    main.cpp \
    myopengl.cpp \
    vpetinterface.cpp

HEADERS += \
    live2d/LAppAllocator.hpp \
    live2d/LAppDefine.hpp \
    live2d/LAppDelegate.hpp \
    live2d/LAppLive2DManager.hpp \
    live2d/LAppModel.hpp \
    live2d/LAppPal.hpp \
    live2d/LAppSprite.hpp \
    live2d/LAppTextureManager.hpp \
    live2d/LAppView.hpp \
    live2d/LAppWavFileHandler.hpp \
    live2d/TouchManager.hpp \
    myopengl.h \
    qheaders.h \
    vpetinterface.h

FORMS += \
    vpetinterface.ui

# OpenGL相关
QT += opengl
QT += core gui openglwidgets
QT += widgets

# Configurations for Live2D SDK

# SDK include路径
INCLUDEPATH += $$PWD/sdk/Framework/src \
    $$PWD/sdk/glew/include \
    $$PWD/sdk/glfw/include \
    $$PWD/sdk/Core/include \
    $$PWD/sdk/stb

# SDK库路径
LIBS += $$PWD/sdk/Framework/lib/Framework.lib \
    $$PWD/sdk/glew/lib/libglew32.lib \
    $$PWD/sdk/glfw/lib/glfw3.lib \
    $$PWD/sdk/Core/lib/windows/x86_64/143/Live2DCubismCore_MT.lib

# 启用GL
DEFINES += CSM_TARGET_WIN_GL

# 解决默认库冲突问题
QMAKE_CXXFLAGS_RELEASE = -O2 -MD -GL
QMAKE_CXXFLAGS_DEBUG = -Zi -MDd

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
