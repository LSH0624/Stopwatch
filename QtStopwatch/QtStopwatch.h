#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtStopwatch.h"
#include <QTimer>
#include "TimerThread.h"

class QtStopwatch : public QMainWindow
{
    Q_OBJECT

public:
    QtStopwatch(QWidget *parent = Q_NULLPTR);

    QTimer* stopwatch_timer = new QTimer(this);
    int stopwatch_time = 0;
    int LABS = 0;      

    TimerThread* TimerThread_emit;

private slots:

    void PushButton_start();
    void PushButton_lab();
    void PushButton_stop();
    void PushButton_reset();

    void on_stopwatch_timer(QTime t);
    
private:
    Ui::QtStopwatchClass ui;
};
