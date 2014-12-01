#include "ViewportWidget.h"

#include "Frame.h"
#include "Area.h"

#include <QMouseEvent>
#include <QDebug>

ViewportWidget::ViewportWidget(QWidget *parent)
	: QGraphicsView(parent), mode(DisplayFrame), selectedArea(0)
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

	if (lastFrameRect != pixmap.rect()) {
		lastFrameRect = pixmap.rect();
		updateAllAreaPolygons();
	}

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
	updateScene(framePtr);
}

void ViewportWidget::updateDiffFrame(QSharedPointer<const Frame> framePtr)
{
	if (mode != DisplayDiff)
		return;
	updateScene(framePtr);
}

void ViewportWidget::mousePressEvent(QMouseEvent *event)
{
	QPointF normalizedPoint = normalizePoint(event->pos());

	if (!selectedArea)
		return;

	selectedArea->add(normalizedPoint);
	updateAreaPolygon(selectedArea);
}

QPointF ViewportWidget::normalizePoint(const QPointF &point) const
{
	return QPointF(point.x() / width(), point.y() / height());
}

QPolygonF ViewportWidget::scalePolygon(const QPolygonF &poly) const
{
	QPolygonF result;

	for (int i = 0; i < poly.size(); ++i)
		result << QPointF(poly[i].x() * lastFrameRect.width(), poly[i].y() * lastFrameRect.height());

	return result;
}

void ViewportWidget::updateAllAreaPolygons()
{
	Area *area;
	foreach(area, areaRegions.keys())
		updateAreaPolygon(area);
}

void ViewportWidget::updateAreaPolygon(Area *area)
{
	QGraphicsPolygonItem *item = areaRegions[area];
	item->setPolygon(scalePolygon(area->getPolygon()));
}

void ViewportWidget::addArea(Area *area)
{
	QGraphicsPolygonItem *item = new QGraphicsPolygonItem();

	areaRegions.insert(area, item);
	scene.addItem(item);
	updateAreaPolygon(area);
	updateAreaColors();
}

void ViewportWidget::selectArea(Area *area)
{
	selectedArea = area;
}

void ViewportWidget::clearSelectedArea()
{
	if (selectedArea) {
		selectedArea->clear();
		updateAreaPolygon(selectedArea);
	}
}

void ViewportWidget::updateAreaColors()
{
	int count = areaRegions.size();
	int stride = 360 / count;
	Area *area;
	int i = 0;
	
	foreach(area, areaRegions.keys()) {
		areaRegions[area]->setBrush(QBrush(QColor::fromHsv(i * stride, 255, 128, 80)));
		++i;
	}
}
