#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "settingsdialog.h"

ChatWindow::ChatWindow(QWidget *mainApp, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    p = (VPetInterface *) mainApp;

    // 窗口属性设置
    this->setWindowTitle("对话...");
    this->setWindowIcon(QIcon(":/ico/resources/icons/main-logo.ico"));
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);

    InitializeUI();
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::closeEvent(QCloseEvent *event)
{
    // 重载关闭事件，关闭时触发信号
    emit windowClose();
    QWidget::closeEvent(event);
}

void ChatWindow::InitializeUI()
{
    connect(ui->btnSettings, &QPushButton::pressed, this, &ChatWindow::onSettingsClicked);

    QFont font;
    font.setFamily("MiSans");
    font.setPointSize(14);
    ui->title->setFont(font);
}

void ChatWindow::onSettingsClicked()
{
    qDebug() << QT_INTERFACE_LOG << "Settings Action triggered";

    SettingsDialog settings(p);
    int returnStatus = settings.exec();

    qDebug() << QT_INTERFACE_LOG << "Settings quited, return value" << returnStatus;
}
