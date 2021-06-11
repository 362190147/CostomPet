/*
 * Texture.cpp
 *
 *  Created on: 2014-11-10
 *      Author: wei
 */

#include "Texture.h"
#include "../util.h"
#include "GLES/gl.h"
#include "../png/Image.h"
namespace cjw3d {

unsigned char* do_Stretch_Linear(int w_Dest, int h_Dest, int bit_depth,
		unsigned char *src, int w_Src, int h_Src) {
	int sw = w_Src - 1, sh = h_Src - 1, dw = w_Dest - 1, dh = h_Dest - 1;
	int B, N, x, y;
	int nPixelSize = bit_depth / 8;
	unsigned char *pLinePrev, *pLineNext;
	unsigned char *pDest = new unsigned char[w_Dest * h_Dest * bit_depth / 8];
	unsigned char *tmp;
	unsigned char *pA, *pB, *pC, *pD;

	for (int i = 0; i <= dh; ++i) {
		tmp = pDest + i * w_Dest * nPixelSize;
		y = i * sh / dh;
		N = dh - i * sh % dh;
		pLinePrev = src + (y++) * w_Src * nPixelSize;
		//pLinePrev =(unsigned char *)aSrc->m_bitBuf+((y++)*aSrc->m_width*nPixelSize);
		pLineNext = (N == dh) ? pLinePrev : src + y * w_Src * nPixelSize;
		//pLineNext = ( N == dh ) ? pLinePrev : (unsigned char *)aSrc->m_bitBuf+(y*aSrc->m_width*nPixelSize);
		for (int j = 0; j <= dw; ++j) {
			x = j * sw / dw * nPixelSize;
			B = dw - j * sw % dw;
			pA = pLinePrev + x;
			pB = pA + nPixelSize;
			pC = pLineNext + x;
			pD = pC + nPixelSize;
			if (B == dw) {
				pB = pA;
				pD = pC;
			}

			for (int k = 0; k < nPixelSize; ++k) {
				*tmp++ = (unsigned char) (int) ((B * N
						* (*pA++ - *pB - *pC + *pD) + dw * N * *pB++
						+ dh * B * *pC++ + (dw * dh - dh * B - dw * N) * *pD++
						+ dw * dh / 2) / (dw * dh));
			}
		}
	}
	return pDest;
}
int get2(int s) {
	int d = 2;
	while (d < s)
		d <<= 1;
	return d;
}
void Texture::init() {
	num = 0;
	unsigned int temp[1] = { 0 };
	glGenTextures(1, temp);
	id = temp[0];
}

Texture::Texture(JNIEnv* env, char *fileName) {
	init();
	jclass BitmapFactory = env->FindClass("android/graphics/BitmapFactory");
	jclass Bitmap = env->FindClass("android/graphics/Bitmap");
	jclass GLUtils = env->FindClass("android/opengl/GLUtils");

	//下面代码和等同Bitmap = BitmapFactory.decodeFile(file);
	jmethodID decodeFile = env->GetStaticMethodID(BitmapFactory, "decodeFile",
			"(Ljava/lang/String;)Landroid/graphics/Bitmap;");
	jstring file = env->NewStringUTF(fileName);
	jobject bitmap = env->CallStaticObjectMethod(BitmapFactory, decodeFile,
			file);
	env->ReleaseStringUTFChars(file, fileName);

	//widthS	= bitmap.getWidth();
	jmethodID getWidth = env->GetMethodID(Bitmap, "getWidth", "()I");
	widthS = env->CallIntMethod(bitmap, getWidth);

	//heightS	= bitmap.getHeight();
	jmethodID getHeight = env->GetMethodID(Bitmap, "getHeight", "()I");
	heightS = env->CallIntMethod(bitmap, getHeight);

	widthD = get2(widthS);
	heightD = get2(heightS);
	jobject bitmap2 = NULL;
	if (widthD != widthS || heightS != heightD) {
		//Bitmap bitmap2=Bitmap.createScaledBitmap(bitmap, widthD, heightD, false );
		jmethodID createScaledBitmap = env->GetStaticMethodID(Bitmap,
				"createScaledBitmap",
				"(Landroid/graphics/Bitmap;IIZ)Landroid/graphics/Bitmap;");
		bitmap2 = env->CallStaticObjectMethod(Bitmap, createScaledBitmap,
				bitmap, widthD, heightD, (jboolean) 0);

	} else {
		bitmap2 = bitmap;
	}

	glBindTexture(GL_TEXTURE_2D, id);
	// Set filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load the bitmap into the bound texture.
	//GLUtils	.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
	jmethodID texImage2D = env->GetStaticMethodID(GLUtils, "texImage2D",
			"(IILandroid/graphics/Bitmap;I)V");
	env->CallStaticVoidMethod(GLUtils, texImage2D, GL_TEXTURE_2D, 0, bitmap2,
			0);

	// bitmap.recycle();
	// if(bitmap2!=bitmap) bitmap.recyle();
	jmethodID recycle = env->GetMethodID(Bitmap, "recycle", "()V");
	env->CallVoidMethod(bitmap, recycle);
	if (bitmap2 != bitmap)
		env->CallVoidMethod(bitmap2, recycle);
}

Texture::Texture(std::string& fileName) {
	unsigned char* data = NULL;
	init();
	PNG* png = new PNG(fileName);
	widthS = png->get_width();
	heightS = png->get_height();

	widthD = get2(widthS);
	heightD = get2(heightS);

	glBindTexture(GL_TEXTURE_2D, id);
	// Set filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (widthS == widthD && heightS == heightD) {
		data = png->get_data();
	}else
		data = do_Stretch_Linear(widthD, heightD, 32, png->get_data(), widthS, heightS);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthD,
					heightD, 0, GL_RGBA, GL_UNSIGNED_BYTE,
					data);

	if(data != png->get_data())
		delete[] data;
	delete png;
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
	id = 0;
}
}

