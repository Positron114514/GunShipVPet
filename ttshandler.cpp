#include "ttshandler.h"

TtsHandler::TtsHandler()
{
    // init voioce list
    _voiceList = new QStringList();
    _voiceList->append(VOICE_CN_XIAOYI);
    _voiceList->append(VOICE_CN_XIOAXIAO);
    _voiceList->append(VOICE_CN_YUNJIAN);
    _voiceList->append(VOICE_CN_YUNXI);
    _voiceList->append(VOICE_CN_YUNXIA);
    _voiceList->append(VOICE_CN_YUNYANG);
    // set rate
    _rate = PyUnicode_FromString("-4%");
    // volume
    _volume = PyUnicode_FromString("+0%");
    // mp3SavePath
    _mp3SaveFileName = PyUnicode_FromString(MP3_SAVE_FILE);

    // player
    _player = new QMediaPlayer();
    if(!_player->isAvailable())
    {
        qDebug() << QT_DEBUG_OUTPUT << "player is not avaliable on this platform";
    }

    // get text_to_mp3_file in python
    _ttsApi = PyImport_ImportModule(PY_TTS_PATH);
    _pyTextToMp3File = PythonHandler::getPyFunction(_ttsApi, "text_to_mp3_file");
}

void TtsHandler::textToMp3File(QString* text, int voiceIndex)
{
    PyObject* args = PyTuple_New(5);
    // text
    PyObject* pyText = PyUnicode_FromString(text->toStdString().c_str());
    // voice
    PyObject* pyVoice = PyUnicode_FromString((*_voiceList)[voiceIndex].toStdString().c_str());

    PyTuple_SetItem(args, 0, pyText);
    PyTuple_SetItem(args, 1, pyVoice);
    PyTuple_SetItem(args, 2, _rate);
    PyTuple_SetItem(args, 3, _volume);
    PyTuple_SetItem(args, 4, _mp3SaveFileName);

    PyObject_CallObject(_pyTextToMp3File, args);
}

void TtsHandler::setRate(int rate)
{
    if(rate > 100 || rate < -100)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Invalid rate";
        return;
    }

    char newRate[10] = {};

    if(rate >= 0)
    {
        sprintf(newRate, "+%d%%", rate);
    }else
    {
        sprintf(newRate, "%d%%", rate);
    }

    _rate = PyUnicode_FromString(newRate);
}

void TtsHandler::setVolume(int volume)
{
    if(volume > 100 || volume < -100)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Invalid volume";
        return;
    }

    char newVolume[10] = {};

    if(volume >= 0)
    {
        sprintf(newVolume, "+%d%%", volume);
    }else
    {
        sprintf(newVolume, "%d%%", volume);
    }

    _volume = PyUnicode_FromString(newVolume);
}

void TtsHandler::speak(QString* text, int voiceIndex)
{
    textToMp3File(text, voiceIndex);

    // 防止声音混乱
    stop();

    _player->setSource(QUrl::fromLocalFile(MP3_SAVE_FILE));
    // 如果是在资源文件里用 fromEncoded 函数获取地址
    //player->setMedia(QUrl::fromEncoded("qrc:/mp3/552800.mp3"));
    _player->play();
}

void TtsHandler::stop()
{
    if(_player->isPlaying())
    {
        _player->stop();
    }
}
