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
#include "MyCameraWindow.h"

MyCameraWindow::MyCameraWindow( QWidget *parent) : QWidget(parent) {


    camera = cvCreateCameraCapture(1);

    if (!camera) {
            camera= cvCaptureFromCAM(0);
            //cout << "hhheeeaarrrr...\n";

    }

    if (!camera) {
            cout << "Could not initialize capturing...\n";
            return;
    }

    assert(camera);

    image = 0;
    black = 0;
    state = 0;
    histogram = 0;
    countur = 0;

    cont = new ConContour();


    QVBoxLayout *layout = new QVBoxLayout;
    cvwidget = new QOpenCVWidget(this);
    layout->addWidget(cvwidget);
    setLayout(layout);
    resize(640, 480);

    startTimer(100);  // 0.1-second timer

 }

void MyCameraWindow::timerEvent(QTimerEvent*) {
    image = cvQueryFrame(camera);
    if(black == 0){
        black = cvCreateImage(cvSize(image->width,image->height),image->depth,image->nChannels);
    }
    if(gray == 0){
        gray = cvCreateImage(cvSize(image->width,image->height),image->depth,1);
    }

    if(state == 1){

        cont->setCurrentFrame(image);
        cont->frameGrabber();


        model->setState(cont->getFingerNum()

                        );
        model->setPoint(cont->getp1());


        model->setSingkronisasiMouse();


        image=cont->getCurrentFrame();

        model->setImage(image);

        cvCvtColor(cont->getSkin(),black,CV_GRAY2BGR);

         model->setCountur(black);
        if(countur == 1){
            model->loadCountur();
        }

        if(histogram == 1){
            cout<<"masuk histogram 1"<<endl;
            model->singkronisasiHis();
        }

    }else{
        cvFlip(image,0,1);
        cvCvtColor(image,gray,CV_RGB2GRAY);
        cvCvtColor(gray,black,CV_GRAY2BGR);

        model->setImage(image);
        model->setCountur(black);

        if(countur == 1){
            model->loadCountur();
        }

        if(histogram == 1){
            cout<<"masuk histogram 1"<<endl;
            model->singkronisasiHis();
        }

    }
      cvwidget->putImage(image);

}

void MyCameraWindow::setModel(SistemModel *model){
    this->model = model;
}


void MyCameraWindow::setState(int state){
    this->state = state;
}

void MyCameraWindow::setHistogram(int histogram){
    this->histogram = histogram;
}

void MyCameraWindow::setContour(int contour){
    this->countur = contour;
}

int MyCameraWindow::getState(){
    return state;
}

int MyCameraWindow::getHistogram(){
    return histogram;
}

int MyCameraWindow::getContour(){
    return countur;
}

