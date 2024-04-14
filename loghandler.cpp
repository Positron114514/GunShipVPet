#include "loghandler.h"

#include <iostream>

LogHandler::LogHandler() {

}

void LogHandler::initLog()
{
    QFile file(LOG_DIR);
    if(file.exists())
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << "";
        }
    }
    std::cout << QString(QT_BACKGROUND_LOG).toStdString() << "log file cleaned";
}

void LogHandler::message(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutex mutex;
    mutex.lock();   // 进程锁

    QString text = QString();

    switch(type)
    {
    case QtDebugMsg:
        text = "Basic";
        break;
    case QtWarningMsg:
        text = "Warning";
        break;
    case QtCriticalMsg:
        text = "Critical";
        break;
    case QtInfoMsg:
        text = "Info";
        break;
    case QtFatalMsg:
        text = "Fatal";
        break;
    default:
        text = "OpenGL";
        break;
    }

    QString log = QDateTime::currentDateTime().toString("{yyyy-MM-dd hh:mm:ss}\n") + msg + "\n";

    QFile file(LOG_DIR);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << log << "\n";
        file.flush();
        file.close();
    }

    mutex.unlock();
}

