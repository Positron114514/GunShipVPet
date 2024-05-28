#include "secondthread.h"
#include "llminterface.h"

SecondThread::SecondThread(QObject *parent, QString prompt, bool tts, int index)
    : QThread{parent}
{
    _prompt = prompt;
    _tts = tts;
    _index = index;
}

void SecondThread::run()
{
    QString result = *LlmInterface::getCompletion(&_prompt);

    // 调用文本转语音线程
    if(_tts)
    {
        thread = new VoiceThread(this->parent(), VoiceThread::Normal, _index, result);
        thread->start();
    }

    emit done(result);
}
