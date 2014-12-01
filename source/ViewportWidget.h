#ifndef _VIEWPORT_WIDGET_H
#define _VIEWPORT_WIDGET_H 

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QSharedPointer>
#include <QMap>

class Area;
class Frame;

class ViewportWidget : public QGraphicsView
{
public:
	ViewportWidget(QWidget *parent);

	enum DisplayMode
	{
		DisplayNone,
		DisplayFrame,
		DisplayDiff
	};
	void setMode(DisplayMode newMode);

	void updateFrame(QSharedPointer<const Frame> framePtr);
	void updateDiffFrame(QSharedPointer<const Frame> framePtr);

	void addArea(Area *area);
	void selectArea(Area *area = 0);
	void clearSelectedArea();

protected:
	void mousePressEvent(QMouseEvent *event);

private:
	void updateAreaColors();
	void updateAreaPolygon(Area *area);
	void updateAllAreaPolygons();

	QPointF normalizePoint(const QPointF &point) const;
	QPolygonF scalePolygon(const QPolygonF &poly) const;
	void updateScene(const QSharedPointer<const Frame> &ptr);

	QGraphicsScene scene;
	QGraphicsPixmapItem item;
	DisplayMode mode;

	QRect lastFrameRect;

	QMap<Area*, QGraphicsPolygonItem*> areaRegions;
	Area *selectedArea;
};

#endif /* _VIEWPORT_WIDGET_H */
