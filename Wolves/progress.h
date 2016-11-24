#pragma once

const int numOfProgress = 8;

class progress
{
	int day;
	int time;
public:
	progress();
	~progress();
	int getDay();
	int getTime();
	void timeGoOn();
};