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
#ifndef HANDTRACKING_H
#define HANDTRACKING_H

#include "iostream"
#include "math.h"
#include "cv.h"
#include "cvaux.h"
#include "highgui.h"
#include "X11/Xlib.h"
#include "X11/extensions/XTest.h"

#include "Image.h"
using namespace std;

using namespace cv;

class HandTracking {

private:

	Display *dpy;



	// Where to start the search from
	int searchx;
	int searchy;


	CvPoint p0;
	CvPoint p1;

	// What state is the mouse in now


	//IplImage *currentFrame;

	int stateX;
	int stateY;
	int konX;
	int konY;

	int countx;
	int county;

	int state;

	int redx;
	int redy;
	int starth;

public:

	HandTracking();
	~HandTracking();

        void setDefault();

	void setState(int state);

	void setP0(CvPoint point);

	void setP1(CvPoint point);

	// in case I want to add mouse handling to the window later
	void on_mouse(int event, int x, int y, int flags, void* param);

	// Fill in the red region and identify its center of gravity
	void trackPoint(Display *dpy);

	void play();

	void getResult();



};

#endif // HANDTRACKING_H
