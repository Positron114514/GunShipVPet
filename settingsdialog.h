#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#pragma once

#include "qheaders.h"
#include "filehandler.h"
#include "vpetinterface.h"
#include "voicethread.h"

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

    void ButtonBoxInit();  // QDialogButtonBox初始化
    void GeneralSettingsInit();  // 通用设置tab信号与槽的初始化
    void ModelSettingsInit();   // Live2d模型设置tab信号与槽的初始化
    void VoiceSettingsInit();   // tts语音包设置tab信号与槽的初始化
    void LLMSettingsInit();     // 大语言模型设置tab信号与槽的初始化
    void AboutSettingsInit();   // 关于设置tab信号与槽的初始化

public slots:
    void onZoomBoxChanged();    // checkbox状态改变槽函数
    void onSliderChanged();     // slider状态改变槽函数
    void onComboBoxChanged();   // combobox状态改变槽函数
    void onImportClicked();     // 导入操作槽函数
    void onLLMBoxChanged();
    void onTTSBoxChanged();
    void onAutoRunBtnClicked(); // 添加开机自启动项槽函数
    // void onRegBtnClicked();     // 实验功能槽函数
    void onChangedAboutPage();  // 切换到帮助与反馈界面后的槽函数
    void onAPISaveClicked();    // API保存按钮按下操作
    void onDeleteModelClicked();
    void onVolumeChanged();
    void onPaceChanged();
    void testVoice();
    void onSaveToModelClicked();

signals:
    void LLMStateChanged(bool state);

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

    int autoRunErrorTime = 0;   // 添加自启失败次数

    bool isHighVolumeNotified = false;

    VoiceThread *thread = nullptr;
};

#endif // SETTINGSDIALOG_H
