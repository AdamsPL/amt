#include "ViewportWidget.h"

#include "Frame.h"

#include <QDebug>

ViewportWidget::ViewportWidget(QWidget *parent)
	: QGraphicsView(parent), mode(DisplayFrame)
{
	scene.addItem(&item);
	setScene(&scene);
}

void ViewportWidget::displayFrame(QSharedPointer<const Frame> ptr)
{
	QPixmap pixmap;

	pixmap.convertFromImage(ptr->getImg());
	item.setPixmap(pixmap);
	scene.setSceneRect(0, 0, pixmap.width(), pixmap.height());

	fitInView(&item);
}

void ViewportWidget::onNewFrame(QSharedPointer<const Frame> ptr)
{
	if (mode != DisplayFrame)
		return;
	displayFrame(ptr);
}

void ViewportWidget::onMovementDetected(QSharedPointer<const Frame> ptr)
{
	if (mode != DisplayDiff)
		return;
	displayFrame(ptr);
}

void ViewportWidget::setMode(DisplayMode newMode)
{
	mode = newMode;
}
