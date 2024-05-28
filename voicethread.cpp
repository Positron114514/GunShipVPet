#include "voicethread.h"
#include "llminterface.h"

VoiceThread::VoiceThread(QObject *parent, TriggerType type, int index, const QString &text)
    : QThread{parent}
{
    _index = index;
    _type = type;
    switch(_type)
    {
    case Normal:
        _text = text;
    default:
        break;
    }
}

void VoiceThread::run()
{
    if(_type == None)
        return;

    if(_type == Test)
    {
        LlmInterface::test(_index); // 测试
        emit done();
        return;
    }

    // _type == Normal
    LlmInterface::speak(&_text, _index);
    emit done();
}
