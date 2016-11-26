#pragma once
#include <QObject>

const int numOfProgress = 6;

class progress : public QObject
{
	Q_OBJECT

private:
	int day;
	int time;
public:
	progress();
	~progress();
	int getDay();
	int getTime();
	void timeGoOn();
};