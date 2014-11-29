#include "ViewportWidget.h"

#include "Frame.h"

#include <QDebug>

ViewportWidget::ViewportWidget(QWidget *parent)
	: QGraphicsView(parent), mode(DisplayFrame)
{
	connect(this, SIGNAL(updateFrameSignal(QSharedPointer<const Frame>)), this, SLOT(updateFrame(QSharedPointer<const Frame>)));
	scene.addItem(&item);
	setScene(&scene);
}

void ViewportWidget::updateFrame(QSharedPointer<const Frame> ptr)
{
	QPixmap pixmap;

	pixmap.convertFromImage(ptr->getImg());
	item.setPixmap(pixmap);
	scene.setSceneRect(0, 0, pixmap.width(), pixmap.height());

	fitInView(&item);
}

void ViewportWidget::setMode(DisplayMode newMode)
{
	mode = newMode;
}

void ViewportWidget::handle(QSharedPointer<const Frame> framePtr)
{
	if (mode != DisplayFrame)
		return;
	emit updateFrameSignal(framePtr);
}

void ViewportWidget::handleDiff(QSharedPointer<const Frame> framePtr)
{
	if (mode != DisplayDiff)
		return;
	emit updateFrameSignal(framePtr);
}
