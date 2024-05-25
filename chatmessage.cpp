#include "chatmessage.h"

ChatMessage::ChatMessage(const QString &text, MessageType type, QWidget *parent)
    : QWidget{parent}
{
    setMinimumWidth(100);
    setMinimumHeight(30);

}

void ChatMessage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 抗锯齿

    QRect bubbleRect = (msgType == User) ? rect().adjusted(MARGIN, MARGIN, -MARGIN * 2, -MARGIN)
                                     : rect().adjusted(MARGIN * 2, MARGIN, -MARGIN, -MARGIN);

    // 绘制气泡
    painter.setPen(Qt::NoPen);
    switch(msgType)
    {
    case User:
        painter.setBrush(QBrush(hex2QColor(ACCENT_COLOR)));
        painter.drawRoundedRect(bubbleRect, 10, 10);
        break;
    case LLM:
        painter.setBrush(Qt::gray);
        painter.drawRoundedRect(bubbleRect.translated(-bubbleRect.width(), 0), 10, 10);
        break;
    default:
        qDebug() << QT_BACKGROUND_LOG << "error: unable to read msgtype";
        return;
    }

    // 绘制文字
    switch(msgType)
    {
    case User:
        painter.setBrush(Qt::black);
        painter.drawText(bubbleRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWrapAnywhere, msgText);
        break;
    case LLM:
        painter.setBrush(Qt::white);
        painter.drawText(bubbleRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWrapAnywhere, msgText);
        break;
    default:
        break;
    }
}
