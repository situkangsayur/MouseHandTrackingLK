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
#ifndef YCRCBSKINDETECTOR_H
#define YCRCBSKINDETECTOR_H

#include "cv.h"
#include "cvaux.h"
#include "highgui.h"
//#include "image.h"
#include  "IColorSkinDetector.h"

using namespace std;
//using namespace cv;

class YCrCbSkindetector: public IColorSkinDetector {
public:
	IplImage *currentYCrCbFrame;
	IplImage *skin;

	IplConvKernel *rect_12;
	IplConvKernel *rect_6;

public:

	YCrCbSkindetector() {
		currentYCrCbFrame = 0;
		skin = 0;

		rect_12 = 0;

		rect_6 = 0;
	}

	IplImage *detectSkin(IplImage *img, CvScalar min, CvScalar max) {

		if (currentYCrCbFrame == 0) {
			currentYCrCbFrame = cvCreateImage(cvGetSize(img), img->depth, 3);
		}
		if (skin == 0) {
			skin = cvCreateImage(cvGetSize(img), img->depth, 1);
		}

		cvCvtColor(img, currentYCrCbFrame, CV_BGR2YCrCb);

		cvInRangeS(currentYCrCbFrame, min, max, skin);
		//			/cvXorS( skin, cvScalarAll(255), skin, 0 );
		//for(int i=0;i<skin->)


		//		Size size12(12,6);

		if (rect_12 == 0) {
			rect_12 = cvCreateStructuringElementEx(12, 12, 6, 6, CV_SHAPE_RECT);
		}
		cvErode(skin, skin, rect_12, 1);

		//Size size6(6,3);

		if (rect_6 == 0) {
			rect_6 = cvCreateStructuringElementEx(6, 6, 3, 3, CV_SHAPE_RECT);
		}

		cvDilate(skin, skin, rect_6, 2);

		return skin;
	}
};
#endif
