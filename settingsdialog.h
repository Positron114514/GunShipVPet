#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#pragma once

#include "qheaders.h"
#include "vpetinterface.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    VPetInterface *p = nullptr;

    void GeneralSettingsInit();  // 通用设置tab信号与槽的初始化

protected:
    // 重写qdialogbuttonbox操作
    void accept() override;
    void reject() override;

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
