#include "llmhandler.h"

// llmhandler
namespace
{
LlmHandler* _llmHandler;
}

// init
LlmHandler::LlmHandler()
{
    // 加载python文件
    chatApi = PyImport_ImportModule(PY_CHAT_API_PATH);
    if(chatApi == NULL)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to load llm/chatapi.py";
    }

    init = PyImport_ImportModule(PY_INIT_PATH);
    if(init == NULL)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to load llm/init.py";
    }

    pyGetCompletion = PythonHandler::getPyFunction(chatApi, PY_GET_COMPLETION);
}

LlmHandler* LlmHandler::getInstance()
{
    if(_llmHandler == NULL)
    {
        _llmHandler = new LlmHandler();
    }

    return _llmHandler;
}

void LlmHandler::getAccessToken(QString apiKey, QString secretKey)
{
    PyObject* args = PyTuple_New(2);
    PyObject* pyGetAccessToken = PythonHandler::getPyFunction(chatApi, PY_GET_ACCESS_TOKEN);

    PyObject* pyApiKey = PyUnicode_FromString(apiKey.toStdString().c_str());
    PyObject* pySecretKey = PyUnicode_FromString(secretKey.toStdString().c_str());

    PyTuple_SetItem(args, 0, pyApiKey);
    PyTuple_SetItem(args, 1, pySecretKey);
    // 运行函数
    accessToken = PyObject_CallObject(pyGetAccessToken, args);
    if(!accessToken)
    {
        qDebug() << QT_DEBUG_OUTPUT << "fail to load access token";
    }else
    {
        qDebug() << QT_DEBUG_OUTPUT << "load access token successfully";
    }
}

// talk with llm
// prompt: input string
// return: output string
QString* LlmHandler::getCompletion(QString *prompt)
{
    PyObject* args = PyTuple_New(2); // 参数1: prompt; 参数2: access_token
    PyObject* pyPrompt = PyUnicode_FromString(prompt->toStdString().c_str());

    PyTuple_SetItem(args, 0, pyPrompt);
    PyTuple_SetItem(args, 1, accessToken);

    PyObject *funcBack = PyObject_CallObject(pyGetCompletion,args);


    // 不确定这能不能用
    char* retRawString;
    PyArg_Parse(funcBack, "s", &retRawString);

    // 检测是否成功调用
    if(strcmp(retRawString, PY_LOAD_JSON_FAILED) == 0)
    {
        qDebug() << QT_DEBUG_OUTPUT << "fail to load json file when getting Completion.";
        return NULL;
    }
    else if(strcmp(retRawString, PY_REQUEST_FAILED))
    {
        qDebug() << QT_DEBUG_OUTPUT << "request failed when getting completion.";
        return NULL;
    }
    else
    {
        return new QString(retRawString);
    }
}


LlmHandler::~LlmHandler()
{
    delete chatApi;
    delete init;
    delete pyGetCompletion;
    delete accessToken;
}
