/*
 * BackGround.cpp
 *
 *  Created on: 2014-11-21
 *      Author: wei
 */

#include "BackGround.h"
#include "GLES/gl.h"
namespace cjw3d {

BackGround::BackGround(float x, float y, float z,Texture* t):GLObject(x, y, z){
	this->t=t;
}

BackGround::~BackGround() {
	// TODO Auto-generated destructor stub
}
void BackGround::draw(){
	//
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);
		glDepthMask(false);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glPushMatrix();

		float *xyz= GLObject::get3dCoord(width/2, height/2, 0.999999f);
		glTranslatef(xyz[0], xyz[1], xyz[2]);
		float temp=sizeH*2/near*far;
		glTranslatef(x, y, z);

		glScalef(temp*width/height, temp, 1.0f);

		//glScalef(5.0f, 5.0f, 5.0f);
		//顶点
		glVertexPointer(3, GL_FLOAT, 0, verticesData);
		//纹理
		glBindTexture(GL_TEXTURE_2D, t->id);
		glTexCoordPointer(2, GL_FLOAT, 0, texturesData);

		//画图
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glPopMatrix();
		//取消
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_BLEND);
		glDepthMask(false);
}

} /* namespace cjw3d */
