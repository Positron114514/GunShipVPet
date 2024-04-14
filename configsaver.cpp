#include "configsaver.h"

ConfigSaver::ConfigSaver(VPetInterface *parent)
{

}

QJsonObject *ConfigSaver::readConfigFile()
{
    QFile file(CONFIG_DIR);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << QT_BACKGROUND_LOG << "can't open config file: " << CONFIG_DIR;
        return NULL;
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
        return NULL;
    }

    return new QJsonObject(doc.object());
}

void ConfigSaver::saveConfigFile(QJsonObject &root)
{
    // Save to config_dir
    QJsonDocument setDoc;
    setDoc.setObject(root);

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

    saveConfigFile(rootObject);
}

void ConfigSaver::saveModelPath(QString &path)
{
    // 获取根 { }
    QJsonObject *root = readConfigFile();
    if(root == NULL){
        qDebug() << "Failed to load config file when saving model dir path.";
    }

    QJsonArray pathArray;

    // 检测是否包含该对象, 如不包含则创建
    if(root->contains("modelPath"))
    {
        QJsonValue modelPath = root->value("modelPath");
        pathArray = modelPath.toArray();
        pathArray.append(path);
    }else
    {
        pathArray.append(path);
    }

    root->insert("modelPath", pathArray);
    saveConfigFile(*root);
}

QStringList *ConfigSaver::getModelPath()
{
    QJsonObject *root = readConfigFile();
    if(root == NULL)
    {
        return NULL;
    }

    if(!root->contains("modelPath"))
    {
        return NULL;
    }

    QJsonValue path = root->value("modelPath");
    QStringList *ret = new QStringList();
    QJsonArray pathArr = path.toArray();

    for(auto var : pathArr)
    {
        ret->append(var.toString());
    }

    return ret;
}

void ConfigSaver::loadConfig(VPetInterface *p)
{
    QJsonObject *root = readConfigFile();
    if(root == NULL){
        writeConfig(p);
        return;
    }
    // Model
    QJsonValue model = root->value("model");
    p->setModelIndex(model.toInt());
    // FPS
    QJsonValue fps = root->value("fps");
    p->setFps(fps.toInt());
    // Window on top
    QJsonValue windowOnTop = root->value("windowOnTop");
    p->setWindowOnTopState(windowOnTop.toBool());
    // Whell zoom state
    QJsonValue whellZoom = root->value("whellZoom");
    p->setWheelZoomState(whellZoom.toBool());
    // // Model Path
    // QJsonArray *ModelPath = getModelPath();
    // for(int i = 0; i < ModelPath->size(); i++)
    // {
    //     FileHandler::addModel((*ModelPath)[i].toString());
    // }
    // 把 load model path 写在live2d里了, 要不然一直崩, 应该是加载顺序的问题

    qDebug() << "Load config successfully.";
}
