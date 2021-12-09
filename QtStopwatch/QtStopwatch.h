#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtStopwatch.h"
#include "TimerThread.h"

class QtStopwatch : public QMainWindow
{
    Q_OBJECT

public:
    QtStopwatch(QWidget *parent = Q_NULLPTR);
        
    int stopwatch_time = 0;
    int LABS = 0;      

    TimerThread* TimerThread_emit;

private slots:

    void PushButton_start();
    void PushButton_lab();
    void PushButton_stop();
    void PushButton_reset();

    void on_stopwatch_timer(QTime t);
    void QtStopwatch::closeEvent();
    
private:
    Ui::QtStopwatchClass ui;
};
