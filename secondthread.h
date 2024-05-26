#ifndef SECONDTHREAD_H
#define SECONDTHREAD_H

#include <QObject>
#include <QThread>

class SecondThread : public QThread
{
    Q_OBJECT
public:
    explicit SecondThread(QObject *parent = nullptr, QString prompt = "");

private:
    QString m_prompt;

protected:
    void run();

signals:
    void done(QString text);
};

#endif // SECONDTHREAD_H
