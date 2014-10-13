#ifndef _MAINWINDOWWIDGET_H
#define _MAINWINDOWWIDGET_H 

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QGraphicsPixmapItem>

class MovementDetector;
class FrameStreamer;
class Frame;

class MainWindowWidget : public QMainWindow
{
Q_OBJECT

public:
	MainWindowWidget();
	void setFrameStreamer(FrameStreamer *streamer);
	void setMovementDetector(MovementDetector *detector);
	void connectComponents();

protected slots:
	void on_actionCamera_triggered();
	void on_actionFile_triggered();
	void on_actionExit_triggered();
	void onNewFrame(QSharedPointer<const Frame> ptr);
	void onMovementDetected(QSharedPointer<const Frame> ptr);

private:
	Ui::MainWindow ui;
	QGraphicsScene scene;
	QGraphicsPixmapItem streamItem;
	QGraphicsPixmapItem movementItem;

	FrameStreamer *streamer;
	MovementDetector *detector;
};

#endif /* _MAINWINDOWWIDGET_H */
