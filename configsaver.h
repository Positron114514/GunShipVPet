#ifndef CONFIGSAVER_H
#define CONFIGSAVER_H

#pragma once

#include "qheaders.h"
#include "vpetinterface.h"



#define CONFIG_DIR "E:\\config.json"

class ConfigSaver : public QWidget
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

    // void initConfigSaver(VPetInterface *p);
    static void loadConfig(VPetInterface *p);

    static void writeConfig(VPetInterface *p);

};

#endif // CONFIGSAVER_H
