#ifndef VPETINTERFACE_H
#define VPETINTERFACE_H

#pragma once

#include "qheaders.h"
#include "llminterface.h"

class SettingsDialog;

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

    void InitializeAutoSaveService(int mesc);

    // // 初始化 LLM 和 TTS
    // void InitiallizeLlmAndTts();

    // 功能开关接口
    void setWindowOnTopState(bool state, bool override = true);
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

    // 对话功能实现接口
    void setLLMEnable(bool state);
    bool LLMEnable();
    void setTTSEnable(bool state);
    bool TTSEnable();

    // api接口：其中api返回值下标为0是apikey，1是secretkey
    void setAPI(QString api, QString secret);
    QStringList api();

    // tts语音包接口
    void setVoice(int index);
    int voice();

    // tts音量接口
    void setVolume(int volume);
    int volume();

    // tts语速接口
    void setPace(int pace);
    int pace();

    // 开机自启实现函数:注册表实现（实验性）
    void regAutoRun();
    bool isRegAutoRun();

    void transparentMouseEvent();

    // 设置接口
    void setSettings(SettingsDialog *pointer);
    SettingsDialog *getSettings();

signals:
    void LLMChanged(bool state);

public slots:
    void onSettingsClicked();
    void onChatClicked();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onLLMChanged(bool state);
    void generalSaveConfig();

private:
    Ui::VPetInterface *ui;

    // 变量
    QSystemTrayIcon *trayIcon;  // 任务栏托盘图标
    QMenu *trayMenu;    // 托盘菜单
    QAction *actionQuit;    // 退出动作
    QAction *actionSettings;    // 设置动作
    QAction *actionChat;    // 大模型对话动作

    QPushButton *btn;

    SettingsDialog *settings = nullptr;

    QTimer *autoSaveTimer = nullptr;

    // // llmHandler
    // LlmHandler* _llmHandler;
    // // ttsHandler
    // TtsHandler* _ttsHandler;
    // ConfigSaver *saver;

    int curFps = DEFAULT_FPS;
    int curModel = DEFAULT_MODEL;
    int curVoice = DEFAULT_VOICE;
    int curVolume = DEFAULT_VOLUME;
    int curPace = DEFAULT_PACE;

    bool isWindowOnTop = true;
    bool isWheelZoomActive = true;
    bool isSystemStartup = false;

    bool isLLMEnable = true;
    bool isTTSEnable = false;

    QString apiKey;
    QString secretKey;
};
#endif // VPETINTERFACE_H
