#include "myopengl.h"

#pragma comment (lib, "Dwmapi.lib")

MyOpenGL::MyOpenGL(QWidget *parent)
    : QOpenGLWidget{parent}
{
    p = (VPetInterface*) this->parentWidget(); // 新增变量存父对象

    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // 定时器任务
    QTimer *timer = new QTimer;
    // 定时器信号与槽
    connect(timer, &QTimer::timeout, this, &MyOpenGL::paintGL);
    // 定时器启动
    timer->start((1.0 / fps) * 100);
    // 设置鼠标追踪
    this->setMouseTracking(true);

}

MyOpenGL::~MyOpenGL()
{
    qDebug() << QT_BACKGROUND_LOG << "Live2D OpenGL released";
}

// 重载Qt鼠标移动事件
// 这里实现两个功能：
// 1.与live2d的交互
// 2.窗口移动事件的触发
void MyOpenGL::mouseMoveEvent(QMouseEvent *event)
{
    // live2d交互
    LAppDelegate::GetInstance()->GetView()->
        OnTouchesMoved(event->pos().x(), event->pos().y());
    update();

    if(isDragging)
    {
        QPointF cursor = event->globalPosition();

        int moveX = cursor.x() - originPos.x();
        int moveY = cursor.y() - originPos.y();

        qDebug() << QT_DEBUG_OUTPUT << "dx=" << moveX << " dy=" << moveY;

        QPointF window = p->pos();
        p->move(window.x() + moveX, window.y() + moveY);

        originPos = event->globalPosition();
    }

    event->ignore();
}

void MyOpenGL::mousePressEvent(QMouseEvent *event)
{
    // live2d交互
    LAppDelegate::GetInstance()->GetView()->
        OnTouchesBegan(event->pos().x(), event->pos().y());

    if(event->buttons() == Qt::LeftButton)
    {
        isDragging = true;
        originPos = event->globalPosition();
    }
}

void MyOpenGL::mouseReleaseEvent(QMouseEvent *event)
{
    LAppDelegate::GetInstance()->GetView()->
        OnTouchesEnded(event->pos().x(), event->pos().y());

    isDragging = false;
}

void MyOpenGL::wheelEvent(QWheelEvent *event)
{
    if(!p->wheelZoomState())
    {
        qDebug() << QT_BACKGROUND_LOG << "wheel zoom disabled";
        return;
    }

    // 修改为线性缩放
    if(event->angleDelta().y() > 0)
    {
        if(this->width() >= 500 || this->height() >= 1000)
        {
            qDebug() << QT_BACKGROUND_LOG << "invalid zoom: current size" << this->size();
            return;
        }

        p->resizeWindow(p->width() + 5, p->height() + 5);

        return;
    }

    if(event->angleDelta().y() < 0)
    {
        if(this->width() <= 120 || this->height() <= 240)
        {
            qDebug() << QT_BACKGROUND_LOG << "invalid zoom: current size" << this->size();
            return;
        }

        p->resizeWindow(p->width() - 5, p->height() - 5);

        return;
    }
}

// OpenGL相关重载
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
