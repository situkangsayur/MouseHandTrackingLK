#
# MouseHandTracking is an application to control mouse pointer of the computer with hand gesture via camera
# Copyright (C) 2011  Hendri Karisma
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# contact author at situkangsayur[at]gmail[dot]com
#
#-------------------------------------------------
#
# Project created by QtCreator 2011-06-16T19:26:35
#
#-------------------------------------------------

QT       += core gui
TARGET = MouseHandTrackingLK
DEPENDPATH += .
TEMPLATE = app


INCLUDEPATH +=  /usr/local/include \
                /usr/include/opencv \
                /usr/lib
LIBS += -lX11 \
        -lXtst \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_calib3d \
    -lopencv_video \
    -lopencv_features2d \
    -lopencv_ml \
    -lopencv_highgui \
    -lopencv_objdetect \
    -lopencv_contrib \
    -lopencv_legacy



SOURCES += main.cpp\
        sistemview.cpp \
    QOpenCVWidget.cpp \
    MyCameraWindow.cpp \
    sistemcontroll.cpp \
    sistemmodel.cpp \
    ConContour.cpp \
    inheritsistemview.cpp \
    handtracking.cpp \
    conhistogram.cpp \
    HistogramWindow.cpp \
    dialoghistogram.cpp \
    QHistogramWidget.cpp \
    dialogcontour.cpp \
    QCounturWidget.cpp \
    CounturWindow.cpp \
    dialoghelp.cpp

HEADERS  += sistemview.h \
    QOpenCVWidget.h \
    MyCameraWindow.h \
    sistemcontroll.h \
    listener.h \
    sistemmodel.h \
    YCrCbSkinDetector.h \
    Image.h \
    IColorSkinDetector.h \
    ConContour.h \
    inheritsistemview.h \
    handtracking.h \
    conhistogram.h \
    HistogramWindow.h \
    dialoghistogram.h \
    QHistogramWidget.h \
    dialogcontour.h \
    QCounturWidget.h \
    CounturWindow.h \
    dialoghelp.h

FORMS    += sistemview.ui \
    dialoghistogram.ui \
    dialogcontour.ui \
    dialoghelp.ui

OTHER_FILES += \
    images/stop.png \
    images/play.png \
    images/histogram.jpg \
    images/GNU.png \
    images/exit.png \
    images/contour.jpg \
    images/7023332-human-hand-concept-made-of-100-icons-set-in-black-color.jpg \
    images/tombolStart.png \
    images/buttonStop.png \
    images/button Keluar.png \
    images/buttonHistogram.png \
    images/buttonContour.png

RESOURCES += \
    projectresource.qrc
