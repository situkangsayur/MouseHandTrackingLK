/**
 * MouseHandTracking is an application to control mouse pointer of the computer with hand gesture via camera
 * Copyright (C) 2011  Hendri Karisma
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * contact author at situkangsayur[at]gmail[dot]com
 */
#ifndef  CONCONTOUR_H
#define CONCONTOUR_H

#include <cv.h>
#include <highgui.h>
#include "Image.h"
#include <cxcore.h>
//#include "math.h"
#include <iostream>
#include <cvaux.h>
#include <stdio.h>
#include <cmath>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "IColorSkinDetector.h"
//#include "CustomYCrCbSkin.h"
#include "YCrCbSkinDetector.h"
//#include "HsvSkinDetector.h"
#include "Image.h"

using namespace std;
//using namespace cv;

const int MAX_CORNERS = 500;

class ConContour {

private:
	IColorSkinDetector *skinDetection;
	IplImage *img;
	IplImage *currentFrame;
	IplImage *tempImage;
	//IplImage *currentFrameCopy;
	IplImage *skinTemp;

	IplImage *skin;
	//lucas kanade
	IplImage *pyrdA;
	IplImage *pyrdB;
	IplImage *eig_image;
	IplImage *tmp_image;
	CvPoint2D32f *cornersA;

	CvSize img_sz;

	CvSize pyr_sz;
	IplImage *tempPyrA;
	IplImage *tempPyrB;
	CvPoint2D32f *cornersB;

	int win_size;

	char features_found[MAX_CORNERS];
	float feature_errors[MAX_CORNERS];
	//end object for lucas kanade

	//VideoCapture frame;
        //CvCapture *grabber;

	//	CvAdaptiveSkinDetector *adaptiveSkinDetector;

	int frameWidth;
	int frameHeight;

	CvScalar hsvMin;
	CvScalar hsvMax;

	CvScalar yccMin;
	CvScalar yccMax;

	CvSeq *hull;

	CvSeq *filtereHull;

	CvSeq *defect;
	//CvPoint **arrPoint;
	CvPoint *arrHull;
	CvConvexityDefect *defectArray;
	CvRect *handRect;

	CvBox2D box;

	CvFont font;

	char number;

	CvMemStorage *gStorage;

	CvSeq *biggestContour;

	CvSeq *currentContour;
	CvSeq *contour;

	//===========================================
	CvPoint startPoint;
	CvPoint depthPoint;
	CvPoint endPoint;

	CvPoint *setPoint;

	int fingerNum;

	CvPoint p0;
	CvPoint p1;
	//CvPoint *setPoint;

private:
	void drawAndComputeFingerNum();
	void checkGStorage(int i);

public:
	ConContour();
	~ConContour();

	//void getYCrCb(IplImage *temp, int x, int y, int z);

	void lukas_canade();

	void frameGrabber();

	void extractContourAndHull(IplImage *skin);

	IplImage *getCurrentFrame();

	void setCurrentFrame(IplImage *image);


        //CvCapture *getGrabber();

	IplImage *getSkin();
	IplImage *getImg();
	int getFingerNum();
	CvPoint getP0();
	CvPoint getp1();
	//void clean();
};

#endif
