#include "vpetinterface.h"
#include "ui_vpetinterface.h"
#include "settingsdialog.h"

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

VPetInterface::VPetInterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VPetInterface)
{
    ui->setupUi(this);

    this->resize(230, 460);

    // 设置窗体透明
    this->setWindowFlag(Qt::WindowType::MSWindowsOwnDC, false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::Tool);
    windowState = this->windowFlags();
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_ShowWithoutActivating);

    // 程序初始化
    setWindowOnTopState(true);
    setWheelZoomState(true);

    // 初始化托盘图标
    InitializeSystemTray();
}

VPetInterface::~VPetInterface()
{
    qDebug() << QT_BACKGROUND_LOG << "VPetInterface released";
    delete ui;
}

void VPetInterface::InitializeSystemTray()
{
    trayMenu = new QMenu(this);

    // 系统托盘相关设置
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/ico/resources/icons/logo-tmp.ico"));
    trayIcon->setToolTip("虚拟桌宠");

    actionQuit = new QAction("退出", this);
    actionSettings = new QAction("设置", this);

    // action 信号与槽
    connect(actionQuit, &QAction::triggered, this, &QApplication::quit);
    connect(actionSettings, &QAction::triggered, this, &VPetInterface::onSettingsClicked);

    // 菜单设置：添加actions时，从上往下
    trayMenu->addAction(actionSettings);
    trayMenu->addAction(actionQuit);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void VPetInterface::onSettingsClicked()
{
    qDebug() << QT_INTERFACE_LOG << "Settings Action triggered";

    SettingsDialog settings(this);
    int returnStatus = settings.exec();

    qDebug() << QT_INTERFACE_LOG << "Settings quited, return value" << returnStatus;
}

void VPetInterface::setWheelZoomState(bool state)
{
    isWheelZoomActive = state;

    qDebug() << QT_BACKGROUND_LOG << "wheel zoom active?" << state;
}

void VPetInterface::setWindowOnTopState(bool state)
{
    isWindowOnTop = state;

    if(state)
        this->setWindowFlag(Qt::WindowStaysOnTopHint);   // 窗口置顶
    else
        this->setWindowFlags(windowState);  // 取消窗口置顶

    this->activateWindow(); // 设置窗口激活

    qDebug() << QT_BACKGROUND_LOG << "window on top state" << state;
}

bool VPetInterface::wheelZoomState()
{
    return isWheelZoomActive;
}

bool VPetInterface::windowOnTopState()
{
    return isWindowOnTop;
}

void VPetInterface::resizeWindow(int width, int height)
{
    QSize orgSize = this->size();

    this->resize(width, height);

    QSize l2dSize = ui->live2dWidget->size();
    int dw = l2dSize.width() - orgSize.width();
    int dh = l2dSize.height() - orgSize.height();

    ui->live2dWidget->resizeGL(width + dw, height + dh);
}

void VPetInterface::resizeWindow(QSize size)
{
    QSize orgSize = this->size();

    this->resize(size);

    QSize l2dSize = ui->live2dWidget->size();
    int dw = l2dSize.width() - orgSize.width();
    int dh = l2dSize.height() - orgSize.height();

    ui->live2dWidget->resizeGL(size.width() + dw, size.height() + dh);
}
