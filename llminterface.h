// llm 和 tts 功能的接口

#ifndef LLMINTERFACE_H
#define LLMINTERFACE_H

#include "qheaders.h"
#include "llmhandler.h"
#include "ttshandler.h"

class LlmInterface
{
public:
    // get access token to wenxin
    // accessToken 会直接加载到 llmhandler.cpp 的对象中, 因此无返回值
    // !使用 getCompletion 前必须调用该方法
    static bool getAccessToken(QString apiKey, QString secretKey);

    // talk with llm
    // prompt: input string
    // return: output string
    // 注意: 如果触发 PY_LOAD_JSON_FAILED 或 PY_REQUEST_FAILED, 返回值为 NULL
    static QString* getCompletion(QString *prompt);

    // 获取声音名字的 list
    static QStringList* getVoiceList();

    // 测试声音
    static void test(int voiceIndex);

    // 说话
    static void speak(QString* text, int voiceIndex);

    // 停止播放当前声音
    static void stop();

    // 设置速度
    static void setRate(int rate);

    // 设置音量
    static void setVolume(int volume);
};

#endif // LLMINTERFACE_H
