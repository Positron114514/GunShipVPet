#include "llmhandler.h"

// init
LlmHandler::LlmHandler()
{
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to initiallize python.";
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    // 加载python文件
    chatApi = PyImport_ImportModule(PY_CHAT_API_PATH);
    if(!chatApi)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to load llm/chatapi.py";
    }

    init = PyImport_ImportModule(PY_INIT_PATH);
    if(!init)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to load llm/init.py";
    }

    pyGetCompletion = getPyFunction(chatApi, PY_GET_COMPLETION);
}

PyObject* LlmHandler::getPyFunction(PyObject* pyFile, QString functionName)
{
    PyObject* retObj = PyObject_GetAttrString(pyFile, functionName.toStdString().c_str());
    if(!retObj)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to load function: " << functionName;
    }
    return retObj;
}

void LlmHandler::getAccessToken()
{
    PyObject* pyGetAccessToken = getPyFunction(chatApi, PY_GET_ACCESS_TOKEN);
    // 运行函数
    accessToken = PyObject_CallFunction(pyGetAccessToken, 0);
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
