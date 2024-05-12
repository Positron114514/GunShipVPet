#include "configsaver.h"
#include "customdir.h"

ConfigSaver::ConfigSaver(VPetInterface *parent)
{

}

QString ConfigSaver::CesarEncrypt(QString str)
{
    int l = str.length();
    QString encr = "";
    for(int i = 0; i < l; i++)
    {
        encr.append(QChar(str[i].toLatin1() - API_CESAR_KEY));
    }
    return encr;
}

QString ConfigSaver::CesarDecrypt(QString str)
{
    int l = str.length();
    QString decr = "";
    for(int i = 0; i < l; i++)
    {
        decr.append(QChar(str[i].toLatin1() + API_CESAR_KEY));
    }
    return decr;
}

QJsonObject *ConfigSaver::readConfigFile()
{
    QFile file(CustomDir::customDir() + QDir::separator() + CONFIG_DIR);
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

    QFile file(CustomDir::customDir() + QDir::separator() + CONFIG_DIR);
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
    // Wheel zoom state
    rootObject.insert("wheelZoom", p->wheelZoomState());
    // Mainwindow size config
    QJsonArray windowSize;
    windowSize.append(p->width());
    windowSize.append(p->height());
    rootObject.insert("windowSize", windowSize);
    // Mainwindow position config
    QJsonArray windowPos;
    windowPos.append(p->pos().x());
    windowPos.append(p->pos().y());
    rootObject.insert("position", windowPos);
    // API config
    QJsonArray api;
    QStringList apiList = p->api();
    api.append(CesarEncrypt(apiList[0]));
    api.append(CesarEncrypt(apiList[1]));
    rootObject.insert("apiKeys", api);
    // LLM&TTS config
    rootObject.insert("chatLLM", p->LLMEnable());
    rootObject.insert("chatTTS", p->TTSEnable());

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
    // Wheel zoom state
    QJsonValue wheelZoom = root->value("wheelZoom");
    p->setWheelZoomState(wheelZoom.toBool());
    // System startup autorun state
    // QJsonValue autoRun = root->value("startupAutoRun");
    // p->setStartupAutoRun(autoRun.toBool());
    // Mainwindow size config
    auto windowSize = root->value("windowSize");
    p->resizeWindow(windowSize[0].toInt(), windowSize[1].toInt());
    // Window position config
    auto windowPos = root->value("position");
    p->move(windowPos[0].toInt(), windowPos[1].toInt());
    // apikeys config
    auto api = root->value("apiKeys");
    p->setAPI(CesarDecrypt(api[0].toString()), CesarDecrypt(api[1].toString()));
    // LLM&TTS config
    p->setLLMEnable(root->value("chatLLM").toBool());
    p->setTTSEnable(root->value("chatTTS").toBool());

    // qDebug() << QT_DEBUG_OUTPUT << "api keys:" << p->api();

    // // Model Path
    // QJsonArray *ModelPath = getModelPath();
    // for(int i = 0; i < ModelPath->size(); i++)
    // {
    //     FileHandler::addModel((*ModelPath)[i].toString());
    // }
    // 把 load model path 写在live2d里了, 要不然一直崩, 应该是加载顺序的问题

    qDebug() << QT_BACKGROUND_LOG << "Load config successfully.";
}
