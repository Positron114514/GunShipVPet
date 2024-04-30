#ifndef FLOATBUTTONWIDGET_H
#define FLOATBUTTONWIDGET_H

#include <QWidget>
#include "qheaders.h"

namespace Ui {
class FloatButtonWidget;
}

class FloatButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FloatButtonWidget(QWidget *parent = nullptr);
    ~FloatButtonWidget();

private:
    Ui::FloatButtonWidget *ui;
};

#endif // FLOATBUTTONWIDGET_H
