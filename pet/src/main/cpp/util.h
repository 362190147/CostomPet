/*
 * util.h
 *
 *  Created on: 2014-11-25
 *      Author: wei
 */

#ifndef UTIL_H_
#define UTIL_H_
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#ifndef LOGI(...)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "pet", __VA_ARGS__)
#endif
#ifndef LOGW(...)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "pet", __VA_ARGS__)
#endif
namespace cjwutil {

class AssetData{
	public:
		unsigned char *pData;
		size_t size;
		AssetData(size_t size);
		~AssetData();
};

class util {

public:
	util();
	~util();
	static void findFiles(char* file_folder);
	//获得储存器路径
	static char* getStornagePath(JNIEnv* env, jobject thiz) ;
	static AssetData* asset_open(AAssetManager* assetMgr, char* pszFileName);

};


} /* namespace cjwutil */
#endif /* UTIL_H_ */
