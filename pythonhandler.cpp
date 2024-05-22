#include "pythonhandler.h"

void PythonHandler::initPython()
{
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to initiallize python.";
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
}

PyObject* PythonHandler::getPyFunction(PyObject* pyFile, QString functionName)
{
    PyObject* retObj = PyObject_GetAttrString(pyFile, functionName.toStdString().c_str());
    if(!retObj)
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to load function: " << functionName;
    }
    return retObj;
}
