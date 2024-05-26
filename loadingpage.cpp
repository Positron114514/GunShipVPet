#include "loadingpage.h"
#include <QMovie>

LoadingPage::LoadingPage(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowOpacity(0.8);    // 透明度
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); // 窗体性质
    QLabel *label = new QLabel(this);
    QMovie *move = new QMovie(":/gif/resources/images/loading.gif");    // 设置动画
    label->setMovie(move);
    label->setScaledContents(true);
    move->start();
}
