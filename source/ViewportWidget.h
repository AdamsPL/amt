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

	virtual void handleDiff(QSharedPointer<const Frame> framePtr);

signals:
	void updateFrameSignal(QSharedPointer<const Frame> framePtr);

private slots:
	void updateFrame(QSharedPointer<const Frame> framePtr);

private:
	virtual void handle(QSharedPointer<const Frame> framePtr);

	QGraphicsScene scene;
	QGraphicsPixmapItem item;
	DisplayMode mode;
};

#endif /* _VIEWPORT_WIDGET_H */
