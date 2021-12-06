#include "QtStopwatch.h"
#include "ui_QtStopwatch.h"
#include <QTimer>

QtStopwatch::QtStopwatch(QWidget *parent)
    : QMainWindow(parent)
{     
    ui.setupUi(this);
    
    stopwatch_timer->setTimerType(Qt::PreciseTimer); //PreciseTimer : ms 구현

    stopwatch_timer = new QTimer(this);
    connect(stopwatch_timer, SIGNAL(timeout()), this, SLOT(on_stopwatch_timer())); //SIGNAL이 발생하면 SLOT 이벤트가 발생.
        //QTimer를 만들고, SLOT에 timeout()에 연결함. start() 넣어주면 특정 interval에 timeout() signal을 발생시킴.

    connect(ui.pushButton_Start, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_start);
    connect(ui.pushButton_Lab, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_lab);
    connect(ui.pushButton_Stop, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_stop);
    connect(ui.pushButton_Reset, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_reset);
}

void QtStopwatch::PushButton_start() //start 누르면 10ms 기준으로 카운트 시작.
{
   stopwatch_timer->start(10); //기본 단위 10ms     
}

void QtStopwatch::on_stopwatch_timer() //start 눌렀을 때 타이머 lcd에 숫자 올리기
{                  
        ++stopwatch_time;

        int hour = stopwatch_time / 360000; // 타이머 기본 단위는 1ms. 1/1000sec. 1시간 = 3600sec = 3600 000ms. 우리는 기본단위 10ms니까 3600 00 으로 나눈거. 7/4=1. 7%4=3
        int minute = stopwatch_time % 360000 / 6000; // % 3600 00 하면 시간이나옴. 그 시간을 / 60 00 하면 분이 나온다
        int second = stopwatch_time % 6000 / 100; // % 60 00하면 시간, 분 날아가고 60초 이내 시간만 남는다(ex 45.00초) 45만 남기려면? 100으로 까면 45만 남음.
        int ms = stopwatch_time % 100;

        // HMS 날리고 0.__ 만 남기려면? 0.__은 사실 ms로 표현하면 45___ms. 100ms + 10ms + 1ms. 
        // 360101 ms 라 하면 1시간 1.01초. ms에서 남기고 싶은건 0.01(1) 만 남기고싶다. 100으로 나누면 된다.

        ui.lcd_H_1->display(hour / 10); //위에서 3600초를 1시간으로 표현했다. 이걸 lcd상으로 표현하면 01. 첫째자리 0으로 만들려면 /10,
        ui.lcd_H_2->display(hour % 10); // 여긴 %10

        ui.lcd_M_1->display(minute / 10);
        ui.lcd_M_2->display(minute % 10);

        ui.lcd_S_1->display(second / 10);
        ui.lcd_S_2->display(second % 10);

        ui.lcd_ms_1->display(ms / 10);
        ui.lcd_ms_2->display(ms % 10);    
}

void QtStopwatch::PushButton_stop()
{
    stopwatch_timer->stop();
}

void QtStopwatch::PushButton_lab()
{
    ++LABS;

    int H_1 = ui.lcd_H_1->value();
    int H_2 = ui.lcd_H_2->value();

    int M_1 = ui.lcd_M_1->value();
    int M_2 = ui.lcd_M_2->value();

    int S_1 = ui.lcd_S_1->value();
    int S_2 = ui.lcd_S_2->value();

    int ms_1 = ui.lcd_ms_1->value();
    int ms_2 = ui.lcd_ms_2->value();

    ui.plainTextEdit->appendPlainText(QString::number(LABS)+ "                  " +     
        QString::number(H_1) + QString::number(H_2) + ":" + QString::number(M_1) + QString::number(M_2)
        + ":" + QString::number(S_1) + QString::number(S_2) + "." + QString::number(ms_1) + QString::number(ms_2));
}

void QtStopwatch::PushButton_reset()
{
    stopwatch_timer->stop();
    stopwatch_time = 0;
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
}