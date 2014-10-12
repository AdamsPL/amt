#include "FrameListener.h"

void FrameListener::onNewFrameSlot(QSharedPointer<const Frame> ptr)
{
	onNewFrame(ptr.data());
}
