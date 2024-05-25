#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "vpetinterface.h"
#include "qheaders.h"

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

signals:
    void windowClose();
    void returnPressed();

public slots:
    void onSettingsClicked();
    void onMessageSent();

protected:
    void closeEvent(QCloseEvent *event) override;
    // void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::ChatWindow *ui;
    VPetInterface *p = nullptr;

    // QVBoxLayout *layout = nullptr;
};

#endif // CHATWINDOW_H
