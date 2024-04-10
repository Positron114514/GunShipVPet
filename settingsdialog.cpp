#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    p = (VPetInterface *) this->parentWidget();

    // 窗体设置
    this->setWindowTitle("虚拟桌宠设置");
    this->setWindowIcon(QIcon(":/img/resources/icons/settings.png"));
    this->setWindowModality(Qt::WindowModal);

    GeneralSettingsInit();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::GeneralSettingsInit()
{
    ui->checkBoxWindowTop->setChecked(p->windowOnTopState());
    ui->checkBoxWheelZoom->setChecked(p->wheelZoomState());

}

void SettingsDialog::accept()
{
    // hint: bug occurs
    // 窗口置顶状态更改后，live2d widget消失，但析构函数并未执行

    p->setWindowOnTopState(ui->checkBoxWindowTop->isChecked());
    p->setWheelZoomState(ui->checkBoxWheelZoom->isChecked());

    qDebug() << QT_BACKGROUND_LOG << "settings carded";

    done(Accepted);
}

void SettingsDialog::reject()
{
    qDebug() << QT_BACKGROUND_LOG << "action rejected";

    done(Rejected);
}
