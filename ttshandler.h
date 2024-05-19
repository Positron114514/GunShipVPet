#ifndef TTSHANDLER_H
#define TTSHANDLER_H

// paths
#define PY_TTS_PATH "python/tts/ttsApi"

#define MP3_SAVE_PATH "./mp3/"

// voices
#define VOICE_NUMBER 6
// female
#define VOICE_CN_XIOAXIAO "zh-CN-XiaoxiaoNeural"
#define VOICE_CN_XIAOYI "zh-CN-XiaoyiNeural"
#define VOICE_CN_YUNXIA "zh-CN-YunxiaNeural"
// male
#define VOICE_CN_YUNJIAN "zh-CN-YunjianNeural"
#define VOICE_CN_YUNXI "zh-CN-YunxiNeural"
#define VOICE_CN_YUNYANG "zh-CN-YunyangNeural"

#include "Python.h"
#include "qheaders.h"

class TtsHandler
{
public:
    TtsHandler();

    void textToMp3File(QString* text, int modelIndex,
                       QString rate = "-4%", QString volume = "+0%",
                       QString fileName = "voice.mp3");

    QStringList* getVoiceList();

    void setModelVoice(int modelIndex, int VoiceIndex);

    ~TtsHandler();

private:
    PyObject* ttsApi;
    PyObject* pyTextToMp3File;
    QStringList* voiceList;
    // 该list顺序和model的顺序一致
    QVector<int>* modleVoiceList;
};


#endif // TTSHANDLER_H
