#ifndef TTSHANDLER_H
#define TTSHANDLER_H

// paths
#define PY_TTS_PATH "python/tts/ttsApi"

#define MP3_SAVE_FILE "./mp3/voice.mp3"

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

#include "pythonhandler.h"
#include "Python.h"
#include "qheaders.h"

class TtsHandler
{
public:
    TtsHandler();

    // call text_to_mp3_file in python
    void textToMp3File(QString* text, int voiceIndex);

    // 获取所有可使用声音的list
    // 返回值为原指针, 可能存在危险
    QStringList* getVoiceList();

    // void setModelVoice(int modelIndex, int VoiceIndex);

    // 说话(直接调用该函数即可)
    void speak(QString* text, int vopiceIndex);

    // 停止说话
    void stop();

    // 调整 rate
    // range: -100 ~ 100
    void setRate(int rate);

    // 调整 volume
    // range: -100 ~ 100
    void setVolume(int volume);

    ~TtsHandler();

private:
    PyObject* _ttsApi;
    PyObject* _pyTextToMp3File;
    QStringList* _voiceList;
    PyObject* _rate;
    PyObject* _volume;
    PyObject* _mp3SaveFileName;
    QMediaPlayer * _player;
};


#endif // TTSHANDLER_H
