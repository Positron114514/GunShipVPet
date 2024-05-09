#include "chatwidget.h"
#include "ui_chatwidget.h"

/*
 * 开发注释：
 * 这个类我希望能进行多线程优化
 * 所以在调用时并未指定父对象
 * 因为QT同一对象树中的窗口及控件没法放到多个线程
 * 因此采取这样的方式
 * 但是目前有一个bug，该窗口析构后整个程序都将终止，需要修复
 * Good Luck bro
 */

ChatWidget::ChatWidget(QWidget *parent, VPetInterface *window)
    : QWidget(parent)
    , ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    // 窗体设置
    this->setWindowTitle("对话...");  // 窗体标题
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);   // 禁止窗口最大化
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::closeEvent(QCloseEvent *event)
{
    this->deleteLater();
}
