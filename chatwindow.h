#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "vpetinterface.h"
#include "qheaders.h"
#include "secondthread.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *mainApp = nullptr, QWidget *parent = nullptr);
    ~ChatWindow();

    enum MsgType
    {
        User = 0,
        LLM = 1
    };

    void InitializeUI();
    void InitializeChat();

    void addMessage(const QString &text, MsgType type);

    inline int countNewLine(const QString &text)
    {
        int cnt = 0;
        for(int i = 0; i < text.length(); i++)
        {
            if(text[i] == '\n')
                cnt++;
        }
        return cnt;
    }

signals:
    void windowClose();
    void returnPressed();

public slots:
    void onSettingsClicked();
    void onMessageSent();
    void onGetResult(QString result);

protected:
    void closeEvent(QCloseEvent *event) override;
    // void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *target, QEvent *event) override;

private:
    Ui::ChatWindow *ui;
    VPetInterface *p = nullptr;

    SecondThread *thread;

    // QVBoxLayout *layout = nullptr;
};

#endif // CHATWINDOW_H
