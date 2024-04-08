#ifndef MYOPENGL_H
#define MYOPENGL_H

#pragma once

#include "live2d/LAppDelegate.hpp"
#include "live2d/LAppView.hpp"
#include "live2d/LAppPal.hpp"
#include "live2d/LAppLive2DManager.hpp"
#include "live2d/LAppDefine.hpp"

#include "qheaders.h"

class MyOpenGL : public QOpenGLWidget
{
public:
    explicit MyOpenGL(QWidget *parent = nullptr);

    int fps = 60;   // 帧数设置，后续可以提供设置接口

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    // 重载函数
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:
};

#endif // MYOPENGL_H
