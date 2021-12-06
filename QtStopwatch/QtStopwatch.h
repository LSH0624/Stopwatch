#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtStopwatch.h"
#include <QTimer>

class QtStopwatch : public QMainWindow
{
    Q_OBJECT

public:
    QtStopwatch(QWidget *parent = Q_NULLPTR);

    QTimer* stopwatch_timer = new QTimer(this);
    int stopwatch_time = 0;
    int LABS = 0;      

private slots:

    void PushButton_start();
    void PushButton_lab();
    void PushButton_stop();
    void PushButton_reset();

    void on_stopwatch_timer();

private:
    Ui::QtStopwatchClass ui;
};
