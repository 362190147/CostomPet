/*
 * Butterfly.cpp
 *
 *  Created on: 2014-11-25
 *      Author: wei
 */

#include "Butterfly.h"
#include <GLES/gl.h>
#include <stdlib.h>
#include <math.h>
namespace cjw3d {

float ver1[] = { -0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.0f };

float tex1[] = { 0.0f, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f };

void moveTo(float* position, float target, int t) {
	if (abs(*position - target) > 0.001f) {
		if (*position > target)
			*position -= 0.03f * t;
		else
			*position += 0.03f * t;
		if (abs(*position - target) < 0.03f * t)
			*position = target;
	}
}

Butterfly::Butterfly(float x, float y, float z, Texture* t) :
		GLObject(x, y, z) {
	this->targetX = x;
	this->targetY = y;
	this->targetZ = z;
	this->texture = t;

}

Butterfly::~Butterfly() {

}

void Butterfly::move(int t) {
	static bool turn = false;
	static float angle = 50.0f;
	static float f = 50.0f;
	moveTo(&x, targetX, t);
	moveTo(&y, targetY, t);
	moveTo(&z, targetZ, t);

	if (turn) {
		angle++;
		if (angle > 50.0f)
			turn = false;
	} else {
		angle--;
		if (angle < 0.0f)
			turn = true;
	}

	if (abs(targetX - x) > 0.1f)
		if (targetX < x) {
			if (f < 180)
				f += 4;
		} else {
			if (f > 0)
				f -= 4;
		}
		glRotatef( f, 0.0f, 1.0f, 0.0f);
		glRotatef( -20-f/4.5f, 0, 0, 1.0f);

		glRotatef( angle, 0.0f, 1.0f, 0.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glRotatef(2.0f*angle, 0.0f, -1.0f, 0.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Butterfly::draw() {

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glDepthMask(false);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(5.0f, 5.0f, 5.0f);
	//顶点
	glVertexPointer(3, GL_FLOAT, 0, ver1);
	//纹理
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexCoordPointer(2, GL_FLOAT, 0, tex1);

	//画图
	move(1);

	glPopMatrix();
	//取消
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_BLEND);
	glDepthMask(false);
}
} /* namespace cjw3d */
