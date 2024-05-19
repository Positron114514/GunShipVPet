#include "pythonhandler.h"

void PythonHadler::initPython()
{
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        qDebug() << QT_DEBUG_OUTPUT << "Fail to initiallize python.";
    }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
}
