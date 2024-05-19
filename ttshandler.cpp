#include "ttshandler.h"

TtsHandler::TtsHandler()
{
    voiceList = new QStringList();
    voiceList->append(VOICE_CN_XIAOYI);
    voiceList->append(VOICE_CN_XIOAXIAO);
    voiceList->append(VOICE_CN_YUNJIAN);
    voiceList->append(VOICE_CN_YUNXI);
    voiceList->append(VOICE_CN_YUNXIA);
    voiceList->append(VOICE_CN_YUNYANG);
    ttsApi = PyImport_ImportModule(PY_TTS_PATH);
}
