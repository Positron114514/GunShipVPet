#ifndef LOADINGPAGE_H
#define LOADINGPAGE_H

#include <QDialog>
#include <QWidget>
#include <QMovie>

class LoadingPage : public QDialog
{
    Q_OBJECT
public:
    LoadingPage(QWidget *parent);

public slots:
    void onFinishProcess();

private:
    QMovie *move;
};

#endif // LOADINGPAGE_H
