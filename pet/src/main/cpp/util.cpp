/*
 * util.cpp
 *
 *  Created on: 2014-11-25
 *      Author: wei
 */

#include "util.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>
namespace cjwutil {

AssetData::AssetData(size_t size){
	this->size	= size;
	this->pData	= new unsigned char[size];;

}

AssetData::~AssetData(){
	delete[] this->pData;
	this->pData = NULL;
}

util::util() {
	// TODO Auto-generated constructor stub

}

util::~util() {
	// TODO Auto-generated destructor stub
}

//获得储存器路径
char* util::getStornagePath(JNIEnv* env, jobject thiz) {
	jclass Environment = env->FindClass("android/os/Environment");
	jclass File = env->FindClass("java/io/File");
	jmethodID getExternalStorageDirectory = env->GetStaticMethodID(Environment,
			"getExternalStorageDirectory", "()Ljava/io/File;");

	jobject file = env->CallStaticObjectMethod(Environment,
			getExternalStorageDirectory);
	jmethodID getPath = env->GetMethodID(File, "getPath",
			"()Ljava/lang/String;");
	jstring path = (jstring) env->CallObjectMethod(file, getPath);
	jboolean t;
	return (char *) env->GetStringUTFChars(path, &t);
}

// 从asset 读取文件
AssetData* util::asset_open(AAssetManager* assetMgr, char* pszFileName) {
	AAsset * pAsset = AAssetManager_open(assetMgr, pszFileName,
			AASSET_MODE_UNKNOWN);
	AssetData* assetData = NULL;
	if (pAsset == NULL)
		return NULL;
	size_t size = AAsset_getLength(pAsset);
	if (size > 0) {
		assetData = new AssetData(size);
		int iRet = AAsset_read(pAsset, assetData->pData, size);
		if (iRet <= 0) {
			delete assetData;
			assetData = NULL;
		}
	}
	AAsset_close(pAsset);
	if (pAsset == NULL)
		size = 0;
	return assetData;
}

void util::findFiles(char* file_folder)
{

    DIR *pDir = NULL;
    struct dirent *dmsg;
    char szFileName[128];
    char szFolderName[128];

    strcpy(szFolderName, file_folder);
    strcat(szFolderName, "/%s");
    if ((pDir = opendir(file_folder)) != NULL)
    {
        // 遍历目录
        while ((dmsg = readdir(pDir)) != NULL)
        {
            if (strcmp(dmsg->d_name, ".") != 0 && strcmp(dmsg->d_name, "..") != 0)
            {
                sprintf(szFileName, szFolderName, dmsg->d_name);
                //printf(szFileName);
            }
        }
    }

    if (pDir != NULL)
    {
        closedir(pDir);
    }
}
} /* namespace cjwutil */
