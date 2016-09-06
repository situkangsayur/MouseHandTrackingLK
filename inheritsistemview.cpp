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

#include "inheritsistemview.h"

InheritSistemView::InheritSistemView(QWidget *parent) :
    QWidget(parent)
{
    setupUi(parent);

    model = new SistemModel();
    controll = new SistemControll();

    model->setListener(this);
    controll->setModel(model);

    tracking = new HandTracking();



    widgetOpenCV->setModel(model);

    hist = 0;
    cou = 0;
     connect(buttonStart,SIGNAL(clicked()),this,SLOT(on_buttonStart_clicked()));
     connect(buttonStop,SIGNAL(clicked()),this,SLOT(on_buttonStop_clicked()));
     connect(buttonHistogram,SIGNAL(clicked()),this,SLOT(on_buttonHistogram_clicked()));
     connect(buttonContour,SIGNAL(clicked()),this,SLOT(on_buttonContour_clicked()));
     connect(buttonExit,SIGNAL(clicked()),this,SLOT(on_buttonExit_clicked()));
     connect(buttonPetunjuk,SIGNAL(clicked()),this,SLOT(on_buttonPetunjuk_clicked()));

     histogram = new DialogHistogram();
     histogram->hide();

     countur = new DialogContour();
     countur->hide();

     help = new DialogHelp();
     help->hide();

}

InheritSistemView::~InheritSistemView(){
    tracking->~HandTracking();
    histogram->~DialogHistogram();
    delete this;
}


void InheritSistemView::on_buttonStart_clicked(){
    cout<<"button start"<<endl;
    controll->startTracking();

}

void InheritSistemView::on_buttonStop_clicked(){

    controll->stopTracking();

}

void InheritSistemView::on_buttonHistogram_clicked(){

    controll->startHistogram();
}

void InheritSistemView::on_buttonContour_clicked(){

    controll->startContour();
}

void InheritSistemView::on_buttonExit_clicked(){
    cout<<"button Stop"<<endl;
        this->~InheritSistemView();
}

void InheritSistemView::on_buttonPetunjuk_clicked(){
        controll->showPetunjuk();
}

void InheritSistemView::onStart(){
    cout<<"onStart "<<endl;

    widgetOpenCV->setState(1);

}

void InheritSistemView::onStop(){
    cout<<"onStop "<<endl;
    widgetOpenCV->setState(0);
    tracking->setDefault();
}

void InheritSistemView::onHistogram(){
    cout<<"onHistogram "<<endl;
    if(histogram->isHidden()){
       widgetOpenCV->setHistogram(1);
       histogram->show();
    }else{
        widgetOpenCV->setHistogram(0);
        histogram->hide();
    }

}

void InheritSistemView::onContour(){
    cout<<"onContour "<<endl;
    if(countur->isHidden()){
        widgetOpenCV->setContour(1);
        countur->show();
    }else{
        widgetOpenCV->setContour(0);
        countur->hide();
    }
}

void InheritSistemView::onTracking(CvPoint point, int state){
        cout<<"get tracker.."<<endl;
        tracking->setP1(point);
        tracking->setState(state);
        tracking->getResult();
}

void InheritSistemView::sinkronisasi(IplImage *image){
    if(hist == 0){
        hist = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
    }
        cvCopy(image,hist);
        histogram->setQwidgetVal(hist,1);
}

void InheritSistemView::loadCountur(IplImage *image){
    if(cou == 0){
        cou = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
    }
        cvCopy(image, cou);
        countur->setCountur(cou,1);

}

void InheritSistemView::onPetunjuk(){
    if(help->isHidden()){
        help->show();
    }else{
        help->hide();
    }
}
