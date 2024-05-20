#ifndef FILEHANDLER_H
#define FILEHANDLER_H

/**
 * 管理Qt和live2D处理文件的方式 以及模型切换功能
 */

#include "live2d/LAppLive2DManager.hpp"
#include "live2d/LAppWavFileHandler.hpp"
#include "live2d/LAppPal.hpp"
#include "qheaders.h"

#define BUF_SIZE 256

// Unfinished
class FileHandler
{
public:
    // 一些操作模型的函数
    // 获取当前的模型数量
    static int getModelNum();

    // 根据索引切换模型
    static void switchModel(int index);

    // 切换至下一个模型
    static void switchModel();

    // 添加模型
    static void addModel(QString path);

    // 获取模型路径列表
    // 返回值类型: QStringList
    static QStringList &getModelDirList();

    // 保存模型路径到 config.json
    static void saveModelPath(QString &path);

    // 从 config.json 中获取模型路径
    static QStringList *getModelPath();

    // static void getModelPath

    // sourceDir -> toDir
    static bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist=true);

    // fromDir -> toDir, 复制文件夹中的内容
    static bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist=true);

    // 删除路经为的dir文件夹
    static bool deleteFolder(const QString &folderPath);

    // 重新加载模型列表
    static void resetModel();

    // 一些类型转换函数
    // 用不用都行, 设成 public 了

    //
    static Csm::csmString &toCsmString(const QString &target);

    static Csm::csmVector<Csm::csmString> &toCsmStringList(const QStringList &target);

    static QString &toQString(const Csm::csmString &target);

    static QStringList &toQStringList(const Csm::csmVector<Csm::csmString> &target);
};

#endif // FILEHANDLER_H
