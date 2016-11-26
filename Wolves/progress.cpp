#include "progress.h"

progress::progress()
{
	day = 0;
	time = 0;
}

progress::~progress(){}

int progress::getDay()
{
	return day;
}

int progress::getTime()
{
	return time;
}

void progress::timeGoOn()
{
	if (day == 0)
	{
		if (time == 2)
		{
			day = 1;
			time = 0;
		}
		else
		{
			time++;
		}
	}
	else if (time == numOfProgress)
	{
		day++;
		time = 0;
	}
	else
		time++;
}