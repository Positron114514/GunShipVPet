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

    void InitializeUI();

signals:
    void windowClose();

public slots:
    void onSettingsClicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ChatWindow *ui;
    VPetInterface *p = nullptr;
};

#endif // CHATWINDOW_H
