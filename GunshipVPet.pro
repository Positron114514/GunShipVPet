QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatmessage.cpp \
    chatwindow.cpp \
    configsaver.cpp \
    customdir.cpp \
    filehandler.cpp \
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
    llminterface.cpp \
    loghandler.cpp \
    main.cpp \
    myopengl.cpp \
    optimizedslider.cpp \
    pythonhandler.cpp \
    qssloader.cpp \
    settingsdialog.cpp \
    ttshandler.cpp \
    vpetinterface.cpp \
    llmhandler.cpp


HEADERS += \
    FileHandler.hpp \
    chatmessage.h \
    chatwindow.h \
    configsaver.h \
    customdir.h \
    filehandler.h \
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
    llminterface.h \
    loghandler.h \
    myopengl.h \
    optimizedslider.h \
    pythonhandler.h \
    qheaders.h \
    qssloader.h \
    settingsdialog.h \
    ttshandler.h \
    vpetinterface.h \
    llmhandler.h

FORMS += \
    chatwindow.ui \
    settingsdialog.ui \
    vpetinterface.ui

# 设置编译后图标
RC_FILE += resources/icons/logo.rc

# OpenGL相关
QT += opengl
QT += core gui openglwidgets
QT += widgets

# media
QT += multimedia


# Configurations for Live2D SDK

# SDK include路径
INCLUDEPATH += $$PWD/sdk/Framework/src \
    $$PWD/sdk/glew/include \
    $$PWD/sdk/glfw/include \
    $$PWD/sdk/Core/include \
    $$PWD/sdk/stb \
    $$PWD/sdk/python/include

# SDK库路径
LIBS += $$PWD/sdk/Framework/lib/Framework.lib \
    $$PWD/sdk/glew/lib/libglew32.lib \
    $$PWD/sdk/glfw/lib/glfw3.lib \
    $$PWD/sdk/Core/lib/windows/x86_64/143/Live2DCubismCore_MT.lib \
    -L$$PWD/sdk/python/libs -lpython38

DEPENDPATH += $$PWD/python3.8.10/libs

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

DISTFILES += \
    todolist.md

# python 路径
# 后续需要改动 (不同机器上路径不同)
# 改完了, 现在要求项目强制安装一个 python3.8.10
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sdk/python/libs -lpython38
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sdk/python/libs -lpython38d

