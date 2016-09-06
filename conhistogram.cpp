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
#include "conhistogram.h"

ConHistogram::ConHistogram() {

	frame = 0;
	singleFrame = 0;
	histimg = cvCreateImage(cvSize(320, 200), 8, 3);
	singleFrame = 0;

	//for draw histogram :
	hist = 0;

	hdims = 50;
	hranges_arr[0] = 0;
	hranges_arr[1] = 255;
	hranges = hranges_arr;
	bin_w = 0;
	//float max_val;
			i = 0;

			hist = cvCreateHist(1, &hdims, CV_HIST_ARRAY, &hranges, 1);

			color = CV_RGB(101,255,0);

		}

ConHistogram::~ConHistogram() {

}

IplImage *ConHistogram::getFrame() {
	return frame;
}

CvHistogram *ConHistogram::getHist() {
	return hist;
}

IplImage *ConHistogram::getHistimg() {
	return histimg;
}

IplImage *ConHistogram::getSingleFrame() {
	return singleFrame;
}

void ConHistogram::setFrame(IplImage *frame) {
	this->frame = frame;
}

void ConHistogram::setHist(CvHistogram *hist) {
	this->hist = hist;
}

void ConHistogram::setHistimg(IplImage *histimg) {
	this->histimg = histimg;
}

void ConHistogram::setSingleFrame(IplImage *singleFrame) {
	this->singleFrame = singleFrame;
}

void ConHistogram::progressImage() {
	//cvShowImage("window", frame);
	if(singleFrame == 0){
		singleFrame=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
	}
	cvCvtColor(frame, frame, CV_RGB2HSV);
	cvSplit(frame, singleFrame, NULL, NULL, NULL);
	drawHistogram();

}

void ConHistogram::drawHistogram() {
	//CvHistogram *hist = 0;

	//hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );

	cvZero(histimg);
	//cvCloneMatND()
	cvCalcHist(&singleFrame, hist, 0, 0);
	cvGetMinMaxHistValue(hist, 0, &max_val, 0, 0);

	cvConvertScale(hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0);
	//cvZero(histimg);
	bin_w = histimg->width / hdims;


	for (i = 0; i < hdims; i++) {
		val = (cvGetReal1D(hist->bins, i) * (histimg->height - 5) / 255);
		//(hsv2rgb(i*180.f/hdims);
		cvRectangle(histimg, cvPoint(i * bin_w, histimg->height),
				cvPoint((i + 1) * bin_w, (int) (histimg->height - val)), color,
				1, 8, 0);
		//cout<<i<<endl;
	}
	cout << hdims << endl;
}

