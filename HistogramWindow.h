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

#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include "qpushbutton.h"
#include "iostream"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "QHistogramWidget.h"
#include "conhistogram.h"
//#include "handtracking.h"
//#include "ConContour.h"


class HistogramWindow : public QWidget
{
    Q_OBJECT
    private:
        QHistogramWidget *widgetHistogram;

        ConHistogram *histogram;
      //  QPushButton  buttonStart;
       // HandTracking *tracking;
      //  ConContour *contour;
        IplImage *img;
        //IplImage *src;

        int set;
        
    public:

        HistogramWindow(QWidget *parent=0);

       // void setQWidget(QWidget *parent);

        void setSet(int s);
        void setImage(IplImage *image);
         
    protected:
        void timerEvent(QTimerEvent*);
};


#endif /*MYCAMERAWINDOW_H_*/
