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
    ModelSettingsInit();
    LLMSettingsInit();
    AboutSettingsInit();
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
    ui->checkBoxTTS->setCheckable(false);

    ui->sliderZoom->setEnabled(isSliderZoomAvailable);
    ui->sliderZoom->setMaximum(MAX_MODEL_WIDTH);    // in width
    ui->sliderZoom->setMinimum(MIN_MODEL_WIDTH);    // in width
    ui->sliderZoom->setPageStep(5);     // in width

    // 设置添加自启动按钮状态
    if(!p->isLnkAutoRun())
    {
        ui->btnSetAutoRun->setDisabled(true);
        ui->labelAutoRunInfo->setText("开机自启动项已存在，请在系统启动设置中设置");
    } else {
        ui->labelAutoRunInfo->setText("将虚拟桌宠添加进开机自启动项");
        connect(ui->btnSetAutoRun, &QPushButton::clicked,
                this, &SettingsDialog::onAutoRunBtnClicked);
    }

    // 设置拖动条状态
    if(isSliderZoomAvailable)
    {
        auto size = p->size();
        QString sizeStr = QString("(%1×%2)").arg(size.width()).arg(size.height());
        ui->labelSize->setText(QString("缩放").append(sizeStr));
        ui->sliderZoom->setValue(size.width());

        // 缩放条时间槽连接:实现拖动缩放
        connect(ui->sliderZoom, &QSlider::sliderMoved, this, &SettingsDialog::onSliderChanged);
        connect(ui->sliderZoom, &QSlider::sliderReleased, this, &SettingsDialog::onSliderChanged);
    } else
        ui->labelSize->setText(QString("缩放").append(ZOOM_ENABLE_REQ));

    QStringList fpsValues;
    fpsValues << "30" << "60";
    ui->comboFPSSetting->addItems(fpsValues);
    ui->comboFPSSetting->setCurrentText(QString::number(p->fps()));

    connect(ui->checkBoxWheelZoom, &QCheckBox::stateChanged,
            this, &SettingsDialog::onZoomBoxChanged);
}

void SettingsDialog::ModelSettingsInit()
{
    fileDir = FileHandler::getModelDirList();
    ui->comboModel->addItems(fileDir);
    modelIndex = p->modelIndex();
    ui->comboModel->setCurrentIndex(modelIndex);

    connect(ui->comboModel, &QComboBox::textActivated,
            this, &SettingsDialog::onComboBoxChanged);
    connect(ui->importButton, &QPushButton::clicked,
            this, &SettingsDialog::onImportClicked);
}

void SettingsDialog::LLMSettingsInit()
{
    connect(ui->checkBoxLLM, &QCheckBox::stateChanged,
            this, &SettingsDialog::onLLMBoxChanged);
}

void SettingsDialog::AboutSettingsInit()
{
    connect(ui->btnWebRaw, &QPushButton::clicked, this, [=]() {
        QString url = "https://github.com/Positron114514/GunShipVPet";
        QDesktopServices::openUrl(QUrl(url.toLatin1()));
    });
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

void SettingsDialog::onImportClicked()
{
    // unfinished
    QString folderDir = QFileDialog::getExistingDirectory(this, "选择模型文件夹", "/");

    // QDir fromDir(folderDir);
    // QDir targetDir("Resources/");

    FileHandler::addModel(folderDir);

    // 将选定路径保存在 config.json 中
    FileHandler::saveModelPath(folderDir);

    ui->comboModel->clear();
    fileDir = FileHandler::getModelDirList();
    ui->comboModel->addItems(fileDir);
}

void SettingsDialog::onLLMBoxChanged()
{
    if(!ui->checkBoxLLM->isChecked())
    {
        ui->checkBoxTTS->setCheckable(false);
    } else {
        ui->checkBoxTTS->setCheckable(true);
    }
}

void SettingsDialog::onAutoRunBtnClicked()
{
    p->setStartupAutoRun(true);
    if(p->isLnkAutoRun())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("操作成功");
        msgBox.setText("开机自启动项添加成功！\n如果需要关闭请在系统启动设置中手动关闭");
        msgBox.button(QMessageBox::Ok)->setText("确定");
        msgBox.exec();

        ui->btnSetAutoRun->setDisabled(true);
        ui->labelAutoRunInfo->setText("开机自启动项已存在，请在系统启动设置中设置");
    } else {
        qDebug() << QT_BACKGROUND_LOG << "AUTORUN link creation failed! Time"
                 << autoRunErrorTime + 1;

        if(autoRunErrorTime <= 3)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setWindowTitle("操作失败");
            msgBox.setText("开机自启动项添加失败！\n请重试...");
            msgBox.button(QMessageBox::Ok)->setText("确定");
            msgBox.exec();

            qDebug() << QT_INTERFACE_LOG << "Error window exec and notified";
            autoRunErrorTime++;
        } else {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("操作多次失败...");
            msgBox.setText("开机自启动项多次添加失败！\n请向我们提交log与Issues，谢谢！");
            msgBox.button(QMessageBox::Ok)->setText("确定");
            connect(msgBox.button(QMessageBox::Ok), &QPushButton::clicked, this, [=]() {
                QString url = "https://github.com/Positron114514/GunShipVPet/issues";
                QDesktopServices::openUrl(url);
            });
            msgBox.exec();

            qDebug() << QT_INTERFACE_LOG << "Multi-error window exec";

            ui->btnSetAutoRun->setDisabled(true);
            ui->labelAutoRunInfo->setText("看起来功能出现了问题，暂时不可用...");
        }
    }
}
