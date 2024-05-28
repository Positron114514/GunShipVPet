#ifndef VOICETHREAD_H
#define VOICETHREAD_H

#include <QObject>
#include <QThread>

class VoiceThread : public QThread
{
    Q_OBJECT
public:
    enum TriggerType
    {
        None = 0,
        Test = 1,
        Normal = 2
    };

    explicit VoiceThread(QObject *parent = nullptr,
                         TriggerType type = None,
                         int index = 0,
                         const QString &text = "");

protected:
    void run() override;

private:
    QString _text;
    TriggerType _type;

    int _index;

signals:
    void done();
};

#endif // VOICETHREAD_H
