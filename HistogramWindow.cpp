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
#include "HistogramWindow.h"

HistogramWindow::HistogramWindow(QWidget *parent) : QWidget(parent) {
    //camera = cam;
    QVBoxLayout *layout = new QVBoxLayout;
    widgetHistogram= new QHistogramWidget(this);

   // contour = new ConContour();


    layout->addWidget(widgetHistogram);
    setLayout(layout);
    resize(320, 200);
    histogram = new ConHistogram();

    startTimer(100);  // 0.1-second timer
 }


void HistogramWindow::setSet(int s){
    this->set = s;
}

void HistogramWindow::setImage(IplImage *image){
    this->img= image;
}

void HistogramWindow::timerEvent(QTimerEvent*) {
    //IplImage *image=cvQueryFrame(camera);
if(img != 0){
    //cvCopy(img,src);
   if(set==1){

       histogram->setFrame(img);
       histogram->progressImage();

        widgetHistogram->putImage(histogram->getHistimg());

        std::cout<<"in == 1"<<endl;
        //widgetHistogram->putImage(img);
   }

}


   // image = tracking->getImage();


}

