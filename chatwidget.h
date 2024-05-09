#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#pragma once

#include <QWidget>
#include <qheaders.h>
#include "vpetinterface.h"

/*
 * 开发注释：
 * 这个类我希望能进行多线程优化
 * 所以在调用时并未指定父对象
 * 因为QT同一对象树中的窗口及控件没法放到多个线程
 * 因此采取这样的方式
 * Good Luck bro
 */

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr, VPetInterface *window = nullptr);
    ~ChatWidget();

protected:
    void close();
    void closeEvent(QCloseEvent *event) override;   // 重载关闭事件

private:
    Ui::ChatWidget *ui;
};

#endif // CHATWIDGET_H
