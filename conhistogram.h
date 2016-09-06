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
#ifndef CONHISTOGRAM_H
#define CONHISTOGRAM_H

#include "iostream"
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

using namespace std;

class ConHistogram {
public:
	IplImage *frame;
	IplImage *singleFrame;
	IplImage *histimg;

	CvHistogram *hist;

	int hdims;
	float hranges_arr[2];
	float* hranges;
	int bin_w;
	float max_val;
	int i;
	double val;
	CvScalar color;

public:
	ConHistogram();
	~ConHistogram();

	//accessor
	IplImage *getFrame();

	CvHistogram *getHist();

	IplImage *getHistimg();

	IplImage *getSingleFrame();

	void setFrame(IplImage *frame);

	void setHist(CvHistogram *hist);

	void setHistimg(IplImage *histimg);

	void setSingleFrame(IplImage *singleFrame);

public:
	//main methode
	void progressImage();

	void drawHistogram();

};

#endif

