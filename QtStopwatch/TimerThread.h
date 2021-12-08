#pragma once
#include <qthread.h>
#include <QTime>

class TimerThread: public QThread
{
	Q_OBJECT

public:
	explicit TimerThread(QObject* parent = 0, bool b = false);//explicit : 원하지않는 형변환이 일어나지 않도록 제한함.
	~TimerThread();
	void run();

	//만약 stop = true 라면, thread는 break.
	//out of the loop, and wil be disposed

	bool bstop;

signals:
	//Gui Thread와 통신하기 위함
	//we need to emit a signal
	void ms_signal(QTime t);

public slots:

};