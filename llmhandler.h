#ifndef LLMHANDLER_H
#define LLMHANDLER_H

#define PY_GET_ACCESS_TOKEN "get_access_token"
#define PY_GET_COMPLETION "get_completion"
#define PY_CHAT_API_PATH "llm/chatapi"
#define PY_INIT_PATH "llm/init"

#define PY_LOAD_JSON_FAILED "loadJsonFailed"
#define PY_REQUEST_FAILED "requestFailed"


// python headers
// 这里需要修改一下路径, 目前路径是我本机上的路径, 需要从注册表读取用户的python安装路径然后进行操作
// 实在不行可以安装一个python到用户路径(抽象)
#include "C:/Users/Lenovo/AppData/Local/Programs/Python/Python36/include/Python.h"
#include "qheaders.h"

// 使用方法:
// 1. 声明 LlmHandler
// 2. 调用方法 getAccessToken 获取 accessToken (因为有可能调用失败所以没有放在构造函数里)
// 3. 调用 getCompletion 方法来对话
class LlmHandler{
public:
    // init
    LlmHandler();

    // 获取python文件中的函数, 并返回一个 PyObject
    static PyObject* getPyFunction(PyObject* pyFile, QString functionName);

    // get access token to wenxin
    void getAccessToken();

    // talk with llm
    // prompt: input string
    // return: output string
    QString* getCompletion(QString *prompt);


private:
    PyObject* chatApi;
    PyObject* init;
    // function get_completion from python
    PyObject* pyGetCompletion;
    PyObject* accessToken;
};

#endif // LLMHANDLER_H
