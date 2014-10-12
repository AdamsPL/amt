#ifndef _MAINWINDOWWIDGET_H
#define _MAINWINDOWWIDGET_H 

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QGraphicsPixmapItem>

class FrameStreamer;
class Frame;

class MainWindowWidget : public QMainWindow
{
Q_OBJECT

public:
	MainWindowWidget(FrameStreamer *streamer);
	void setFrameStreamer(FrameStreamer *streamer);

protected slots:
	void on_actionCamera_triggered();
	void on_actionFile_triggered();
	void on_actionExit_triggered();
	void onNewFrame(QSharedPointer<const Frame> ptr);

private:
	Ui::MainWindow ui;
	QGraphicsScene scene;
	QGraphicsPixmapItem item;
	FrameStreamer *streamer;
};

#endif /* _MAINWINDOWWIDGET_H */
