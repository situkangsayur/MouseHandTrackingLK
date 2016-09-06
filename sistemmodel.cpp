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
#include "sistemmodel.h"

SistemModel::SistemModel()
{
}


void SistemModel::setPtX(int ptX){
    this->ptX = ptX;
}

void SistemModel::setPtY(int ptY){
    this->ptY = ptY;
}

int SistemModel::getPtX(){
    return ptX;
}

int SistemModel::getPtY(){
    return ptY;
}

void SistemModel::setImage(IplImage *image){
    this->image = image;
}

void SistemModel::setCountur(IplImage *countur){
    this->countur = countur;
}

void SistemModel::setPoint(CvPoint points){
    this->point = points;
}

CvPoint SistemModel::getPoint(){
    return this->point;
}

void SistemModel::setState(int state){
    this->state = state;
}

int SistemModel::getState(){
    return state;
}

void SistemModel::setListener(listener *list){
        this->listen = list;
}

 void SistemModel::fireOnStart(){
     if(listen != NULL){
         listen->onStart();
     }
 }

 void SistemModel::fireOnStop(){
     if(listen != NULL){
         listen->onStop();
     }
 }

 void SistemModel::fireOnHistogram(){
     if(listen != NULL){
         listen->onHistogram();
     }
 }

 void SistemModel::fireOnContour(){
     if(listen != NULL){
         listen->onContour();
     }
 }

 void SistemModel::fireOnSingkronisasi(){
     if(listen != NULL){
         listen->sinkronisasi(image);
     }
 }


 void SistemModel::fireOnTracking(){
     if(listen != NULL){
         listen->onTracking(this->point, this->state);
     }
 }

 void SistemModel::fireOnLoadCountur(){
     if(listen != NULL){
         listen->loadCountur(countur);
     }
 }

 void SistemModel::fireOnPetunjuk(){
     if(listen!=NULL){
         listen->onPetunjuk();
     }
 }



 void SistemModel::doHandTracking(){
     fireOnStart();
 }

 void SistemModel::doStopHandTracking(){
     fireOnStop();
 }


 void SistemModel::getHistogram(){
     fireOnHistogram();
 }

 void SistemModel::getContour(){
     fireOnContour();
 }

 void SistemModel::setSingkronisasiMouse(){
     fireOnTracking();
 }

 void SistemModel::singkronisasiHis(){
     fireOnSingkronisasi();
 }

 void SistemModel::loadCountur(){
     fireOnLoadCountur();
 }

 void SistemModel::tampilPetunjuk(){
    fireOnPetunjuk();
 }



