#ifndef _ENGINE_H
#define _ENGINE_H 

class Frame;
class Timer;
class FrameSource;
class EventMonitor;

class Engine
{
public:
	Engine();
	void iterate();

	inline void setTimer(Timer *timer) { this->timer = timer; }
	inline void setFrameDelay(int delay) { this->frameDelay = delay; }
	inline void setSource(FrameSource *src) { this->source = src; }
	inline void setEventMonitor(EventMonitor *monitor) { this->monitor = monitor; }

private:
	Timer *timer;
	int frameDelay;
	FrameSource *source;
	EventMonitor *monitor;
};

#endif /* _ENGINE_H */
