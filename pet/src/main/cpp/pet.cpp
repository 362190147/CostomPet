/*
 * Copyright (C)
 *
 */
#include <string.h>
#include <string>
#include <jni.h>
#include <android/log.h>
#include "util.h"
#include <GLES/gl.h>
#include "cjw3d/GLObject.h"
#include "cjw3d/BackGround.h"
#include "cjw3d/Butterfly.h"
#include "dirent.h"



void searchdir(char *path)
{
	DIR *dp;
	struct dirent *dmsg;
	int i=0;
  char addpath[1000] = {'\0'}, *tmpstr;
  if ((dp = opendir(path)) != NULL)
  {
   while ((dmsg = readdir(dp)) != NULL)
   {
    if (!strcmp(dmsg->d_name, ".") || !strcmp(dmsg->d_name, ".."))
      continue;
    strcpy(addpath, path);
    strcat(addpath, "/");
    strcat(addpath, dmsg->d_name);
    if (dmsg->d_type == DT_DIR )
    {
      char *temp;
      temp=dmsg->d_name;
      if(strchr(dmsg->d_name, '.'))
      {
        if((strcmp(strchr(dmsg->d_name, '.'), dmsg->d_name)==0))
        {

         continue;
        }
      }
      LOGI("........directname:%s",dmsg->d_name);
      searchdir(addpath);
    }
   }
  }
  closedir(dp);
}
using namespace cjw3d;

extern "C" {
JNIEXPORT jstring Java_top_yumesekai_pet_FloatView_stringFromJNI(JNIEnv* env,
		jobject thiz) {
	return env->NewStringUTF("test");
}

JNIEXPORT void Java_top_yumesekai_pet_FloatView_onCreateC(JNIEnv* env, jobject thiz,jobject asssetMar);
JNIEXPORT void Java_top_yumesekai_pet_FloatView_onChangeC(JNIEnv* env, jobject thiz,
		int width, int height);
JNIEXPORT void Java_top_yumesekai_pet_FloatView_onDestroyC(JNIEnv* env, jobject thiz);
JNIEXPORT void Java_top_yumesekai_pet_FloatView_onTouchC(JNIEnv* env, jobject thiz);
JNIEXPORT void Java_top_yumesekai_pet_FloatView_drawC(JNIEnv* env, jobject thiz);
}

GLObject* obj = NULL;
char *StoragePath = NULL;
Texture *t = NULL;

extern "C" {
void Java_top_yumesekai_pet_FloatView_onCreateC(JNIEnv *env, jobject thiz, jobject asssetMar) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/**
	StoragePath = cjwutil::util::getStornagePath(env, thiz);
	//if(StoragePath!=NULL) LOGI(StoragePath);

	char filePath[256];
	sprintf(filePath, "%s/cjwpet/", StoragePath);
	searchdir(StoragePath);
	cjwutil::util::findFiles(filePath);
	sprintf(filePath, "%s/cjwpet/aiyin.png", StoragePath);
	std::string a(filePath);
	t = new Texture(a);
	 */
	std::string a("file:///android_asset/bg.png");
	 t=new Texture(a);
	//obj = (GLObject*)new Butterfly(0.0f, 0.0f, 0.0f, t);
	obj = new BackGround(0, 0, 0, t);
}

void Java_top_yumesekai_pet_FloatView_onChangeC(JNIEnv *env, jobject thiz, int width,
										  int height) {
	GLObject::viewPort(0, 0, width, height);
	GLObject::Frustumf(width, height, 3, 1, 7);
}

void Java_top_yumesekai_pet_FloatView_drawC(JNIEnv *env, jobject thiz) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	GLObject::gluLookAt();
	if (obj != NULL)
		obj->draw();
}

void Java_top_yumesekai_pet_FloatView_onTouchC(JNIEnv *env, jobject thiz) {

}

void Java_top_yumesekai_pet_FloatView_onDestroyC(JNIEnv *env, jobject thiz) {
	if (obj != NULL) {
		delete obj;
		obj = NULL;
	}
}


}