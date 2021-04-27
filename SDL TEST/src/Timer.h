#pragma once
#include "Core.h"

class Timer
{
public:
	Timer();
	~Timer();
	void Start(unsigned int timerValue);
	bool TimeUp() const;
private:
	unsigned int m_Start, m_TimerValue;
};

