#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#pragma once

#include "qheaders.h"
#include "filehandler.h"
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
    void ModelSettingsInit();   // Live2d模型设置tab信号与槽的初始化
    void LLMSettingsInit();     // 大语言模型设置tab信号与槽的初始化
    void AboutSettingsInit();   // 关于设置tab信号与槽的初始化

public slots:
    void onZoomBoxChanged();    // checkbox状态改变槽函数
    void onSliderChanged();     // slider状态改变槽函数
    void onComboBoxChanged();   // combobox状态改变槽函数
    void onImportClicked();     // 导入操作槽函数
    void onLLMBoxChanged();

protected:
    // 重写qdialogbuttonbox操作
    void accept() override;
    void reject() override;

private:
    Ui::SettingsDialog *ui;

    bool isSliderZoomAvailable;
    QStringList fileDir;
    int modelIndex;    // 存储combobox选中的模型索引
    QSize orgSize;  // 初始窗口大小状态存储

};

#endif // SETTINGSDIALOG_H
