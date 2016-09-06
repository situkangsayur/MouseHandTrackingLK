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
#ifndef SISTEMMODEL_H
#define SISTEMMODEL_H

#include "iostream"
#include "listener.h"
#include "cv.h"
//#include "handtracking.h"

class SistemModel
{
private :

    int ptX;
    int ptY;
    CvPoint point;
    listener *listen;
    IplImage *image;
    IplImage *countur;

    int state;


public:
    SistemModel();

    void setPtX(int ptX);
    void setPtY(int ptY);

    int getPtX();
    int getPtY();
    void setImage(IplImage *image);
    void setCountur(IplImage *countur);

    void setPoint(CvPoint points);
    CvPoint getPoint();

    void setState(int state);
    int getState();

    void setListener(listener *list);

   void doHandTracking();
   void doStopHandTracking();

   void getHistogram();

   void getContour();

   void setSingkronisasiMouse();

   void singkronisasiHis();

   void loadCountur();

   void tampilPetunjuk();

   //void doTracking();

 protected :
     void fireOnStart();
     void fireOnStop();
     void fireOnHistogram();
     void fireOnContour();
     void fireOnSingkronisasi();
     void fireOnTracking();
     void fireOnLoadCountur();
     void fireOnPetunjuk();
};

#endif // SISTEMMODEL_H
