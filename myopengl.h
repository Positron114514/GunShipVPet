#ifndef MYOPENGL_H
#define MYOPENGL_H

#pragma once

#include "live2d/LAppDelegate.hpp"
#include "live2d/LAppView.hpp"
#include "live2d/LAppPal.hpp"
#include "live2d/LAppLive2DManager.hpp"
#include "live2d/LAppDefine.hpp"

#include "qheaders.h"
#include "vpetinterface.h"

class MyOpenGL : public QOpenGLWidget
{
public:
    explicit MyOpenGL(QWidget *parent = nullptr);
    ~MyOpenGL();

    VPetInterface *p = nullptr;     // 父对象存储

    void setOpenGLFps();

    // 重载函数
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QTimer * timer;
    bool isDragging = false;
    QPointF originPos;

signals:
};

#endif // MYOPENGL_H
