#ifndef TIMER_H

#define TIMER_H

#include <time.h>

class Timer
{
private:
	
	static Timer*		m_Timer;

	clock_t		lastTime;
	
	float		ClockDiff	( clock_t clock1, clock_t clock2 );

public:

	Timer();
	~Timer();

	static Timer*		GetInstance			();
	void				CleanUp				();

	float		GetElapsedTime	();
	void		ResetTimer		();
};

#endif