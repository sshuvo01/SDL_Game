#include "Timer.h"

Timer::Timer()
{
	m_Start = SDL_GetTicks();
	m_TimerValue = 0;
}

Timer::~Timer()
{
}

void Timer::Start(unsigned int timerValue)
{
	m_Start = SDL_GetTicks();
	m_TimerValue = timerValue;
}

bool Timer::TimeUp() const
{
	if (SDL_GetTicks() - m_Start < m_TimerValue) return false;
	else return true;
}

