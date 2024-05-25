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

void ChatWindow::addMessage(const QString &text, MsgType type)
{
    QFont titleFont("MiSans", 12, 600);
    QFont contentFont("MiSans", 11, 400);

    // QWidget *widgetSender = new QWidget;
    QWidget *widgetMessage = new QWidget;
    // widgetSender->setMaximumWidth(ui->demoArea->width());
    widgetMessage->setMaximumWidth(ui->demoArea->width());
    QLabel *message = new QLabel(widgetMessage);

    QListWidgetItem *senderItem = new QListWidgetItem(ui->demoArea);
    QListWidgetItem *messageItem = new QListWidgetItem(ui->demoArea);

    switch(type)
    {
    case MsgType::User:
        senderItem->setFont(titleFont);
        senderItem->setIcon(QIcon(":/svg/resources/svgs/user.svg"));
        senderItem->setText("您");
        break;
    case MsgType::LLM:
        senderItem->setFont(titleFont);
        senderItem->setIcon(QIcon(":/svg/resources/svgs/intelligence.svg"));
        senderItem->setText("文心一言");
        break;
    }
    // sender->setScaledContents(true);
    // sender->resize(14, 14);
    // sender->setAlignment(Qt::AlignLeft);

    message->setText(text);
    message->setFont(contentFont);
    message->adjustSize();
    message->setWordWrap(true);
    message->setAlignment(Qt::AlignTop);
    message->resize(widgetMessage->size());

    senderItem->setFlags(senderItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    messageItem->setFlags(messageItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);

    ui->demoArea->addItem(senderItem);
    ui->demoArea->addItem(messageItem);

    ui->demoArea->setItemWidget(messageItem, widgetMessage);

    // int lineNum = (fontMetrics().horizontalAdvance(message->text())) / ui->demoArea->width();
    int totalWidth = fontMetrics().horizontalAdvance(message->text());
    int oneLineWidth = ui->demoArea->width();
    int lineHeight;

    if(totalWidth < oneLineWidth)
        lineHeight = 1;
    else {
        lineHeight = (totalWidth % oneLineWidth) ?
                         (totalWidth / oneLineWidth + 1) : (totalWidth / oneLineWidth);
    }
    int totalHeight = lineHeight * 30;

    messageItem->setSizeHint(QSize(0, totalHeight));
    widgetMessage->show();
}

void ChatWindow::onMessageSent()
{
    qDebug() << QT_DEBUG_OUTPUT << "message function";
    QString prompt = ui->chat->toPlainText();   // 读取prompt
    addMessage(prompt, MsgType::User);

    ui->chat->clear();  // 清空输入框

    qDebug() << QT_DEBUG_OUTPUT << "get result";
    QString result = *LlmInterface::getCompletion(&prompt); // 得到输出
    addMessage(result, MsgType::LLM);
}

void ChatWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        emit returnPressed();
}
