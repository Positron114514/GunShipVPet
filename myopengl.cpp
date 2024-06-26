#include "myopengl.h"
#include "filehandler.h"
#include "live2d/LAppModel.hpp"

#pragma comment (lib, "Dwmapi.lib")

MyOpenGL::MyOpenGL(QWidget *parent)
    : QOpenGLWidget{parent}
{
    p = (VPetInterface*) this->parentWidget(); // 新增变量存父对象

    // 定时器任务
    timer = new QTimer(this);
    // 定时器信号与槽
    connect(timer, &QTimer::timeout, this, &MyOpenGL::paintGL);
    connect(timer, &QTimer::timeout, this, [=]() {
        update();
    });
    // 定时器启动
    timer->start((1.0 / p->fps()) * 100);
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
    // LAppDelegate::GetInstance()->GetView()->
    //     OnTouchesMoved(event->globalPosition().x(), event->globalPosition().y());
    update();

    if(isDragging)
    {
        QPointF cursor = event->globalPosition();

        int moveX = cursor.x() - originPos.x();
        int moveY = cursor.y() - originPos.y();

        // qDebug() << QT_DEBUG_OUTPUT << "dx=" << moveX << " dy=" << moveY;

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
    // LAppDelegate::GetInstance()->GetView()->
    //     OnTouchesMoved(event->globalPosition().x(), event->globalPosition().y());

    if(event->buttons() == Qt::LeftButton)
    {
        isDragging = true;
        originPos = event->globalPosition();
    } else if(event->buttons() == Qt::RightButton) {
        int modelNum = FileHandler::getModelNum();
        p->setModelIndex((p->modelIndex() + 1) % modelNum);
    } else {
        p->setWindowOnTopState(false, false);
        p->transparentMouseEvent();
    }
}

void MyOpenGL::mouseReleaseEvent(QMouseEvent *event)
{
    LAppDelegate::GetInstance()->GetView()->
        OnTouchesEnded(event->pos().x(), event->pos().y());

    isDragging = false;
}

void MyOpenGL::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() != Qt::LeftButton)
        return;

    if(!p->LLMEnable())
        return; // 若功能未开启，则不执行新建窗口

    // 设置只能存在一个chat窗口
    if(chat == nullptr)
    {
        chat = new ChatWindow(p);
        chat->show();
        connect(chat, &ChatWindow::windowClose, this, &MyOpenGL::chatWindowDestroy);
        qDebug() << QT_INTERFACE_LOG << "ChatWindow created";
    }

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
        if(this->width() >= MAX_MODEL_WIDTH)
        {
            qDebug() << QT_BACKGROUND_LOG << "invalid zoom: current size" << this->size();
            return;
        }

        p->resizeWindow(p->width() + 5, p->height() + 5 * MODEL_PROPORTION);

        return;
    }

    if(event->angleDelta().y() < 0)
    {
        if(this->width() <= MIN_MODEL_WIDTH)
        {
            qDebug() << QT_BACKGROUND_LOG << "invalid zoom: current size" << this->size();
            return;
        }

        p->resizeWindow(p->width() - 5, p->height() - 5 * MODEL_PROPORTION);

        return;
    }
}

void MyOpenGL::setOpenGLFps()
{
    timer->setInterval((1.0 / p->fps()) * 100);
}

// // 会出现恶性bug
// void MyOpenGL::transparentMouse()
// {
//     HWND hWnd=(HWND)(this->winId());
//     POINT pt;
//     GetCursorPos(&pt);
//     ScreenToClient(hWnd,&pt);
//     long double x, y;
//     x = pt.x * 2.0 / width() - 1.0;
//     y = 1.0 - pt.y * 2.0 / height();
//     bool res = LAppModel::GetInstance()->isMouseOnModel(x, y);
//     if(res)
//         SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd,GWL_EXSTYLE)&(~WS_EX_TRANSPARENT));
//     else
//         SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLongW(hWnd,GWL_EXSTYLE)|WS_EX_TRANSPARENT);
//     DragAcceptFiles(hWnd,true);
// }

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
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void MyOpenGL::setChatWindowP(ChatWindow *window)
{
    chat = window;
}

ChatWindow * MyOpenGL::chatWindowP()
{
    return chat;
}

void MyOpenGL::chatWindowDestroy()
{
    delete chat;
    chat = nullptr;
}
