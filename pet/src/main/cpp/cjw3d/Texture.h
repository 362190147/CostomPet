/*
 * Texture.h
 *
 *  Created on: 2014-11-10
 *      Author: wei
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "jni.h"
#include <string>

namespace cjw3d {
class Texture{

public:
	unsigned int id;
	/**图的原始宽度*/
	int widthS;
	/**纹理的宽度*/
	int widthD;
	/**图的原始宽度*/
	int heightS;
	/**纹理的高度*/
	int heightD;
	int num;
	void init();
	Texture(JNIEnv* env, char *fileName);
	Texture(std::string& fileName);
	~Texture();
};
}
#endif /* TEXTURE_H_ */
