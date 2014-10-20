#ifndef _TIMER_H
#define _TIMER_H 

class Timer
{
public:
	virtual void waitFor(int ms) = 0;
};

#endif /* _TIMER_H */
