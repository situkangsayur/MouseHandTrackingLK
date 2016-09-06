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
#ifndef INHERITSISTEMVIEW_H
#define INHERITSISTEMVIEW_H

#include <QWidget>
#include <QDialog>
#include "iostream"
#include "ui_sistemview.h"
#include "stdlib.h"
#include "listener.h"

#include "sistemmodel.h"
#include "sistemcontroll.h"
#include "cv.h"
#include "handtracking.h"
#include "dialoghistogram.h"
#include "dialogcontour.h"
#include "dialoghelp.h"


using namespace std;


class InheritSistemView : public QWidget, public Ui::SIstemView,public listener
{
    Q_OBJECT

public :
    SistemModel *model;
    SistemControll *controll;
    HandTracking *tracking;

    DialogHistogram *histogram;
    DialogContour *countur;
    IplImage *hist;
    IplImage *cou;
    DialogHelp *help;


public:
    explicit
    InheritSistemView(QWidget *parent = 0);
    ~InheritSistemView();

signals:

public :
        void onStart();
        void onStop();
        void onHistogram();
        void onContour();
        void onTracking(CvPoint point, int state);
        void sinkronisasi(IplImage *image);
        void loadCountur(IplImage *image);
        void onPetunjuk();



    public slots:
                void on_buttonStart_clicked();
                void on_buttonStop_clicked();
                void on_buttonHistogram_clicked();
                void on_buttonContour_clicked();
                void on_buttonExit_clicked();
                void on_buttonPetunjuk_clicked();

};

#endif // INHERITSISTEMVIEW_H
