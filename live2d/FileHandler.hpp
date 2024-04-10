#ifndef FILEHANDLER_H
#define FILEHANDLER_H

/**
 * 管理Qt和live2D处理文件的方式 以及模型切换功能
 */

#include "LAppLive2DManager.hpp"
#include "LAppPal.hpp"
#include "qheaders.h"

// Unfinished
class FileHandler{
public:
    // 获取当前的模型数量
    static int getModelNum();

    // 根据索引切换模型
    static void switchModel(int index);

    // 切换至下一个模型
    static void switchModel();

    // 添加模型
    static void addModel(Csm::csmString path);

    // 获取模型路径列表
    // 返回值类型: QStringList
    static QStringList *getModelList();

};

#endif // FILEHANDLER_H
