/*
 * GLObject.h
 *
 *  Created on: 2014-11-14
 *      Author: wei
 */

#ifndef GLOBJECT_H_
#define GLOBJECT_H_
#include "Matrix.h"
namespace cjw3d {

class GLObject {
protected:
	//摄像机位置
	static float camera[];
	/**屏幕宽度*/
	static int width;
	/**屏幕高度*/
	static int height;
	/**最近距离*/
	static float near;
	/**最远距离*/
	static float far;
	/**最近点屏幕的最大高度*/
	static float sizeH;
	/**投影矩阵*/
	static float* mProject;
	/**视图矩阵*/
	static float* mModelView;
	/**视图属性*/
	static int* viewport;
	/**默认顶点*/
	static float verticesData[12];
	/**默认纹理坐标*/
	static float texturesData[8];
	/**物体中心点x坐标*/
	float x;
	/**物体中心点y坐标*/
	float y;
	/**物体中心点z坐标*/
	float z;
	/**物体x坐标上的扩大率*/
	float xRat;
	/**物体y坐标上的扩大率*/
	float yRate;
	/**物体z坐标上的扩大率*/
	float zRate;
	/**生命*/
	float life;
	/**是否碰撞检测*/
	bool hanteiFlag;
public:
	GLObject(float x,float y,float z);
	virtual ~GLObject();
	virtual void draw();
	//virtual void onTouch();
	/**设置模型矩阵*/
	static void gluLookAt();
	static void gluLookAt(float eyeX, float eyeY, float eyeZ, float centerX,
			float centerY, float centerZ, float upX, float upY, float upZ);
	static void Frustumf(int w, int h, float size, float zNear, float zFar);
	static void viewPort(int x, int y, int width, int height);
	static float* getCamera(float* camera);
	static float* get3dCoord(float x,float y,float d);
};

} /* namespace cjw3d */
#endif /* GLOBJECT_H_ */
