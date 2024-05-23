#include "vpetinterface.h"
#include "ui_vpetinterface.h"
#include "settingsdialog.h"
#include "configsaver.h"
#include "customdir.h"
#include "chatwindow.h"

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
    this->setWindowIcon(QIcon(":/ico/resources/icons/main-logo.ico"));
    this->setFont(QFont(":/font/MiSans-Regular.ttf"));

    QRect geo = QGuiApplication::primaryScreen()->geometry();

    // 窗体几何设置
    this->resize(DEFAULT_MODEL_WIDTH, DEFAULT_MODEL_WIDTH * MODEL_PROPORTION);
    this->move(geo.width() * DEFAULT_POS_PROPORTION, geo.height() * DEFAULT_POS_PROPORTION);  // 窗体默认放右下角

    // 设置窗体透明
    this->setWindowFlag(Qt::WindowType::MSWindowsOwnDC, false);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_ShowWithoutActivating);

    // this->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // 鼠标操作穿透测试

    // 设置初始化
    setWindowOnTopState(true);
    setWheelZoomState(true);

    // 初始化用户文件目录
    InitializeAppDir();

    // 初始化托盘图标
    InitializeSystemTray();

    // 初始化配置文件
    ConfigSaver::loadConfig(this);

    // 初始化自动保存
    InitializeAutoSaveService(AUTOSAVE_TIMEOUT);
}

VPetInterface::~VPetInterface()
{
    ConfigSaver::writeConfig(this); // 保存配置文件
    qDebug() << QT_BACKGROUND_LOG << "VPetInterface released";
    delete ui;
}

void VPetInterface::InitializeSystemTray()
{
    trayMenu = new QMenu(this);

    // 系统托盘相关设置
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/ico/resources/icons/tray-logo.ico"));
    trayIcon->setToolTip("虚拟桌宠");

    connect(trayIcon, &QSystemTrayIcon::activated, this, &VPetInterface::onTrayIconActivated);

    actionQuit = new QAction("退出", this);
    actionSettings = new QAction("设置", this);
    actionChat = new QAction("对话", this);

    // action 信号与槽
    connect(actionQuit, &QAction::triggered, this, &QApplication::quit);
    connect(actionSettings, &QAction::triggered, this, &VPetInterface::onSettingsClicked);
    connect(actionChat, &QAction::triggered, this, &VPetInterface::onChatClicked);
    connect(this, &VPetInterface::LLMChanged, this, &VPetInterface::onLLMChanged);

    // 菜单设置：添加actions时，从上往下
    trayMenu->addAction(actionChat);
    trayMenu->addSeparator();
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

void VPetInterface::InitializeAutoSaveService(int mesc)
{
    autoSaveTimer = new QTimer(this);

    connect(autoSaveTimer, &QTimer::timeout, this, &VPetInterface::generalSaveConfig);

    autoSaveTimer->start(mesc);
}

void VPetInterface::onSettingsClicked()
{
    qDebug() << QT_INTERFACE_LOG << "Settings Action triggered";

    if(settings == nullptr)
    {
        settings = new SettingsDialog(this);
        // connect(settings, &SettingsDialog::windowClose, this, &VPetInterface::onSettingsClosed);
        int returnStatus = settings->exec();

        qDebug() << QT_INTERFACE_LOG << "Settings quited, return value" << returnStatus;

        settings = nullptr;
    }
}

void VPetInterface::onChatClicked()
{
    ChatWindow *window = ui->live2dWidget->chatWindowP();
    if(window == nullptr)
    {
        window = new ChatWindow(this);
        ui->live2dWidget->setChatWindowP(window);
        window->show();
        connect(window, &ChatWindow::windowClose, ui->live2dWidget, &MyOpenGL::chatWindowDestroy);
        qDebug() << QT_INTERFACE_LOG << "ChatWindow created";
    }
}

void VPetInterface::setWheelZoomState(bool state)
{
    isWheelZoomActive = state;

    qDebug() << QT_BACKGROUND_LOG << "wheel zoom active?" << state;
}

void VPetInterface::setWindowOnTopState(bool state, bool override)
{
    if(override)
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
    if(width < MIN_MODEL_WIDTH || height < MIN_MODEL_WIDTH * MODEL_PROPORTION)
        return;

    QSize orgSize = this->size();

    this->resize(width, height);

    QSize l2dSize = ui->live2dWidget->size();
    int dw = l2dSize.width() - orgSize.width();
    int dh = l2dSize.height() - orgSize.height();

    ui->live2dWidget->resizeGL(width + dw, height + dh);
}

void VPetInterface::resizeWindow(QSize size)
{
    if(size.width() < MIN_MODEL_WIDTH || size.height() < MIN_MODEL_WIDTH * MODEL_PROPORTION)
        return;

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
    if(curModel == index)
        return;

    curModel = index;
    if(index < FileHandler::getModelNum())
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

void VPetInterface::setAPI(QString api, QString secret)
{
    apiKey = api;
    secretKey = secret;
}

QStringList VPetInterface::api()
{
    QStringList list;
    list.push_back(apiKey);
    list.push_back(secretKey);
    return list;
}

void VPetInterface::setLLMEnable(bool state)
{
    isLLMEnable = state;
    qDebug() << QT_INTERFACE_LOG << "LLM Status" << isLLMEnable;
}

bool VPetInterface::LLMEnable()
{
    return isLLMEnable;
}

void VPetInterface::setTTSEnable(bool state)
{
    isTTSEnable = state;
    qDebug() << QT_INTERFACE_LOG << "TTS Status" << isTTSEnable;

    emit LLMChanged(isLLMEnable);  // 信号触发
}

bool VPetInterface::TTSEnable()
{
    return isTTSEnable;
}

void VPetInterface::setVoice(int index)
{
    if(curVoice == index)
        return;

    curVoice = index;
    // 设置语音包

    qDebug() << QT_INTERFACE_LOG << "voice model changed:";
}

int VPetInterface::voice()
{
    return curVoice;
}

void VPetInterface::setVolume(int volume)
{
    if(volume < 0 || volume > 100)
        return;
    curVolume = volume;
    qDebug() << QT_INTERFACE_LOG << "volume changed to:" << volume;
}

int VPetInterface::volume()
{
    return curVolume;
}

void VPetInterface::setPace(int pace)
{
    if(pace < 0 || pace > 100)
        return;
    curPace = pace;
    qDebug() << QT_INTERFACE_LOG << "pace changed to:" << pace;
}

int VPetInterface::pace()
{
    return curPace;
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

void VPetInterface::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Trigger:
        this->showNormal(); // 单击，显示桌宠本身
        this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        ui->live2dWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false);
        if(isWindowOnTop)
            this->setWindowOnTopState(true, false);
        break;
    case QSystemTrayIcon::DoubleClick:
        onSettingsClicked();    // 双击，显示设置界面
        break;
    default:
        break;
    }
}

void VPetInterface::onLLMChanged(bool state)
{
    actionChat->setDisabled(!state);
}

void VPetInterface::transparentMouseEvent()
{
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);  // 鼠标操作穿透
    ui->live2dWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

SettingsDialog* VPetInterface::getSettings()
{
    return settings;
}

void VPetInterface::setSettings(SettingsDialog *pointer)
{
    settings = pointer;
    if(pointer != nullptr)
        qDebug() << QT_INTERFACE_LOG << "Settings created" << settings;
    else
        qDebug() << QT_BACKGROUND_LOG << "Settings deleted";
}

void VPetInterface::generalSaveConfig()
{
    ConfigSaver::writeConfig(this);
    qDebug() << QT_BACKGROUND_LOG << "config.json saved";
}
