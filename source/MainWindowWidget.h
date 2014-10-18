#ifndef _MAINWINDOWWIDGET_H
#define _MAINWINDOWWIDGET_H 

#include "ui_mainwindow.h"

#include <QMainWindow>

class MovementDetector;
class FrameStreamer;

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
	void on_actionDisplayFrame_triggered();
	void on_actionDisplayDiff_triggered();
	void on_actionDisplayNone_triggered();

private:
	Ui::MainWindow ui;

	FrameStreamer *streamer;
	MovementDetector *detector;
};

#endif /* _MAINWINDOWWIDGET_H */
