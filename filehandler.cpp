#include "FileHandler.h"

void FileHandler::switchModel(int index)
{
    if (index < 0 || index > LAppLive2DManager::GetInstance()->GetModelNum())
    {
        LAppPal::PrintLogLn("Invalid index");
    }
    LAppLive2DManager::GetInstance()->ChangeScene(index);
}

void FileHandler::switchModel()
{
    LAppLive2DManager::GetInstance()->NextScene();
}

int FileHandler::getModelNum()
{
    return LAppLive2DManager::GetInstance()->GetModelDirSize();
}

void FileHandler::addModel(QString path)
{
    LAppLive2DManager::GetInstance()->AddModel(path.toLocal8Bit().data());
}

QStringList &FileHandler::getModelDirList()
{
    return toQStringList(LAppLive2DManager::GetInstance()->GetModelDir());
}


// 一些类型转换函数
// 主要方便这个文件里一些函数
// 用不用都行, 设成 public 了

//
Csm::csmString &FileHandler::toCsmString(const QString &target)
{
    return *new Csm::csmString(target.toStdString().c_str());
}

Csm::csmVector<Csm::csmString> &FileHandler::toCsmStringList(const QStringList &target)
{
    Csm::csmVector<Csm::csmString> *retVector = new Csm::csmVector<Csm::csmString>();
    for(auto x:target)
    {
        retVector->PushBack(toCsmString(x));
    }

    return *retVector;
}

QString &FileHandler::toQString(const Csm::csmString &target)
{
    return *new QString(target.GetRawString());
}

QStringList &FileHandler::toQStringList(const Csm::csmVector<Csm::csmString> &target)
{
    QStringList *retList = new QStringList();

    for(int i = 0; i < target.GetSize(); i++)
    {
        retList->push_back(toQString(target[i]));
    }

    return *retList;
}
