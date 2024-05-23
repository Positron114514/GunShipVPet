#include "llminterface.h"

// get access token to wenxin
// accessToken 会直接加载到 llmhandler.cpp 的对象中, 因此无返回值
// !使用 getCompletion 前必须调用该方法
void LlmInterface::getAccessToken(QString apiKey, QString secretKey)
{
    LlmHandler::getInstance()->getAccessToken(apiKey, secretKey);
}

// talk with llm
// prompt: input string
// return: output string
// 注意: 如果触发 PY_LOAD_JSON_FAILED 或 PY_REQUEST_FAILED, 返回值为 NULL
QString* LlmInterface::getCompletion(QString *prompt)
{
    return LlmHandler::getInstance()->getCompletion(prompt);
}

// 获取声音名字的 list
QStringList* LlmInterface::getVoiceList()
{
    return TtsHandler::getInstance()->getVoiceList();
}

// 测试声音
void LlmInterface::test(int voiceIndex)
{
    TtsHandler::getInstance()->test(voiceIndex);
}

// 说话
void LlmInterface::speak(QString* text, int voiceIndex)
{
    TtsHandler::getInstance()->speak(text, voiceIndex);
}

// 停止播放当前声音
void LlmInterface::stop()
{
    TtsHandler::getInstance()->stop();
}

// 设置速度
void LlmInterface::setRate(int rate)
{
    TtsHandler::getInstance()->setRate(rate);
}

// 设置音量
void LlmInterface::setVolume(int volume)
{
    TtsHandler::getInstance()->setVolume(volume);
}
