#ifndef _TIMER_H
#define _TIMER_H 

class Engine;

class Timer
{
public:
	Timer(Engine &engine);
	virtual void waitFor(int ms) = 0;

protected:
	void trigger();

private:
	Engine &engine;
};

#endif /* _TIMER_H */
