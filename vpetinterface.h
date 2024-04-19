#ifndef VPETINTERFACE_H
#define VPETINTERFACE_H

#pragma once

#include "qheaders.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class VPetInterface;
}
QT_END_NAMESPACE

class VPetInterface : public QWidget
{
    Q_OBJECT

public:
    VPetInterface(QWidget *parent = nullptr);
    ~VPetInterface();

    void InitializeSystemTray();

    void InitializeAppDir();

    // 功能开关接口
    void setWindowOnTopState(bool state);
    void setWheelZoomState(bool state);
    bool windowOnTopState();
    bool wheelZoomState();

    // 窗口缩放接口
    void resizeWindow(int width, int height);
    void resizeWindow(QSize size);

    // 帧率设置接口
    void setFps(int fps);
    int fps();

    // 模型状态存储接口
    void setModelIndex(int index);
    int modelIndex();

    // 开机自启实现函数:注册表实现（实验性）
    void regAutoRun();
    bool isRegAutoRun();

    // 开机自启实现函数:快捷方式实现
    void lnkAutoRun();
    bool isLnkAutoRun();

    // 开机自启状态存储接口
    // void setStartupAutoRun(bool state);
    // bool startupAutoRun();

public slots:
    void onSettingsClicked();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::VPetInterface *ui;

    // 变量
    QSystemTrayIcon *trayIcon;  // 任务栏托盘图标
    QMenu *trayMenu;    // 托盘菜单
    QAction *actionQuit;    // 退出动作
    QAction *actionSettings;    // 设置动作

    // ConfigSaver *saver;

    int curFps = DEFAULT_FPS;
    int curModel = DEFAULT_MODEL;

    bool isWindowOnTop = true;
    bool isWheelZoomActive = true;
    bool isSystemStartup = false;
};
#endif // VPETINTERFACE_H
