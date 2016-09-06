#ifndef COUNTURWINDOW_H_
#define COUNTURWINDOW_H_

#include <QWidget>
#include <QVBoxLayout>
#include "QCounturWidget.h"
#include "qpushbutton.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>



class CounturWindow : public QWidget
{
    Q_OBJECT
    private:
        QCounturWidget *widgetCountur;
        CvCapture *camera;

        IplImage *image;
        int set;
        
    public:

        CounturWindow(QWidget *parent=0);
        ~CounturWindow();

        void setImage(IplImage *image);

        void setSet(int s);
         
    protected:
        void timerEvent(QTimerEvent*);
};


#endif /*ContourWindow_H_*/
