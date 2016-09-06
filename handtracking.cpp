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
#include "handtracking.h"

using namespace std;

void HandTracking::setP0(CvPoint point) {
	p0 = point;

}
void HandTracking::setP1(CvPoint point) {
	p1 = point;
}

HandTracking::HandTracking() {
	dpy = XOpenDisplay(0);

	searchx = -1;
	searchy = -1;

	// How big to make the starting region


	// How big the last starting region was

        state = 5;
        countx = 1;
	county = 1;
	stateX = 0;
	stateY = 0;
	konX = 0;
	konY = 0;
}

HandTracking::~HandTracking() {
	XTestFakeButtonEvent(dpy, 1, 0, 0);
	XTestFakeButtonEvent(dpy, 2, 0, 0);
	XTestFakeButtonEvent(dpy, 3, 0, 0);
	XFlush(dpy);
}

void HandTracking::setDefault(){
    XTestFakeButtonEvent(dpy, 1, 0, 0);
    XTestFakeButtonEvent(dpy, 2, 0, 0);
    XTestFakeButtonEvent(dpy, 3, 0, 0);
    XFlush(dpy);
}

void HandTracking::trackPoint(Display *dpy) {


        redx = ((p1.x / (640 / 100)) * (1550 / 100));
        redy = ((p1.y / (480 / 100)) * (890 / 100));

	if (redx < searchx) {
		//	countx = searchx - redx;
		redx -= countx;
		stateX = 0;
	} else {
		//	county = redx - searchx;
		//	redx += countx;
		stateX = 1;
	}

	if (redy < searchy) {

		//	county = searchy - redy;
		redy -= county;
		stateY = 0;

	} else {

		stateY = 1;
	}

	if (countx <= 10) {
		countx++;
	}
	if (county <= 10) {
		county++;
	}

	cout << redx << "&" << redy << countx << endl;
	//int screenx = (int) ((redx * 11366.0) - 100);
	//int screeny = (int) ((redy * 1768.0) - 100);

	// move the mouse to the red region's center of gravity
	XTestFakeMotionEvent(dpy, DefaultScreen (dpy), redx, redy, 0);

	if ((redx <= 0) || (konX != stateX)) {
		countx = 1;
	}
	if ((redy <= 0) || (konY != stateY)) {
		county = 1;
	}

	konX = stateX;
	konY = stateY;

	searchx = redx;
	searchy = redy;

        if (state == 0 || state == 1) {
		XTestFakeButtonEvent(dpy, 1, 1, 0);
	}

	if (state == 3) {
                        XTestFakeButtonEvent(dpy, 2, 1, 0);
	}

	if (state >= 4) {
		XTestFakeButtonEvent(dpy, 1, 0, 0);
		XTestFakeButtonEvent(dpy, 2, 0, 0);
		XTestFakeButtonEvent(dpy, 3, 0, 0);
	}

        if (state == 2) {
		XTestFakeButtonEvent(dpy, 3, 1, 0);
		//XTestFakeButtonEvent(dpy, 3, 0, 0);
	}


	XFlush(dpy);

}


void HandTracking::getResult() {

	trackPoint(dpy);


}
void HandTracking::setState(int state) {
	this->state = state;
}
