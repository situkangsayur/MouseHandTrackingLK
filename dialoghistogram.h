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
#ifndef DIALOGHISTOGRAM_H
#define DIALOGHISTOGRAM_H

#include <QDialog>
#include "cv.h"
//#include "inherithistogramdialog.h"

namespace Ui {
    class DialogHistogram;
}

class DialogHistogram : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHistogram(QWidget *parent = 0);
    ~DialogHistogram();

     void setQwidgetVal(IplImage *img,int val);

private slots:
     void on_buttonTutup_clicked();

private:
    Ui::DialogHistogram *ui;
};

#endif // DIALOGHISTOGRAM_H
