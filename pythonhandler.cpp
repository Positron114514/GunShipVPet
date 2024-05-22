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

void PythonHandler::importMoudle(QString moudleName)
{

    QString pySentence = "import " + moudleName;
    PyRun_SimpleString(pySentence.toStdString().c_str());
}

void PythonHandler::importNecessaryPyMoudle()
{
    importMoudle("os");
    importMoudle("requests");
    importMoudle("json");

    PyRun_SimpleString("from requests.exceptions import JSONDecodeError");

    importMoudle("edge_tts");
    importMoudle("asyncio");
}
