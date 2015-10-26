#include <QGridLayout>
#include <QDebug>
#include "headctrl.h"

using namespace cv;

static QLabel *showimage;

Headctrl::Headctrl(QWidget *parent) : QWidget(parent)
{
    showimage = new QLabel;
    //layout
    ctl_layout = new QGridLayout;
    ctl_sublayout = new QVBoxLayout;
    ctl_on_btn = new QPushButton(tr("Begin Control"));
    ctl_off_btn = new QPushButton(tr("Stop Control"));
    ctl_on_btn->setMinimumSize(100,200);
    ctl_off_btn->setMinimumSize(100,200);

    ctl_sublayout->addWidget(ctl_on_btn);
    ctl_sublayout->addWidget(ctl_off_btn);
    ctl_layout->addWidget(showimage,1,1);
    ctl_layout->addLayout(ctl_sublayout,1,2);
    ctl_layout->setColumnStretch(0,3);
    ctl_layout->setColumnStretch(1,1);
    setLayout(ctl_layout);

    connect(ctl_on_btn,SIGNAL(clicked(bool)),this,SLOT(headctrlstart()));
    connect(ctl_off_btn,SIGNAL(clicked(bool)),this,SLOT(headctrlend()));
}

void getframe()
{
    double timec;
    extern Mat img;
    extern IplImage * frame;
    //extern Mat HandImg;
    Mat tomat(frame,false);
    timec=cvGetTickCount();
    detface(tomat);


    cvtColor(img,img, CV_BGR2RGB);
    //cvtColor(HandImg,HandImg,CV_RGB2BGR);
    QImage image((const uchar*)img.data,img.cols,img.rows,img.step,QImage::Format_RGB888);
    //QImage image((const uchar*)HandImg.data,HandImg.cols,HandImg.rows,HandImg.step,QImage::Format_RGB888);
    showimage->setPixmap(QPixmap::fromImage(image));
    timec = (double)cvGetTickCount() - timec;
    printf( "show time = %g ms\n", timec/((double)cvGetTickFrequency()*1000));
}

void Headctrl::headctrlstart()
{
    extern int state;
    state = 1;
}

void Headctrl::headctrlend()
{
    extern int state;
    state = 4;
}
