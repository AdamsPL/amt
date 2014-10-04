#ifndef _FRAMELISTENER_H
#define _FRAMELISTENER_H 

#include <QObject>

class Frame;

class FrameListener : public QObject
{
Q_OBJECT

public:
	virtual void onNewFrame(const Frame *frame) = 0;

private slots:
	void onNewFrameSlot(const Frame *frame);
};

#endif /* _FRAMELISTENER_H */
