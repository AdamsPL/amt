#ifndef _FRAMELISTENER_H
#define _FRAMELISTENER_H 

#include <QObject>
#include <QSharedPointer>

class Frame;

class FrameListener : public QObject
{
Q_OBJECT

public:
	virtual void onNewFrame(const Frame *frame) = 0;

private slots:
	void onNewFrameSlot(QSharedPointer<const Frame> ptr);
};

#endif /* _FRAMELISTENER_H */
