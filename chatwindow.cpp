#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "settingsdialog.h"
#include "llminterface.h"

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

    this->grabKeyboard();

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



    // layout = new QVBoxLayout(ui->demoArea);

    // 回车键等操作信号与槽连接
    connect(this, &ChatWindow::returnPressed, this, &ChatWindow::onMessageSent);
}

void ChatWindow::InitializeChat()
{
    p->InitiallizeLlmAndTts();  // 初始化llm和tts
}

void ChatWindow::onSettingsClicked()
{
    qDebug() << QT_INTERFACE_LOG << "Settings Action triggered";

    if(p->getSettings() == nullptr)
    {
        SettingsDialog* settings = new SettingsDialog(p);
        p->setSettings(settings);

        int returnStatus = settings->exec();

        qDebug() << QT_INTERFACE_LOG << "Settings quited, return value" << returnStatus;

        p->setSettings(nullptr);
    }

    ui->chat->setDisabled(!p->LLMEnable());
}

void ChatWindow::addMessage(const QString &text, ChatMessage::MessageType type)
{
    qDebug() << QT_DEBUG_OUTPUT << "add message";
    ChatMessage *message = new ChatMessage(text, type, this);
    qDebug() << QT_DEBUG_OUTPUT << "add message1";
    ui->demoArea->addWidget(message);
    qDebug() << QT_DEBUG_OUTPUT << "add message2";
    messages.append(message);

}

void ChatWindow::onMessageSent()
{
    qDebug() << QT_DEBUG_OUTPUT << "message function";
    QString prompt = ui->chat->toPlainText();   // 读取prompt
    addMessage(prompt, ChatMessage::User);

    ui->chat->clear();  // 清空输入框

    qDebug() << QT_DEBUG_OUTPUT << "get result";
    QString result = *LlmInterface::getCompletion(&prompt); // 得到输出
    addMessage(result, ChatMessage::LLM);
}

void ChatWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        emit returnPressed();
}
