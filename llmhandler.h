#ifndef LLMHANDLER_H
#define LLMHANDLER_H

#define PY_GET_ACCESS_TOKEN "get_access_token"
#define PY_GET_COMPLETION "get_completion"
#define PY_CHAT_API_PATH "llm/chatapi"
#define PY_INIT_PATH "llm/init"


// python headers
#include "C:/Users/Lenovo/AppData/Local/Programs/Python/Python36/include/Python.h"
#include "qheaders.h"


class LlmHandler{
public:
    // init
    LlmHandler();

    // 获取python文件中的函数, 并返回一个 PyObject
    static PyObject* getPyFunction(PyObject* pyFile, QString functionName);

    // get access token to wenxin
    QString* getAccessToken();

    // talk with llm
    // prompt: input string
    // return: output string
    QString* getCompletion(QString *prompt);


private:
    PyObject* chatApi;
    PyObject* init;
    // function get_completion from python
    PyObject* pyGetCompletion;
    QString* accessToken;
};

#endif // LLMHANDLER_H
