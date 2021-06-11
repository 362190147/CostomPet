/*
 * BackGround.h
 *
 *  Created on: 2014-11-21
 *      Author: wei
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "GLObject.h"
#include "Texture.h"
namespace cjw3d {

class BackGround: public cjw3d::GLObject {
	Texture *t;
public:
	BackGround(float x,float y ,float z,Texture* t);
	~BackGround();
	virtual void draw();
};

} /* namespace cjw3d */
#endif /* BACKGROUND_H_ */
