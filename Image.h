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
#ifndef IMAGE_H
#define IMAGE_H

#include "cv.h"
#include <stdio.h>
#include <ctype.h>


template<class T> class Image {

private:
	IplImage *imgp;

public:
	Image(IplImage *img = 0) {
		imgp = img;
	}
	~Image() {
		imgp = 0;
	}
	void operator=(IplImage *img) {
		imgp = img;
	}
	inline T* operator[](const int rowIndex) {
		return ((T*) (imgp->imageData + rowIndex * imgp->widthStep));
	}
};

typedef struct {
	unsigned char b, g, r;
} RgbPixel;
typedef struct {
	float b, g, r;
} RgbPixelFloat;

typedef struct {
	float Cr, Y, Cb;
} YCrCbPixel;

typedef struct {
	float H;
} GrayPixel;

typedef Image<RgbPixel> RgbImage;
typedef Image<YCrCbPixel> YcrCbImage;
typedef Image<GrayPixel> GrayImage;

#endif
