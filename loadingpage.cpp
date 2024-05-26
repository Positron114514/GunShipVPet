#include "loadingpage.h"
#include <QLabel>

LoadingPage::LoadingPage(QWidget *parent)
    : QDialog(parent)
{
    this->resize(100, 100);
    this->setWindowOpacity(0.8);    // 透明度
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); // 窗体性质
    QLabel *label = new QLabel(this);
    move = new QMovie(":/gif/resources/images/loading.gif");    // 设置动画
    label->setMovie(move);
    label->setScaledContents(true);
    label->resize(100, 100);
    move->start();
}

void LoadingPage::onFinishProcess()
{
    this->close();
}
