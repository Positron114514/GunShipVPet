#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <QWidget>
#include "qheaders.h"

#define MARGIN 10
#define ACCENT_COLOR "1de9b6"

class ChatMessage : public QWidget
{
    Q_OBJECT
public:
    enum MessageType
    {
        User = 0,
        LLM = 1
    };

    // 构造函数
    explicit ChatMessage(const QString &text, MessageType type, QWidget *parent = nullptr);

    void InitializeLabels();

    inline QColor hex2QColor(QString hex)
    {
        return QColor(hex.toUInt(NULL, 16));
    }

protected:
    // void paintEvent(QPaintEvent *event) override;

private:
    QString msgText;
    MessageType msgType;

    QLabel *sender, *content;

signals:
};

#endif // CHATMESSAGE_H
