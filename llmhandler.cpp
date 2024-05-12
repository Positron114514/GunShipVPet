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

QString* LlmHandler::getAccessToken()
{
    PyObject* pyGetAccessToken = getPyFunction(chatApi, PY_GET_ACCESS_TOKEN);

}
