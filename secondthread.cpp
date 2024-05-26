#include "secondthread.h"
#include "llminterface.h"

SecondThread::SecondThread(QObject *parent, QString prompt)
    : QThread{parent}
{
    m_prompt = prompt;
}

void SecondThread::run()
{
    QString result = *LlmInterface::getCompletion(&m_prompt);
    emit done(result);
}
