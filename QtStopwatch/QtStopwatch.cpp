#include "QtStopwatch.h"
#include "ui_QtStopwatch.h"
#include "TimerThread.h"

QtStopwatch::QtStopwatch(QWidget *parent)
    : QMainWindow(parent)
{     
    ui.setupUi(this);

    TimerThread_emit = new TimerThread(this, true); //TimerThread로 연결.
  
    connect(TimerThread_emit, &TimerThread::ms_signal, this, &QtStopwatch::on_stopwatch_timer); //SIGNAL이 발생하면 SLOT 이벤트가 발생.
    //아래보다 위쪽으로 짜자. 둘이 동일한 기능이다.
    //connect(stopwatch_timer, SIGNAL(timeout()), this, SLOT(on_stopwatch_timer())); //SIGNAL이 발생하면 SLOT 이벤트가 발생.
    //QTimer를 만들고, SLOT에 timeout()에 연결. start() 넣어주면 특정 interval에 timeout() signal을 발생.  

    connect(ui.pushButton_Start, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_start);
    connect(ui.pushButton_Lab, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_lab);
    connect(ui.pushButton_Stop, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_stop);
    connect(ui.pushButton_Reset, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_reset);

    ui.pushButton_Lab->setEnabled(false); //버튼 비활성화 이벤트. start제외한 다른 버튼은 시작시 false로.
    ui.pushButton_Stop->setEnabled(false);
    ui.pushButton_Reset->setEnabled(false);
}

void QtStopwatch::closeEvent()
{
    TimerThread_emit->bstop = false;
    this->close();
}

void QtStopwatch::PushButton_start() //start 누르면 10ms 기준으로 카운트 시작.
{
    TimerThread_emit->start(); //기본 단위 10ms     

    ui.pushButton_Start->setEnabled(false);
    ui.pushButton_Lab->setEnabled(true);
    ui.pushButton_Stop->setEnabled(true);
}

void QtStopwatch::on_stopwatch_timer(QTime t) //start 눌렀을 때 타이머 lcd에 숫자 올리기. connect에서 TimerThread::ms_signal을 썼기에 signal에서 나오는 값(QTime t)을 받는거
{           
        int hour = t.hour(); //t(00:00:00.00)에서 앞의 hour부분만 떼옴
        //stopwatch_time / 360000; //이전 코드. 타이머 기본 단위는 1ms. 1/1000sec. 1시간 = 3600sec = 3600 000ms. 우리는 기본단위 10ms니까 3600 00 으로 나눈거. 7/4=1. 7%4=3
        int minute = t.minute(); //stopwatch_time % 360000 / 6000; // % 3600 00 하면 시간이나옴. 그 시간을 / 60 00 하면 분이 나온다
        int second = t.second();//stopwatch_time % 6000 / 100; // % 60 00하면 시간, 분 날아가고 60초 이내 시간만 남는다(ex 45.00초) 45만 남기려면? 100으로 까면 45만 남음.
        int ms = t.msec();//stopwatch_time % 100;

        // HMS 날리고 0.__ 만 남기려면? 0.__은 사실 ms로 표현하면 45___ms. 100ms + 10ms + 1ms. 
        // 360101 ms 라 하면 1시간 1.01초. ms에서 남기고 싶은건 0.01(1) 만 남기고싶다. 100으로 나누면 된다.

        ui.lcd_H_1->display(hour / 10); //위에서 3600초를 1시간으로 표현했다. 이걸 lcd상으로 표현하면 01. 첫째자리 0으로 만들려면 /10,
        ui.lcd_H_2->display(hour % 10); // 여긴 %10

        ui.lcd_M_1->display(minute / 10);
        ui.lcd_M_2->display(minute % 10);

        ui.lcd_S_1->display(second / 10);
        ui.lcd_S_2->display(second % 10);

        ui.lcd_ms_1->display(ms / 100);
        ui.lcd_ms_2->display(ms % 100 /10);    
}

void QtStopwatch::PushButton_stop()
{
    TimerThread_emit->bstop = false;

    ui.pushButton_Stop->setEnabled(false);
    ui.pushButton_Start->setEnabled(false);   
    ui.pushButton_Reset->setEnabled(true);    
}

void QtStopwatch::PushButton_lab()
{
    ++LABS;

    int H_1 = ui.lcd_H_1->intValue();
    int H_2 = ui.lcd_H_2->value();

    int M_1 = ui.lcd_M_1->value();
    int M_2 = ui.lcd_M_2->value();

    int S_1 = ui.lcd_S_1->intValue();
    int S_2 = ui.lcd_S_2->intValue();

    int ms_1 = ui.lcd_ms_1->intValue();
    int ms_2 = ui.lcd_ms_2->intValue(); 

    ui.plainTextEdit->appendPlainText(QString::number(LABS)+ "                  " +     
        QString::number(H_1) + QString::number(H_2) + " : " + QString::number(M_1) + QString::number(M_2)
        + " : " + QString::number(S_1) + QString::number(S_2) + " . " + QString::number(ms_1) + QString::number(ms_2));
}

void QtStopwatch::PushButton_reset()
{
    TimerThread_emit->bstop;    
    
    LABS = 0;

    ui.lcd_H_1->display(0);
    ui.lcd_H_2->display(0);
    ui.lcd_M_1->display(0);
    ui.lcd_M_2->display(0);
    ui.lcd_S_1->display(0);
    ui.lcd_S_2->display(0);
    ui.lcd_ms_1->display(0);
    ui.lcd_ms_2->display(0);

    ui.plainTextEdit->setPlainText("");

    ui.pushButton_Start->setEnabled(true);
    ui.pushButton_Reset->setEnabled(false);
    ui.pushButton_Stop->setEnabled(false);
    ui.pushButton_Lab->setEnabled(false);
}