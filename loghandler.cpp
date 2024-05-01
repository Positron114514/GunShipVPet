#include "loghandler.h"
#include "customdir.h"

#include <iostream>
#include <QApplication>

LogHandler::LogHandler() {

}

void LogHandler::initLog()
{
    QFile file(CustomDir::customDir() + QDir::separator() + LOG_DIR);
    if(file.exists())
    {
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << "";
        }
    }
    std::cout << QString(QT_BACKGROUND_LOG).toStdString() << "log file cleaned\n";
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

    QFile file(CustomDir::customDir() + QDir::separator() + LOG_DIR);

    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << log << "\n";
        std::cout << log.toStdString() << std::endl;  // 保证控制台同时有输出
        file.flush();
        file.close();
    }

    mutex.unlock();
}

QString LogHandler::captureGLError(GLenum type)
{
    switch(type)
    {
    case GL_NO_ERROR:
        return "No Error";
        break;
    case GL_INVALID_ENUM:
        return "Invalid Enum";
        break;
    case GL_INVALID_VALUE:
        return "Invalid Value";
        break;
    case GL_INVALID_OPERATION:
        return "Invalid Operation";
        break;
    case GL_STACK_OVERFLOW:
        return "Stack: stack overflow";
        break;
    case GL_STACK_UNDERFLOW:
        return "Stack: stack underflow";
        break;
    case GL_OUT_OF_MEMORY:
        return "Out of memory";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "Invalid framebuffer operation";
        break;
    default:
        return 0;
        break;
    }
}
