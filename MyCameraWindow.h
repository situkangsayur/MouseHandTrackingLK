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
#ifndef MYCAMERAWINDOW_H_
#define MYCAMERAWINDOW_H_

//#include "qmetatype.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QOpenCVWidget.h>
#include "iostream"
#include "cv.h"
#include "highgui.h"
#include "ConContour.h"
#include "sistemmodel.h"
#include <stdlib.h>

//#include "handtracking.h"



class MyCameraWindow : public QWidget
{
    Q_OBJECT
    private:
        QOpenCVWidget *cvwidget;
        CvCapture *camera;

        IplImage *image;
        IplImage *black;
        IplImage *gray;



        ConContour *cont;
       // HandTracking *tracking;
        SistemModel *model;

        int state;
        int histogram;
        int countur;
        
    public:
        MyCameraWindow( QWidget *parent=0);

        void setModel(SistemModel *model);
        void setState(int state);
        void setHistogram(int histogram);
        void setContour(int conrtour);
        int getState();
        int getHistogram();
        int getContour();
         
    protected:
        void timerEvent(QTimerEvent*);



};


#endif /*MYCAMERAWINDOW_H_*/
