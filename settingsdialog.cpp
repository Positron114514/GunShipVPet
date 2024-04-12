#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#define ZOOM_ENABLE_REQ "（关闭鼠标缩放后可用）"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    this->setFixedSize(this->size());

    p = (VPetInterface *) this->parentWidget();
    orgSize = p->size();

    // 窗体设置
    this->setWindowTitle("虚拟桌宠设置");
    this->setWindowIcon(QIcon(":/img/resources/icons/settings.png"));
    this->setWindowModality(Qt::WindowModal);

    ui->configureBox->button(QDialogButtonBox::Cancel)->setText("取消");
    ui->configureBox->button(QDialogButtonBox::Ok)->setText("确定");

    GeneralSettingsInit();
}

SettingsDialog::~SettingsDialog()
{
    qDebug() << QT_BACKGROUND_LOG << "Settings released";
    delete ui;
}

void SettingsDialog::GeneralSettingsInit()
{
    isSliderZoomAvailable = !p->wheelZoomState();

    ui->checkBoxWindowTop->setChecked(p->windowOnTopState());
    ui->checkBoxWheelZoom->setChecked(p->wheelZoomState());

    ui->sliderZoom->setEnabled(isSliderZoomAvailable);
    ui->sliderZoom->setMaximum(MAX_MODEL_WIDTH);    // in width
    ui->sliderZoom->setMinimum(MIN_MODEL_WIDTH);    // in width
    ui->sliderZoom->setPageStep(5);     // in width

    // 设置拖动条状态
    if(isSliderZoomAvailable)
    {
        auto size = p->size();
        QString sizeStr = QString("(%1×%2)").arg(size.width()).arg(size.height());
        ui->labelSize->setText(QString("缩放").append(sizeStr));
        ui->sliderZoom->setValue(size.width());
    } else
        ui->labelSize->setText(QString("缩放").append(ZOOM_ENABLE_REQ));

    fileDir = FileHandler::getModelDirList();
    ui->comboModel->addItems(fileDir);
    modelIndex = p->modelIndex();
    ui->comboModel->setCurrentIndex(modelIndex);

    QStringList fpsValues;
    fpsValues << "30" << "60";
    ui->comboFPSSetting->addItems(fpsValues);
    ui->comboFPSSetting->setCurrentText(QString::number(p->fps()));

    connect(ui->checkBoxWheelZoom, &QCheckBox::stateChanged,
            this, &SettingsDialog::onZoomBoxChanged);

    connect(ui->comboModel, &QComboBox::textActivated,
            this, &SettingsDialog::onComboBoxChanged);
}

void SettingsDialog::accept()
{
    p->setWindowOnTopState(ui->checkBoxWindowTop->isChecked());
    p->setWheelZoomState(ui->checkBoxWheelZoom->isChecked());

    p->setModelIndex(modelIndex);

    p->setFps(ui->comboFPSSetting->currentText().toInt());

    qDebug() << QT_BACKGROUND_LOG << "settings carded";

    done(Accepted);
}

void SettingsDialog::reject()
{
    p->resizeWindow(orgSize);

    qDebug() << QT_BACKGROUND_LOG << "action rejected";

    done(Rejected);
}

void SettingsDialog::onZoomBoxChanged()
{
    bool state = ui->checkBoxWheelZoom->isChecked();

    if(!state)
    {
        auto size = p->size();
        QString sizeStr = QString("(%1×%2)").arg(size.width()).arg(size.height());
        ui->labelSize->setText(QString("缩放").append(sizeStr));

        ui->sliderZoom->setValue(p->size().width());

        // 缩放条时间槽连接:实现拖动缩放
        connect(ui->sliderZoom, &QSlider::sliderMoved, this, &SettingsDialog::onSliderChanged);
        connect(ui->sliderZoom, &QSlider::sliderReleased, this, &SettingsDialog::onSliderChanged);

        isSliderZoomAvailable = true;
    } else {
        ui->labelSize->setText(QString("缩放").append(ZOOM_ENABLE_REQ));
        isSliderZoomAvailable = false;
    }

    ui->sliderZoom->setEnabled(isSliderZoomAvailable);
}

void SettingsDialog::onSliderChanged()
{
    int value = ui->sliderZoom->value();
    p->resizeWindow(value, value * MODEL_PROPORTION);

    auto size = p->size();
    QString sizeStr = QString("(%1×%2)").arg(size.width()).arg(size.height());
    ui->labelSize->setText(QString("缩放").append(sizeStr));
}

void SettingsDialog::onComboBoxChanged()
{
    modelIndex = ui->comboModel->currentIndex();
    qDebug() << QT_DEBUG_OUTPUT << "current index:" << modelIndex;
}
