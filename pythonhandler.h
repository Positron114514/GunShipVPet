#ifndef PYTHONHANDLER_H
#define PYTHONHANDLER_H

#include "Python.h"
#include "qheaders.h"

class PythonHandler
{
public:
    static void initPython();
    // 获取python文件中的函数, 并返回一个 PyObject
    static PyObject* getPyFunction(PyObject* pyFile, QString functionName);
    // import python moudle
    static void importMoudle(QString moduleName);
    // import 工程必须的库
    static void importNecessaryPyMoudle();
};

#endif // PYTHONHANDLER_H
