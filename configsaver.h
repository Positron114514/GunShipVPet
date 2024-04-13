#ifndef CONFIGSAVER_H
#define CONFIGSAVER_H

#pragma once

#include "qheaders.h"
#include "vpetinterface.h"

#define RELEASE

#ifdef FIXED
#define CONFIG_DIR "E:\\config.json"
#endif

#ifdef RELEASE
#define CONFIG_DIR "config.json"
#endif

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

    static void loadConfig(VPetInterface *p);

    static void writeConfig(VPetInterface *p);

};

#endif // CONFIGSAVER_H
