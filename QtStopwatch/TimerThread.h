#pragma once
#include <qthread.h>
#include <QTime>

class TimerThread: public QThread
{
	Q_OBJECT

public:
	explicit TimerThread(QObject* parent = 0, bool b = false);//explicit : �������ʴ� ����ȯ�� �Ͼ�� �ʵ��� ������.
	~TimerThread();
	void run();

	//���� stop = true ���, thread�� break.
	//out of the loop, and wil be disposed

	bool bstop;

signals:
	//Gui Thread�� ����ϱ� ����
	//we need to emit a signal
	void ms_signal(QTime t);

public slots:

};