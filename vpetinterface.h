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

    // 重载事件过滤器
    // bool eventFilter(QObject *watched, QEvent *event);

public slots:
    void onSettingsClicked();

private:
    Ui::VPetInterface *ui;

    // 变量
    QSystemTrayIcon *trayIcon;  // 任务栏托盘图标
    QMenu *trayMenu;    // 托盘菜单
    QAction *actionQuit;    // 退出动作
    QAction *actionSettings;    // 设置动作

};
#endif // VPETINTERFACE_H
