#include "ViewportWidget.h"

#include "Frame.h"

#include <QDebug>

ViewportWidget::ViewportWidget(QWidget *parent)
	: QGraphicsView(parent), mode(DisplayFrame)
{
	scene.addItem(&item);
	setScene(&scene);
}

void ViewportWidget::updateScene(const QSharedPointer<const Frame> &ptr)
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

void ViewportWidget::updateFrame(QSharedPointer<const Frame> framePtr)
{
	if (mode != DisplayFrame)
		return;
	updateFrame(framePtr);
}

void ViewportWidget::updateDiffFrame(QSharedPointer<const Frame> framePtr)
{
	if (mode != DisplayDiff)
		return;
	updateFrame(framePtr);
}
