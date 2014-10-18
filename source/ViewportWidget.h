#ifndef _VIEWPORT_WIDGET_H
#define _VIEWPORT_WIDGET_H 

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QSharedPointer>

class Frame;

class ViewportWidget : public QGraphicsView
{
	Q_OBJECT

public:
	ViewportWidget(QWidget *parent);
	enum DisplayMode
	{
		DisplayNone,
		DisplayFrame,
		DisplayDiff
	};
	void setMode(DisplayMode newMode);

protected slots:
	void onNewFrame(QSharedPointer<const Frame> ptr);
	void onMovementDetected(QSharedPointer<const Frame> ptr);

private:
	void displayFrame(QSharedPointer<const Frame> ptr);

	QGraphicsScene scene;
	QGraphicsPixmapItem item;
	DisplayMode mode;
};

#endif /* _VIEWPORT_WIDGET_H */
