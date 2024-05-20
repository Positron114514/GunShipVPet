#include "FileHandler.h"
#include "configsaver.h"


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

void FileHandler::saveModelPath(QString &path)
{
    ConfigSaver::saveModelPath(path);
}

QStringList *FileHandler::getModelPath()
{
    QStringList *ret = ConfigSaver::getModelPath();
    if(ret == NULL)
    {
        return new QStringList();
    }
    return ret;
}

//拷贝文件：
bool FileHandler::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

//拷贝文件夹：
bool FileHandler::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                    targetDir.filePath(fileInfo.fileName()),
                                    coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                             targetDir.filePath(fileInfo.fileName()))){
                return false;
            }
        }
    }
    return true;
}

// 删除文件夹
bool FileHandler::deleteFolder(const QString &folderPath)
{
    if(folderPath.isEmpty() || !QDir().exists(folderPath))
    {
        qDebug() << QT_BACKGROUND_LOG << "delete folder: invalid path";
        return false;
    }

    QFileInfo info(folderPath);

    if(info.isFile())
    {
        qDebug() << QT_BACKGROUND_LOG << "delete folder: dir isn't a folder";
        return false;
    }

    if(info.isDir())
    {
        QDir dir(folderPath);
        dir.removeRecursively();
        qDebug() << QT_BACKGROUND_LOG << "delete folder: deleted dir";
        return true;
    }

    qDebug() << QT_BACKGROUND_LOG << "delete folder: unknown fault";
    return false;
}

void FileHandler::resetModel()
{
    LAppLive2DManager::GetInstance()->SetUpModel();
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
