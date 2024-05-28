#ifndef SECONDTHREAD_H
#define SECONDTHREAD_H

#include <QObject>
#include <QThread>
#include "voicethread.h"

class SecondThread : public QThread
{
    Q_OBJECT
public:
    explicit SecondThread(QObject *parent = nullptr, QString prompt = "",
                          bool tts = false, int index = 0);

private:
    QString _prompt;
    VoiceThread *thread;

    bool _tts;
    int _index;

protected:
    void run();

signals:
    void done(QString text);
};

#endif // SECONDTHREAD_H
