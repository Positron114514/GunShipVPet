#include "floatbuttonwidget.h"
#include "ui_floatbuttonwidget.h"

FloatButtonWidget::FloatButtonWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FloatButtonWidget)
{
    ui->setupUi(this);
    connect(ui->btnSettings, &QPushButton::clicked, this, [=]() {
        qDebug() << QT_DEBUG_OUTPUT << "settings clicked";
    });
}

FloatButtonWidget::~FloatButtonWidget()
{
    delete ui;
}
