#include "ttshandler.h"
#include "customdir.h"

namespace
{
TtsHandler* _ttsHandler;
}


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
    _mp3SaveFileName = PyUnicode_FromString(CustomDir::voiceOutputDir().toUtf8());

    // player
    _player = new QMediaPlayer();
    if(!_player->isAvailable())
    {
        qDebug() << QT_DEBUG_OUTPUT << "player is not avaliable on this platform";
    }
    _audioOutput = new QAudioOutput();
    _audioOutput->setVolume(50);
    _player->setAudioOutput(_audioOutput);

    // get text_to_mp3_file in python
    _ttsApi = PyImport_ImportModule(PY_TTS_PATH);
    if(_ttsApi == NULL)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to load ttsApi.";
    }
    _pyTextToMp3File = PythonHandler::getPyFunction(_ttsApi, "text_to_mp3_file");

    qDebug() << QT_DEBUG_OUTPUT << "init ttsHandler successfully.";
}

bool TtsHandler::isValidIndex(int voiceIndex)
{
    if(voiceIndex >= VOICE_NUMBER || voiceIndex < 0)
    {
        qDebug() << QT_DEBUG_OUTPUT << "incalid voiceIndex";
        return false;
    }
    else
    {
        return true;
    }
}

TtsHandler* TtsHandler::getInstance()
{
    if(_ttsHandler == NULL)
    {
        _ttsHandler = new TtsHandler();
    }

    return _ttsHandler;
}

void TtsHandler::textToMp3File(QString* text, int voiceIndex)
{
    qDebug() << QT_DEBUG_OUTPUT << "loading textToMp3File";
    if(!isValidIndex(voiceIndex))
    {
        return;
    }

    PyObject* args = PyTuple_New(5);
    // text
    qDebug() << QT_DEBUG_OUTPUT << "speaking: " << text->toStdString().c_str();
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

void TtsHandler::setVolume(double volume)
{
    if(volume > 100 || volume < 0)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Invalid volume";
        return;
    }

    _audioOutput->setVolume(volume);
}

void TtsHandler::speak(QString* text, int voiceIndex)
{
    if(!isValidIndex(voiceIndex))
    {
        return;
    }

    textToMp3File(text, voiceIndex);

    // 防止声音混乱
    stop();

    _player->setSource(QUrl::fromLocalFile(CustomDir::voiceOutputDir()));

    qDebug() << QT_DEBUG_OUTPUT << "set player source: " << CustomDir::voiceOutputDir();
    // 如果是在资源文件里用 fromEncoded 函数获取地址
    //player->setMedia(QUrl::fromEncoded("qrc:/mp3/552800.mp3"));

    _player->play();
}

void TtsHandler::test(int voiceIndex)
{
    if(!isValidIndex(voiceIndex))
    {
        return;
    }

    QString s = QString::fromUtf8("你好, 这是一条测试");
    speak(&s, voiceIndex);
}

void TtsHandler::stop()
{
    if(_player->isPlaying())
    {
        _player->stop();
    }
}

QStringList* TtsHandler::getVoiceList()
{
    return _voiceList;
}

TtsHandler::~TtsHandler()
{
    delete _ttsApi;
    delete _pyTextToMp3File;
    delete _voiceList;
    delete _rate;
    delete _volume;
    delete _mp3SaveFileName;
    delete _player;
}
