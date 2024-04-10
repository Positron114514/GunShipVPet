#include "FileHandler.hpp"

void FileHandler::switchModel(int index){
    if (index < 0 || index > LAppLive2DManager::GetInstance()->GetModelNum()){
        LAppPal::PrintLogLn("Invalid index");
    }
    LAppLive2DManager::GetInstance()->ChangeScene(index);
}

void FileHandler::switchModel(){
    LAppLive2DManager::GetInstance()->NextScene();
}

int FileHandler::getModelNum(){
    return LAppLive2DManager::GetInstance()->GetModelDirSize();
}

void FileHandler::addModel(Csm::csmString path){
    LAppLive2DManager::GetInstance()->AddModel(path);
}

QStringList *FileHandler::getModelList(){
    QStringList *returnList = new QStringList();
    auto modelList = LAppLive2DManager::GetInstance()->GetModelDir();

    // 将 vector<Csm::csmString> 转化为 QStringList
    for(int i = 0; i < LAppLive2DManager::GetInstance()->GetModelDirSize(); i++){
        returnList->push_back(modelList[i].GetRawString());
    }
    return returnList;
}
