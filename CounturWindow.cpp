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
#include "CounturWindow.h"

CounturWindow::CounturWindow(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout;
    widgetCountur= new QCounturWidget(this);

    layout->addWidget(widgetCountur);
    setLayout(layout);
    resize(640, 480);
    image=0;

    startTimer(100);  // 0.1-second timer
 }

CounturWindow::~CounturWindow(){
    delete widgetCountur;
    delete image;
}


void CounturWindow::setImage(IplImage *image){
    this->image = image;
}

void CounturWindow::setSet(int s){
    this->set = s;
}

void CounturWindow::timerEvent(QTimerEvent*) {

 if(image != 0){
   if(set==1){
       widgetCountur->putImage(image);
   }else{
       widgetCountur->putImage(image);
   }
 }
}

