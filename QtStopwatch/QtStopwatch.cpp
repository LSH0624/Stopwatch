#include "QtStopwatch.h"
#include "ui_QtStopwatch.h"
#include "TimerThread.h"

QtStopwatch::QtStopwatch(QWidget *parent)
    : QMainWindow(parent)
{     
    ui.setupUi(this);

    TimerThread_emit = new TimerThread(this, true); //TimerThread�� ����.
  
    connect(TimerThread_emit, &TimerThread::ms_signal, this, &QtStopwatch::on_stopwatch_timer); //SIGNAL�� �߻��ϸ� SLOT �̺�Ʈ�� �߻�.
    //�Ʒ����� �������� ¥��. ���� ������ ����̴�.
    //connect(stopwatch_timer, SIGNAL(timeout()), this, SLOT(on_stopwatch_timer())); //SIGNAL�� �߻��ϸ� SLOT �̺�Ʈ�� �߻�.
    //QTimer�� �����, SLOT�� timeout()�� ����. start() �־��ָ� Ư�� interval�� timeout() signal�� �߻�.  

    connect(ui.pushButton_Start, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_start);
    connect(ui.pushButton_Lab, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_lab);
    connect(ui.pushButton_Stop, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_stop);
    connect(ui.pushButton_Reset, &QAbstractButton::clicked, this, &QtStopwatch::PushButton_reset);

    ui.pushButton_Lab->setEnabled(false); //��ư ��Ȱ��ȭ �̺�Ʈ. start������ �ٸ� ��ư�� ���۽� false��.
    ui.pushButton_Stop->setEnabled(false);
    ui.pushButton_Reset->setEnabled(false);
}

void QtStopwatch::closeEvent()
{
    TimerThread_emit->bstop = false;
    this->close();
}

void QtStopwatch::PushButton_start() //start ������ 10ms �������� ī��Ʈ ����.
{
    TimerThread_emit->start(); //�⺻ ���� 10ms     

    ui.pushButton_Start->setEnabled(false);
    ui.pushButton_Lab->setEnabled(true);
    ui.pushButton_Stop->setEnabled(true);
}

void QtStopwatch::on_stopwatch_timer(QTime t) //start ������ �� Ÿ�̸� lcd�� ���� �ø���. connect���� TimerThread::ms_signal�� ��⿡ signal���� ������ ��(QTime t)�� �޴°�
{           
        int hour = t.hour(); //t(00:00:00.00)���� ���� hour�κи� ����
        //stopwatch_time / 360000; //���� �ڵ�. Ÿ�̸� �⺻ ������ 1ms. 1/1000sec. 1�ð� = 3600sec = 3600 000ms. �츮�� �⺻���� 10ms�ϱ� 3600 00 ���� ������. 7/4=1. 7%4=3
        int minute = t.minute(); //stopwatch_time % 360000 / 6000; // % 3600 00 �ϸ� �ð��̳���. �� �ð��� / 60 00 �ϸ� ���� ���´�
        int second = t.second();//stopwatch_time % 6000 / 100; // % 60 00�ϸ� �ð�, �� ���ư��� 60�� �̳� �ð��� ���´�(ex 45.00��) 45�� �������? 100���� ��� 45�� ����.
        int ms = t.msec();//stopwatch_time % 100;

        // HMS ������ 0.__ �� �������? 0.__�� ��� ms�� ǥ���ϸ� 45___ms. 100ms + 10ms + 1ms. 
        // 360101 ms �� �ϸ� 1�ð� 1.01��. ms���� ����� ������ 0.01(1) �� �����ʹ�. 100���� ������ �ȴ�.

        ui.lcd_H_1->display(hour / 10); //������ 3600�ʸ� 1�ð����� ǥ���ߴ�. �̰� lcd������ ǥ���ϸ� 01. ù°�ڸ� 0���� ������� /10,
        ui.lcd_H_2->display(hour % 10); // ���� %10

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