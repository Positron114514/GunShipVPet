#ifndef CONFIGSAVER_H
#define CONFIGSAVER_H

#pragma once

#include "qheaders.h"
#include "vpetinterface.h"
#include "filehandler.h"

class ConfigSaver : public QObject
{
    Q_OBJECT

public:
    ConfigSaver(VPetInterface *parent = nullptr);

    enum configType
    {
        Zoom,
        OnTop,
        Fps,
        Model
    };

    static QString CesarEncrypt(QString str);
    static QString CesarDecrypt(QString str);

    static void loadConfig(VPetInterface *p);

    static void writeConfig(VPetInterface *p);

    static void saveModelPath(QString &path);

    static QStringList *getModelPath();

protected:
    // 读取 json 文件, 并获取根节点
    static QJsonObject *readConfigFile();
    // 保存 json 文件
    static void saveConfigFile(QJsonObject &root);

};

#endif // CONFIGSAVER_H
