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
#include "ConContour.h"

using namespace std;

int ConContour::getFingerNum() {
        return fingerNum;
}

CvPoint ConContour::getP0() {
        return p0;
}
CvPoint ConContour::getp1() {
        return p1;
}

IplImage *ConContour::getImg() {
        return img;
}

IplImage *ConContour::getSkin() {
        return skin;
}

/*
CvCapture *ConContour::getGrabber() {
        return grabber;
}
*/

IplImage *ConContour::getCurrentFrame() {
        return currentFrame;
}

void ConContour::setCurrentFrame(IplImage *image) {
        currentFrame = image;
}

void ConContour::checkGStorage(int i) {

        if (gStorage == NULL) {
                gStorage = cvCreateMemStorage(0);
        } else {
                cvClearMemStorage(gStorage);
        }

}

ConContour::~ConContour() {
        //bersih2
        //cvReleaseCapture(&grabber);
        cvReleaseImage(&tempImage);
        //cvReleasesImage(&currentContour);
        cvReleaseImage(&currentFrame);
        //cvReleaseImage(&currentFrameCopy);
        cvReleaseImage(&skinTemp);
        cvReleaseImage(&img);
        cvReleaseImage(&tempImage);
        cvReleaseImage(&pyrdA);
        cvReleaseImage(&pyrdB);
        //cvReleaseCapture(&grabber);
        //cvRelease(//ull);
        //cvRelease(&filtereHull);
        //cvRelease(&biggestContour);
        //cvRelease(&defect);

}

ConContour::ConContour() {

        //inisialisasi


        tempImage = 0;
        currentFrame = 0;
        //currentFrameCopy = 0;
        skinDetection = new YCrCbSkindetector();
        img = 0;
        skin = 0;
        skinTemp = 0;
        //for lucas kanade========
        pyrdA = 0;
        pyrdB = 0;
        //img_sz = 0;
        eig_image = 0;
        tmp_image = 0;

        cornersA = new CvPoint2D32f[MAX_CORNERS];

        //pyr_sz = 0;
        tempPyrA = 0;
        tempPyrB = 0;
        cornersB = 0;

        win_size = 10;

        cornersB = new CvPoint2D32f[MAX_CORNERS];

        //end for lucas kanade


        //for mouse
        fingerNum = 0;



        hull = NULL;

        filtereHull = NULL;

        defect = NULL;

        //CvBox2D box=NULL;

        biggestContour = NULL;
/*
        grabber = cvCaptureFromCAM(1);
        //grabber = cvCaptureFromFile("M2U00253.MPG");

        if (!grabber) {
                grabber = cvCaptureFromCAM(0);
                //cout << "hhheeeaarrrr...\n";

        }

        //	cout << "set capture...\n";

        if (!grabber) {
                cout << "Could not initialize capturing...\n";
                return;
        }
        */
        //inisialisasi storage
        gStorage = NULL;

        //cvNamedWindow("windows", 1);
        //cvNamedWindow("result", 1);

        //cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
        //cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);

        frameWidth = 320;
        frameHeight = 240;
        //nilai warna kulit
        yccMin = cvScalar(0, 131, 80);
        yccMax = cvScalar(245, 185, 135);

        hsvMin = cvScalar(0, 30, 80, 0);
        hsvMax = cvScalar(20, 150, 255, 0);
        //skin detector , but unused
        //adaptiveSkinDetector = new CvAdaptiveSkinDetector(1,CvAdaptiveSkinDetector::MORPHING_METHOD_ERODE_DILATE);

}

void ConContour::frameGrabber() {
        //grabber, mengambil query frame
        //currentFrame = cvQueryFrame(grabber);

        if (!currentFrame) {
                return;
        }

        cvFlip(currentFrame, 0, 1);
        //persiapan image untuk pyramidal lucas kanade

        if ((pyrdA == 0) && (pyrdB == 0)) {
                pyrdA = cvCreateImage(
                                cvSize(currentFrame->width, currentFrame->height),
                                currentFrame->depth, 1);
                pyrdB = cvCreateImage(
                                cvSize(currentFrame->width, currentFrame->height),
                                currentFrame->depth, 1);
                img = cvCreateImage(cvSize(currentFrame->width, currentFrame->height),
                                currentFrame->depth, currentFrame->nChannels);
                tempImage = cvCreateImage(
                                cvSize(currentFrame->width, currentFrame->height),
                                currentFrame->depth, currentFrame->nChannels);
        }

        //copy frame sementara
        /*
         if (currentFrameCopy == 0) {
         currentFrameCopy = cvCreateImage(
         cvSize(currentFrame->width, currentFrame->height),
         currentFrame->depth, currentFrame->nChannels);
         }
         */

        //copy frame utama ke temporary frame
        //	cvCopyImage(currentFrame, currentFrameCopy);

        //image untuk menyimpan kontur image skin
        if (skin == 0) {
                skin = cvCreateImage(cvSize(currentFrame->width, currentFrame->height),
                                currentFrame->depth, 1);

        }

        //tempat penyimpanan sementara kontur, hasil threshold

        if (skinTemp == 0) {
                skinTemp = cvCreateImage(
                                cvSize(currentFrame->width, currentFrame->height),
                                currentFrame->depth, 1);

        }

        //pendeteksi warna kulit dengan warna YCrCb

        try {
                //adaptiveSkinDetector->process(currentFrameCopy,skinTemp);
                skin = skinDetection->detectSkin(currentFrame, yccMin, yccMax);
                cvCopy(skin, skinTemp);

                //mengambil kontur dari edge skin yang didapat

                extractContourAndHull(skinTemp);

                //konversi gambar titik tengah dari img ke pyrdA "grayscale"
                cvCvtColor(img, pyrdA, CV_BGR2GRAY);

                //menggambar kontur convexity defects dan menghitung jumlah jari

                drawAndComputeFingerNum();

                //pencarian pergerakan tangan dengan lucas kanade

                lukas_canade();

                //ambil lokasi sebelumnya dari titik tengah tangan manusia..
                cvCopy(pyrdA, pyrdB);

                // menghapus gambar img menjadi hitam kembali
                cvCopy(tempImage, img);
                //	return skin;
        } catch (cv::Exception e) {
                cout << e.msg << endl;
        }

        //free(&defectArray);
        //return currentFrame;
}

void ConContour::extractContourAndHull(IplImage *skin) {
        //inisialisasi storage

        checkGStorage(1);
        checkGStorage(2);
        checkGStorage(3);
        checkGStorage(4);
        checkGStorage(5);

        int v;
        contour = NULL;

        //mencari contour dari kulit
        v = cvFindContours(skin, gStorage, &contour, sizeof(CvContour),
                        CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

        //variabel penyimpan kontur terbesar
        biggestContour = NULL;

        double result1 = 0;
        double result2 = 0;
        //mencari kontur terbesar
        while (contour != NULL) {

                result1 = contour->total;

                if (result1 > result2) {
                        result2 = result1;
                        biggestContour = contour;

                }
                contour = contour->h_next;

        }

        //menggambar kontur dengan melakukan approxypoly untuk mengambil gambar kontur yang didapat
        if (biggestContour != NULL) {

                //cvDrawContours(currentFrame, biggestContour, cvScalarAll(255),cvScalarAll(255), 100);

                currentContour = NULL;
                try {
                        //checkGStorage(1);
                        biggestContour = cvApproxPoly(biggestContour, sizeof(CvContour),
                                        gStorage, CV_POLY_APPROX_DP,
                                        biggestContour->total * 0.0025, 0);

                        //	cout << "past approxymaly\n";


                        cvDrawContours(currentFrame, biggestContour, cvScalar(89, 123, 90),
                                        cvScalar(0, 0, 0), 0, 2, 8);

                        //biggestContour = currentContour;

                        //cvConvexHull()
                        hull = cvConvexHull2(biggestContour, gStorage, CV_CLOCKWISE, 0);
                } catch (Exception e) {
                        cout << e.msg << endl;
                }

                box = cvMinAreaRect2(biggestContour, gStorage);

                //cout << "get the box from the contour pasted.. \n";

                //box = &tempBox;
                //box = tempBox;

                int startX = box.center.x - (box.size.width / 2);
                int startY = box.center.y - (box.size.height / 2);

                int row = startY + box.size.height;
                int col = startX + box.size.width;

                CvPoint2D32f points[row * col];
                int ret = 0;

                for (int i = startY; i < row; i++) {
                        for (int j = startX; j < col; j++) {

                                points[ret].x = i;
                                points[ret].y = j;
                                ret++;
                        }
                }

                //points= box;5

                //handRect = cvMinAreaRect2();

                //cvDraw(currentFrame);
                /*
                 for()

                 CvPoint *ps[] = new CvPoint[ARRAY_LEN(point2)];
                 for (int i = 0; i < ARRAY_LEN(point2); i++)
                 ps[i] = cvPoint(points[i].x, points[i].y);
                 */
                /*
                 int countHull = hull->total;
                 arrHull = (CvPoint*) malloc(sizeof(CvPoint) * countHull);

                 //CvMat hMatrix = cvMat(1, countHull, CV_32SC2, arrHull);

                 for (int i = 0; i < countHull; i++) {
                 arrHull[i] = **CV_GET_SEQ_ELEM( CvPoint*, hull, i );
                 }
                 */

                /*
                 int hullArea=0;
                 for(int x=0;x<convexHullImage->width;x++){
                 for(int y=0;y<convexHullImage->height;y++){
                 if(cvPointPolygonTest(&hMatrix, cvPoint2D32f(x, y), 0)>0){
                 hullArea++;
                 }
                 }
                 }
                 */

                //cout << "set array from hull .. \n";
                /*
                 try {
                 cvCvtSeqToArray(hull, arrHull, CV_WHOLE_SEQ);
                 cout << "past set array from hull .. \n";
                 } catch (cv::Exception e) {
                 cout << e.msg << "cvCvtSeqToArray(hull, arrHull, CV_WHOLE_SEQ);"
                 << endl;
                 }
                 */

                int n = 1;
                //draw hull *belum berhasil :D
                /*
                 try {

                 for(int i = 0 ; i<count ; i++){
                 cout << "check loop.. \n";
                 *arrPoint[i] = arrHull[i];
                 }


                 //	cvPolyLine(currentFrame, &arrHull, &n, countHull, 1,CV_RGB(0, 255, 0), 1, 1,0);
                 } catch (cv::Exception e) {
                 cout << e.msg
                 << "cvPolyLine(currentFrame, arrHull, n, hull->total, true,"
                 << endl;
                 }
                 */
                //menggambar titik tengah


                cvCircle(currentFrame, cvPoint(box.center.x, box.center.y), 15,
                                CV_RGB(255, 0, 0), 5, 1, 0);
                //	box.center.y+=100;
                cvCircle(img, cvPoint(box.center.x, box.center.y), 1,
                                CV_RGB(255, 0, 0), 2, 1, 0);

                //float radius;
                /*
                 try {
                 filtereHull = cvCreateSeq(CV_SEQ_FLAG_CLOSED, sizeof(filtereHull),
                 sizeof(CvPoint), gStorageHull);
                 } catch (cv::Exception e) {
                 cout << e.msg
                 << "filtereHull = cvCreateSeq(CV_SEQ_FLAG_CLOSED, sizeof(filtereHull),"
                 << endl;
                 }
                 */

                //	setPoint = (CvPoint*) cvGetSeqElem(hull,0);

                //cout<<setPoint->x<<" & "<<setPoint->y<<endl;
                /*
                 for (int i = 0; i < hull->total; i++) {

                 if (sqrt(
                 pow(arrHull[i].x - arrHull[i + 1].x, 2) + pow(
                 arrHull[i].y - arrHull[i + 1].y, 2))
                 > (box.size.width / 10)) {

                 CvPoint setPoint;

                 try {
                 setPoint = cvPoint(arrHull[i].x, arrHull[i].y);
                 } catch (cv::Exception e) {
                 cout << e.msg
                 << "setPoint in for loop contour, to get arrhull"
                 << endl;
                 }

                 try {
                 cvSeqPush(filtereHull, &setPoint);
                 } catch (cv::Exception e) {
                 cout << e.msg << " cvseqpush in contour... " << endl;
                 }

                 }
                 }
                 */

                try {

                        defect = cvConvexityDefects(biggestContour, hull, gStorage);

                        int defnum = defect->total;

                        defectArray = (CvConvexityDefect*) malloc(
                                        sizeof(CvConvexityDefect) * defnum);

                        cvCvtSeqToArray(defect, defectArray, CV_WHOLE_SEQ);
                } catch (cv::Exception e) {
                        cout << e.msg << endl;
                }

        }
        //free(&points[]);
        //free(arrHull);
        //free(arrHull);


}

void ConContour::drawAndComputeFingerNum() {
        fingerNum = 0;
        //cout << "getin to draw and compute finger...\n";

        //menggambar daerah hull
        /*
         for (int i = 0; i < filtereHull->total; i++) {
         arrHull[i] = cvPoint(arrHull[i].x, arrHull[i].y);
         //circleFrame.Draw(hullCircle, new Bgr(Color.Aquamarine),2);
         // cvCircle(currentFrame, hullPoint, 5, cvScalar(0, 220, 180), 1);

         }

         int n = 1;
         cvPolyLine(currentFrame, &arrHull, &n, filtereHull->total, 1,
         CV_RGB(0, 255, 0), 1, 1, 0);
         */
        //cout << sizeof(defectArray) << " " << sizeof(CvConvexityDefect) << endl;
        //if (defect->total > 0) {

        //gambar convexityDefects :D/

        for (int i = 0; i < defect->total; i++) {

                try {
                        startPoint = cvPoint(defectArray[i].start->x,
                                        defectArray[i].start->y);
                        //cout << "get point\n";

                        //cout << "try get depth point \n";


                        depthPoint = cvPoint(defectArray[i].depth_point->x,
                                        defectArray[i].depth_point->y);

                        //cout << "get depth point \n";


                        endPoint = cvPoint(defectArray[i].end->x, defectArray[i].end->y);
                        //cout << "get end point \n";
                } catch (cv::Exception e) {
                        cout << e.msg << "endpoint from cvpoint contour" << endl;
                }

                if (((startPoint.y < box.center.y) || (depthPoint.y < box.center.y))
                                && (startPoint.y < depthPoint.y) && (sqrt(
                                pow(startPoint.x - depthPoint.x, 2) + pow(
                                                startPoint.y - depthPoint.y, 2)) > box.size.height
                                / 6.0)) {
                        fingerNum++;
                         cvLine(currentFrame, startPoint, depthPoint, CV_RGB(200,10,0), 2);
                       //cvLine(currentFrame, depthPoint, endPoint, CV_RGB(255,0,0), 5);
                        //	cout << "get line point \n";
                }

                cvCircle(currentFrame, startPoint, 2, CV_RGB(0,178,211), 5);
                //cout << "get circle point \n";

                cvCircle(currentFrame, depthPoint, 3, CV_RGB(0,255,0), 5);
                //	cout << "get circle point \n";


                //cvCircle(currentFrame, endPoint, 3, CV_RGB(0,0,255), 5);
                //	cout << "get circle point \n";


        }

        cout << "show number" << fingerNum << endl;

        sprintf(&number, "%i", fingerNum);

        //number = "hello";
        cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 5.0, 5.0, 0, 5.0, 4);
        cvPutText(currentFrame, &number, cvPoint(50, 150), &font,
                        cvScalar(255, 0, 0));

}

void ConContour::lukas_canade() {
        // Initialize, load two images from the file system, and
        // allocate the images and other structures we will need for
        // results.
        //
        // Initialize, load two images from the file system, and
        // allocate the images and other structures we will need for
        // results.
        //cvLoadImage("OpticalFlow0.jpg",CV_LOAD_IMAGE_GRAYSCALE)
        //cvLoadImage("OpticalFlow1.jpg",CV_LOAD_IMAGE_GRAYSCALE)

        //	IplImage* imgA = imageA;
        //IplImage* imgB = imageB;

        //if (img_sz == NULL) {

        //}

        /*
         *
         * win_size = 10;
         */

        //IplImage* imgC = imageC;

        // The first thing we need to do is get the features
        // we want to track.
        if (eig_image == 0) {
                img_sz = cvGetSize(pyrdA);
                eig_image = cvCreateImage(img_sz, IPL_DEPTH_32F, 1);
        }

        if (tmp_image == 0) {
                tmp_image = cvCreateImage(img_sz, IPL_DEPTH_32F, 1);
                pyr_sz = cvSize(pyrdA->width + 8, pyrdB->height / 3);
        }

        int corner_count = MAX_CORNERS;

        cvGoodFeaturesToTrack(pyrdA, eig_image, tmp_image, cornersA, &corner_count,
                        0.01, 5.0, 0, 3, 0, 0.04);
        cvFindCornerSubPix(pyrdB, cornersA, corner_count,
                        cvSize(win_size, win_size), cvSize(-1, -1),
                        cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
        // Call the Lucas Kanade algorithm
        //


        if (tempPyrA == 0) {
                tempPyrA = cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
        }
        if (tempPyrB == 0) {
                tempPyrB = cvCreateImage(pyr_sz, IPL_DEPTH_32F, 1);
        }

        cvCalcOpticalFlowPyrLK(pyrdA, pyrdB, tempPyrA, tempPyrB, cornersA,
                        cornersB, corner_count, cvSize(win_size, win_size), 5,
                        features_found, feature_errors,
                        cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3), 0);
        // Now make some image of what we are looking at:
        //
        for (int i = 0; i < corner_count; i++) {
                if (features_found[i] == 0 || feature_errors[i] > 550) {
                        //       printf("Error is %f/n",feature_errors[i]);
                        continue;
                }
                //    printf("Got it/n");
                p0 = cvPoint(cvRound(cornersA[i].x), cvRound(cornersA[i].y));
                p1 = cvPoint(cvRound(cornersB[i].x), cvRound(cornersB[i].y));
                cvLine(currentFrame, p0, p1, CV_RGB(101,56,255), 3);
        }

        /*free(&img_sz);
         //free(&cornersA);
         //free(&cornersB);
         //free(&pyr_sz);

         free(&img_sz);
         free(&cornersA);
         free(&cornersB);
         free(&pyr_sz);
         //		cvWaitKey(0);
         //	return 0;
         * */

}
