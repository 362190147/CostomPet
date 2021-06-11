/*
 * GLU.h
 *
 *  Created on: 2014-11-14
 *      Author: wei
 */

#ifndef GLU_H_
#define GLU_H_

namespace cjw3d {

class GLU {
public:
	GLU();
	~GLU();
	static char* gluErrorString(int error);
	static void gluLookAt(float eyeX, float eyeY, float eyeZ,
			float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
	static void gluOrtho2D(float left, float right,
	           float bottom, float top);
	static void gluPerspective(float fovy, float aspect,
	           float zNear, float zFar);
	static int gluProject(float objX, float objY, float objZ,
	            float* model, int modelOffset, float* project, int projectOffset,
	            int* view, int viewOffset, float *win, int winOffset);
	static int gluUnProject(float winX, float winY, float winZ,
	           float *model, int modelOffset, float* project, int projectOffset,
	           int *view, int viewOffset, float* obj, int objOffset);
};

} /* namespace cjw3d */
#endif /* GLU_H_ */
