#ifndef LLMHANDLER_H
#define LLMHANDLER_H

#define PY_GET_ACCESS_TOKEN "get_access_token"
#define PY_GET_COMPLETION "get_completion"
#define PY_CHAT_API_PATH "llm/chatapi"
#define PY_INIT_PATH "llm/init"

// 错误处理
#define PY_LOAD_JSON_FAILED "loadJsonFailed"
#define PY_REQUEST_FAILED "requestFailed"


// 注意: 这里需要强制安装 python3.8.10 在工程项目里面
#include "Python.h"
#include "qheaders.h"

// 使用方法:
// 1. 声明一个 LlmHandler 对象
// 2. 调用方法 getAccessToken 获取 accessToken (因为有可能调用失败所以没有放在构造函数里)
// 3. 调用 getCompletion 方法来对话
class LlmHandler{
public:
    // init
    LlmHandler();

    // 获取python文件中的函数, 并返回一个 PyObject
    static PyObject* getPyFunction(PyObject* pyFile, QString functionName);

    // get access token to wenxin
    void getAccessToken(QString apiKey, QString secretKey);

    // talk with llm
    // prompt: input string
    // return: output string
    // 注意: 如果触发 PY_LOAD_JSON_FAILED 或 PY_REQUEST_FAILED, 返回值为 NULL
    QString* getCompletion(QString *prompt);

    ~LlmHandler();


private:
    PyObject* chatApi;
    PyObject* init;
    // function get_completion from python
    PyObject* pyGetCompletion;
    PyObject* accessToken;
};

#endif // LLMHANDLER_H
