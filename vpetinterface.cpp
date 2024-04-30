#include "vpetinterface.h"
#include "ui_vpetinterface.h"
#include "settingsdialog.h"
#include "configsaver.h"
#include "customdir.h"
#include "floatbuttonwidget.h"

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

    // 窗体初始化设置
    this->setWindowTitle("GunshipVPet虚拟桌宠");
    this->setWindowIcon(QIcon(":/ico/resources/icons/logo-temp.ico"));
    this->setFont(QFont(":/font/MiSans-Regular.ttf"));

    // 窗体几何设置
    this->resize(DEFAULT_MODEL_WIDTH, DEFAULT_MODEL_WIDTH * MODEL_PROPORTION);
    this->move(1350, 650);  // 窗体默认放右下角

    // 设置窗体透明
    this->setWindowFlag(Qt::WindowType::MSWindowsOwnDC, false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_ShowWithoutActivating);

    // 设置初始化
    setWindowOnTopState(true);
    setWheelZoomState(true);

    // 初始化交互控件
    InitializeInterface();

    // 初始化用户文件目录
    InitializeAppDir();

    // 初始化托盘图标
    InitializeSystemTray();

    // 初始化配置文件
    ConfigSaver::loadConfig(this);
}

VPetInterface::~VPetInterface()
{
    ConfigSaver::writeConfig(this); // 保存配置文件
    qDebug() << QT_BACKGROUND_LOG << "VPetInterface released";
    delete ui;
}

void VPetInterface::InitializeInterface()
{
    // FloatButtonWidget *w = new FloatButtonWidget;
    // ui->live2dWidget->layout()->addWidget(w);
}

void VPetInterface::InitializeSystemTray()
{
    trayMenu = new QMenu(this);

    // 系统托盘相关设置
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/ico/resources/icons/logo-tmp.ico"));
    trayIcon->setToolTip("虚拟桌宠");

    connect(trayIcon, &QSystemTrayIcon::activated, this, &VPetInterface::onTrayIconActivated);

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

void VPetInterface::InitializeAppDir()
{
    QDir dir(CustomDir::customDir());
    if(!dir.exists())
        QDir().mkdir(CustomDir::customDir());  // 不存在则创建文件夹
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
        this->setWindowFlag(Qt::WindowStaysOnTopHint, true);   // 窗口置顶
    else
        this->setWindowFlag(Qt::WindowStaysOnTopHint, false);  // 取消窗口置顶

    this->show();   // 设置窗口出现

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

void VPetInterface::setFps(int fps)
{
    curFps = fps;
    ui->live2dWidget->setOpenGLFps();
    qDebug() << QT_INTERFACE_LOG << "set fps" << fps;
}

int VPetInterface::fps()
{
    return curFps;
}

void VPetInterface::setModelIndex(int index)
{
    curModel = index;
    if(index <= FileHandler::getModelNum())
        FileHandler::switchModel(index);
    else
    {
        FileHandler::switchModel(DEFAULT_MODEL);
        curModel = DEFAULT_MODEL;
        qDebug() << QT_BACKGROUND_LOG << "model overwrite";
    }
    qDebug() << QT_INTERFACE_LOG << "set model index" << index;
}

int VPetInterface::modelIndex()
{
    return curModel;
}

void VPetInterface::regAutoRun()
{
    QString appPath = QApplication::applicationFilePath();

    QSettings settings(REG_AUTO_RUN, QSettings::Registry64Format);

    // 获取app名
    QFileInfo info(appPath);
    QString name = info.baseName();

    // 检查是否有更换路径
    QString oldPath = settings.value(name).toString();
    QString newPath = QDir::toNativeSeparators(appPath);

    if(oldPath != newPath)
        settings.setValue(name, newPath);
}

bool VPetInterface::isRegAutoRun()
{
    QString appPath = QApplication::applicationFilePath();
    QSettings settings(REG_AUTO_RUN, QSettings::Registry64Format);
    QFileInfo fInfo(appPath);
    QString name = fInfo.baseName();
    QString oldPath = settings.value(name).toString();
    QString newPath = QDir::toNativeSeparators(appPath);
    return (settings.contains(name) && newPath == oldPath);
}

void VPetInterface::lnkAutoRun()
{
    QString startupPath = CustomDir::autoRunLnkDir();
    QString srcFile = QApplication::applicationFilePath();

    if(QFile(startupPath).exists())
        QFile::remove(startupPath);

    QFile::link(srcFile, startupPath);
}

bool VPetInterface::isLnkAutoRun()
{
    QString startupPath = CustomDir::autoRunLnkDir();
    return QFile(startupPath).exists();
}

void VPetInterface::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        this->showNormal(); // 单击，显示桌宠本身
        break;
    case QSystemTrayIcon::DoubleClick:
        onSettingsClicked();    // 双击，显示设置界面
        break;
    default:
        break;
    }
}
