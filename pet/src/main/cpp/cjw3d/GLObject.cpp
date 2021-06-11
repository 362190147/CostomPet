/*
 * GLObject.cpp
 *
 *  Created on: 2014-11-14
 *      Author: wei
 */

#include "GLObject.h"
#include "GLES/gl.h"
#include "string.h"
#include "Matrix.h"
#include "GLU.h"
namespace cjw3d {
float GLObject::camera[] = {
		0.0f, 0.0f, 4.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f };
int GLObject::width = 1;
int GLObject::height = 1;
float GLObject::near = 1;
float GLObject::far = 1;
float GLObject::sizeH = 1;

float* GLObject::mModelView = new float[16];
float* GLObject::mProject = new float[16];
int* GLObject::viewport = new int[4];
float GLObject::verticesData[12] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f };
float GLObject::texturesData[8] = { 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f };

GLObject::GLObject(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

GLObject::~GLObject() {

}

void GLObject::gluLookAt() {
	Matrix::setLookAtM(mModelView, 0, camera[0], camera[1], camera[2],
			camera[3], camera[4], camera[5], camera[6], camera[7], camera[8]);
	glLoadMatrixf(mModelView);
}

void GLObject::gluLookAt(float eyeX, float eyeY, float eyeZ, float centerX,
		float centerY, float centerZ, float upX, float upY, float upZ) {
	camera[0] = eyeX;
	camera[1] = eyeY;
	camera[2] = eyeZ;
	camera[3] = centerX;
	camera[4] = centerY;
	camera[5] = centerZ;
	camera[6] = upX;
	camera[7] = upY;
	camera[8] = upZ;
	GLObject::gluLookAt();
}

void GLObject::Frustumf(int w, int h, float size, float zNear, float zFar) {
	width = w;
	height = h;
	sizeH = size;
	near = zNear;
	far = zFar;
	int life = 0;
	float ratio = (float) width / (float) height;
	glMatrixMode(GL_PROJECTION); // set matrix to projection mode
	//glLoadIdentity();                        // reset the matrix to its default state
	//glFrustumf(-sizeH*ratio, sizeH*ratio, -sizeH, sizeH, zNear, zFar); // apply the projection matrix
	Matrix::frustumM(mProject, 0, -sizeH * ratio, sizeH * ratio, -sizeH, sizeH,
			zNear, zFar);
	glLoadMatrixf(mProject);

}

/**
 * 设置视图
 * @param x 屏幕坐标
 * @param y 屏幕坐标
 * @param width 视图宽度
 * @param height 视图宽度
 */
void GLObject::viewPort(int x, int y, int width, int height) {
	viewport[0] = x;
	viewport[1] = y;
	viewport[2] = width;
	viewport[3] = height;
	glViewport(x, y, width, height);
}

float* GLObject::getCamera(float* camara) {
	memcpy(camera, GLObject::camera, 16 * sizeof(float));
	return camera;
}

/**
 * 获得屏幕上点的三围坐标
 * @param x 屏幕坐标
 * @param y 屏幕坐标
 * @param d 深度
 * @return 3d坐标
 */
float* GLObject::get3dCoord(float x,float y,float d) {
	float *xyz= new float[4];
	GLU::gluUnProject(x, (float)height-y, d, mModelView, 0, mProject, 0, viewport, 0, xyz, 0);
	xyz[0]/=xyz[3];
	xyz[1]/=xyz[3];
	xyz[2]/=xyz[3];
	return xyz;
}

void GLObject::draw() {
	//
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glDepthMask(false);

	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(5.0f, 5.0f, 5.0f);
	//顶点
	glVertexPointer(3, GL_FLOAT, 0, verticesData);
	//纹理
	//glBindTexture(GL_TEXTURE_2D, texture.id);
	//glTexCoordPointer(2, GL_FLOAT, 0, texturesData);

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
