#ifndef _VIEWPORT_WIDGET_H
#define _VIEWPORT_WIDGET_H 

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QSharedPointer>

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

private:
	void updateScene(const QSharedPointer<const Frame> &ptr);

	QGraphicsScene scene;
	QGraphicsPixmapItem item;
	DisplayMode mode;
};

#endif /* _VIEWPORT_WIDGET_H */
