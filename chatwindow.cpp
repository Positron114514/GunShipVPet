#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "settingsdialog.h"
#include "llmhandler.h"


#include <QPainter>
#include <QMargins>
#include <QTextOption>
#include <QFontMetrics>
#include <QPaintEvent>
#include <QPainter>
#include <QMovie>
#include <QLabel>

ChatWindow::ChatWindow(QWidget *mainApp, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);

    p = (VPetInterface *) mainApp;

    // 窗口属性设置
    this->setWindowTitle("与文心一言对话");
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChatWindow::TalkWithAI(){

    LlmHandler *dialog;
    QString *answer;
    dialog->getAccessToken(p->api()[0],p->api()[1]);

    auto content = ui->chat->toPlainText();

    answer = dialog->getCompletion(&content);
    //理论上answer是输出结果

}


QNChatMessage::QNChatMessage(QWidget *parent) : QWidget(parent)
{
    QFont te_font = this->font();
    te_font.setFamily("MiSans");
    te_font.setPointSize(12);
    te_font.setLetterSpacing(QFont::AbsoluteSpacing, 3);          //设置字间距为3像素 //设置字间距像素值
    this->setFont(te_font);
    m_leftPixmap = QPixmap(":/img/resources/Custome.png");
    m_rightPixmap = QPixmap(":/img/resources/images/MdiRobotExcited.png");

    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName(":/img/resources/loading.gif");
    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16,16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground , true);
    m_loading->setAutoFillBackground(true);
    //表示加载的图标

    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white
                     );
    this->setPalette(palette);
    //设置背景白色
}

void QNChatMessage::setTextSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void QNChatMessage::setText(QString text, QString time, QSize allSize, QNChatMessage::User_Type userType)
{
    m_msg = text;
    m_userType = userType;
    m_time = time;
    QDateTime curDateTime=QDateTime::currentDateTime();
    m_curTime = curDateTime.toString ("hh:mm: ss11");//获取时间
    m_allSize = allSize;
    if(userType == User_Me) {
        if(!m_isSending) {
            m_loading->move(m_kuangRightRect.x() - m_loading->width() - 10, m_kuangRightRect.y()+m_kuangRightRect.height()/2- m_loading->height()/2);
            m_loading->show();
            m_loadingMovie->start();
        }//表示加载中
    } else {
        m_loading->hide();
    }

    this->update();
}

QSize QNChatMessage::fontRect(QString str)
{
    m_msg = str;
    int minHei = 30;//这里参数可能要改一下，原先是雅黑
    int iconWH = 40;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 10;
    int sanJiaoW = 6;
    int kuangTMP = 20;
    int textSpaceRect = 12;
    m_kuangWidth = this->width() - kuangTMP - 2*(iconWH+iconSpaceW+iconRectW);
    m_textWidth = m_kuangWidth - 2*textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(m_msg); // 整个的size

    qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

    if(size.width() < (m_textWidth+m_spaceWid))
    {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
    }
    else
    {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
    }

    m_textLeftRect.setRect(m_kuangLeftRect.x()+textSpaceRect,m_kuangLeftRect.y()+iconTMPH,
                           m_kuangLeftRect.width()-2*textSpaceRect,m_kuangLeftRect.height()-2*iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x()+textSpaceRect,m_kuangRightRect.y()+iconTMPH,
                            m_kuangRightRect.width()-2*textSpaceRect,m_kuangRightRect.height()-2*iconTMPH);

    //这里我理解的是在设置气泡的数据
    return QSize(size.width(), hei);
}

QSize QNChatMessage::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    int nCount = src.count("\n");
    int nMaxWidth = 0;
    if(nCount == 0)
    {
        nMaxWidth = fm.width(src);//这里的这个宽度应该是字符串的总长
        QString value = src;
        if(nMaxWidth > m_textWidth)
        {
            nMaxWidth = m_textWidth;
            int size = m_textWidth / fm.width(" ");
            int num = fm.width(value) / m_textWidth;
            int ttmp = num*fm.width(" ");
            num = ( fm.width(value) ) / m_textWidth;
            nCount += num;
            QString temp = "";
            for(int i = 0; i < num; i++)
            {
                temp += value.mid(i*size, (i+1)*size) + "\n";
            }
            src.replace(value, temp);
        }
        //设置多行
    }
    else
    {
        for(int i = 0; i < (nCount + 1); i++)
        {
            QString value = src.split("\n").at(i);
            nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
            if(fm.width(value) > m_textWidth)
            {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                num = ((i+num)*fm.width(" ") + fm.width(value)) / m_textWidth;
                nCount += num;
                QString temp = "";
                for(int i = 0; i < num; i++)
                {
                    temp += value.mid(i*size, (i+1)*size) + "\n";
                }
                src.replace(value, temp);
            }
        }
    }
    return QSize(nMaxWidth+m_spaceWid, (nCount + 1) * m_lineHeight+2*m_lineHeight);
}

void QNChatMessage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if(m_userType == User_Type::User_She)
    { // 用户（右边的那个）
        //头像

        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x()-1,m_kuangLeftRect.y()-1,m_kuangLeftRect.width()+2,m_kuangLeftRect.height()+2,4,4);
        //框
        QColor col_Kuang(255,255,255);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect,4,4);

        //三角
        QPointF points[3] =
        {
            QPointF(m_sanjiaoLeftRect.x(), 30),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 25),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //三角加边
        QPen penSanJiaoBian;
        penSanJiaoBian.setColor(col_KuangB);
        painter.setPen(penSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 36));

        //内容
        QPen penText;
        penText.setColor(QColor(51,51,51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textLeftRect, m_msg,option);
    }
    else if(m_userType == User_Type::User_Me)
    { // 自己（左边的那个）
        //头像

        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //框
        QColor col_Kuang(75,164,242);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangRightRect,4,4);

        //三角
        QPointF points[3] =
        {
            QPointF(m_sanjiaoRightRect.x()+m_sanjiaoRightRect.width(), 30),
            QPointF(m_sanjiaoRightRect.x(), 25),
            QPointF(m_sanjiaoRightRect.x(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //内容
        QPen penText;
        penText.setColor(Qt::black);//字体的颜色参数应该也得改一下
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRightRect,m_msg,option);

    }
    else if(m_userType == User_Type::User_Time)
    { // 时间
        QPen penText;
        penText.setColor(QColor(153,153,153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont te_font = this->font();
        te_font.setFamily("MiSans");
        te_font.setPointSize(10);
        painter.setFont(te_font);
        painter.drawText(this->rect(),m_curTime,option);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////

//根据大语言模型接口，将用户与大语言模型的对话做一个聊天界面，放到demo中
//重载enter键->输入和shift+enter键->换行
//关于这个我的思路是用_kbhit()读取来判断，但读完之后还得要交互窗口输出建立一个信号和槽。窗口还没搞定。。。
//
//美化界面
//文本转语音

//api: oiRNjbVQZXXEZaNkvstJxEA5
//secret: cmFZxAvX7XKmmGdtW4MqGMHUxiQvirga
