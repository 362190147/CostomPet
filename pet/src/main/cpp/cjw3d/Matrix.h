/*
 * Matrix.h
 *
 *  Created on: 2014-11-14
 *      Author: wei
 */

#ifndef MATRIX_H_
#define MATRIX_H_

namespace cjw3d {

class Matrix {
public:
	Matrix();
	~Matrix();
	static void multiplyMM(float result[], int resultOffset, float lhs[], int lhsOffset, float rhs[], int rhsOffset);

    static void multiplyMV(float resultVec[],
    		int resultVecOffset, float lhsMat[], int lhsMatOffset,
    		float rhsVec[], int rhsVecOffset);

	static void transposeM(float mTrans[], int mTransOffset, float m[],int mOffset);

	static bool invertM(float mInv[], int mInvOffset, float m[], int mOffset);

	static void orthoM(float m[], int mOffset,
	       float left, float right, float bottom, float top,
	       float near, float far);

	static void frustumM(float m[], int offset,
	           float left, float right, float bottom, float top,
	           float near, float far);

	static void perspectiveM(float m[], int offset,
		         float fovy, float aspect, float zNear, float zFar);

	static float length(float x, float y, float z);

	static void setIdentityM(float sm[], int smOffset);

	static void scaleM(float sm[], int smOffset,
	           float m[], int mOffset,
	           float x, float y, float z);
	static void scaleM(float m[], int mOffset,
	           float x, float y, float z);

	static void translateM(float tm[], int tmOffset,
	           float m[], int mOffset,
	           float x, float y, float z);

	static void translateM(
	           float m[], int mOffset,
	           float x, float y, float z);

	static void rotateM(float rm[], int rmOffset,
	           float m[], int mOffset,
	           float a, float x, float y, float z);

	static void setRotateM(float rm[], int rmOffset,
	            float a, float x, float y, float z);

	static void setRotateEulerM(float rm[], int rmOffset,
	           float x, float y, float z);

	static void setLookAtM(float rm[], int rmOffset,
	           float eyeX, float eyeY, float eyeZ,
	           float centerX, float centerY, float centerZ, float upX, float upY,
	           float upZ);

};

} /* namespace cjw3d */
#endif /* MATRIX_H_ */
