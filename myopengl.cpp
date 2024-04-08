#include "myopengl.h"

MyOpenGL::MyOpenGL(QWidget *parent)
    : QOpenGLWidget{parent}
{
    // 定时器任务
    QTimer *timer = new QTimer;
    // 定时器信号与槽
    connect(timer, &QTimer::timeout, this, &MyOpenGL::paintGL);
    // 定时器启动
    timer->start((1.0 / fps) * 100);
    // 设置鼠标追踪
    this->setMouseTracking(true);

}

// 重载Qt鼠标移动事件
void MyOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    LAppDelegate::GetInstance()->GetView()->OnTouchesMoved(event->x(), event->y());
    update();
    event->ignore();
}

void MyOpenGL::mousePressEvent(QMouseEvent *event)
{
    LAppDelegate::GetInstance()->GetView()->OnTouchesBegan(event->x(), event->y());
}

void MyOpenGL::mouseReleaseEvent(QMouseEvent *event)
{
    LAppDelegate::GetInstance()->GetView()->OnTouchesEnded(event->x(), event->y());
}

void MyOpenGL::initializeGL()
{
    LAppDelegate::GetInstance()->Initialize(this);
}

void MyOpenGL::resizeGL(int w, int h)
{
    LAppDelegate::GetInstance()->resize(w, h);
}

void MyOpenGL::paintGL()
{
    LAppDelegate::GetInstance()->update();
}
