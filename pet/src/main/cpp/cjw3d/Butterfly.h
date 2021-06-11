/*
 * Butterfly.h
 *
 *  Created on: 2014-11-25
 *      Author: wei
 */

#ifndef BUTTERFLY_H_
#define BUTTERFLY_H_
#include "GLObject.h"
#include "Texture.h"
namespace cjw3d {

class Butterfly : GLObject{
public:
	float targetX;
	float targetY;
	float targetZ;
	Texture* texture;//纹理
	Butterfly(float x,float y,float z,Texture* t);
	~Butterfly();
	virtual void draw();
	void move(int time);
};

} /* namespace cjw3d */
#endif /* BUTTERFLY_H_ */
