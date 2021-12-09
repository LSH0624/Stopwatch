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
//run() ������ �� �����尡 ����.
void TimerThread::run()
{
	bstop = true;
	QTime n(0, 0, 0, 0); // n == 00:00:00.00 ���� �ʱ� ���� => �ǵ� ms �����Ǵ°� �³� Ȯ�ο��.
	QTime t;
	int msec{ 0 }; //msec�� 0���� ����.

	while (bstop)
	{
		QThread::msleep(1);		
		msec += 10; //msec�� +10�� ����
		t = n.addMSecs(msec); // ���� msec ���� t�� ������. �ᱹ run ������ �� ms_signal�� ���� signal�� �Ѱ��ش�

		emit ms_signal(t);		//���� ������ �ѹ���. �� 25�ٿ� QTime t; �ѹ��� �� ����.					
	}
}