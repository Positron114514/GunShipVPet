#include "configsaver.h"

ConfigSaver::ConfigSaver(VPetInterface *parent)
{

}

void ConfigSaver::writeConfig(VPetInterface *p)
{
    QJsonObject rootObject;
    // Model
    rootObject.insert("model", p->modelIndex());
    // FPS
    rootObject.insert("fps", p->fps());
    // Window on top
    rootObject.insert("windowOnTop", p->windowOnTopState());
    // Whell zoom state
    rootObject.insert("whellZoom", p->wheelZoomState());

    // Save to config_dir
    QJsonDocument setDoc;
    setDoc.setObject(rootObject);

    QFile file(CONFIG_DIR);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "can't open config file: " << CONFIG_DIR;
        return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);		// 设置写入编码是UTF8
    // 写入文件
    stream << setDoc.toJson();
    file.close();
}

void ConfigSaver::loadConfig(VPetInterface *p)
{
    QFile file(CONFIG_DIR);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << QT_BACKGROUND_LOG << "can't open config file: " << CONFIG_DIR;
        writeConfig(p);
        return;
    }

    qDebug() << QT_BACKGROUND_LOG << "file opened";

    // 读取文件的全部内容
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);		// 设置读取编码是UTF8
    QString configString = stream.readAll();

    file.close();

    // 用于报告错误
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(configString.toUtf8(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << QT_BACKGROUND_LOG << "Json格式错误！" << jsonError.error;
        return;
    }

    // 加载 doc 中的设置
    QJsonObject root = doc.object();
    // Model
    QJsonValue model = root.value("model");
    p->setModelIndex(model.toInt());
    // FPS
    QJsonValue fps = root.value("fps");
    p->setFps(fps.toInt());
    // Window on top
    QJsonValue windowOnTop = root.value("windowOnTop");
    p->setWindowOnTopState(windowOnTop.toBool());
    // Whell zoom state
    QJsonValue whellZoom = root.value("whellZoom");
    p->setWheelZoomState(whellZoom.toBool());

    qDebug() << "Load config successfully.";
}
