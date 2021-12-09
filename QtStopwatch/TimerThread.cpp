#include "TimerThread.h"
#include <qthread.h>
#include <QTime>
#include <QThread>
#include "QtStopwatch.h"

TimerThread::TimerThread(QObject *parent, bool b):QThread(parent), bstop(b) //=>???? MSB418 : 
{
}

TimerThread::~TimerThread()
{
}
//run() will be called when this tread start
//run() 누르면 이 스레드가 동작.
void TimerThread::run()
{
	bstop = true;
	QTime n(0, 0, 0, 0); // n == 00:00:00.00 으로 초기 설정 => 맨뒤 ms 구현되는거 맞나 확인요망.
	QTime t;
	int msec{ 0 }; //msec를 0으로 시작.

	while (bstop)
	{
		QThread::msleep(1);		
		msec += 10; //msec를 +10씩 증가
		t = n.addMSecs(msec); // 변수 msec 마다 t에 더해줌. 결국 run 눌렀을 때 ms_signal을 통해 signal을 넘겨준다

		emit ms_signal(t);		//변수 지정은 한번만. 위 25줄에 QTime t; 한번이 면 족함.					
	}
}