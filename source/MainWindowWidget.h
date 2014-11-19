#ifndef _MAINWINDOWWIDGET_H
#define _MAINWINDOWWIDGET_H 

#include "ui_mainwindow.h"

#include <QMainWindow>

class FrameMovementExtractor;
class FrameStreamer;

class MainWindowWidget : public QMainWindow
{
Q_OBJECT

public:
	MainWindowWidget();
	void setFrameStreamer(FrameStreamer *streamer);
	void setFrameMovementExtractor(FrameMovementExtractor *detector);
	void connectComponents();

protected slots:
	void on_actionCamera_triggered();
	void on_actionFile_triggered();
	void on_actionExit_triggered();
	void on_actionDisplayFrame_triggered();
	void on_actionDisplayDiff_triggered();
	void on_actionDisplayNone_triggered();
	void on_fpsBox_valueChanged(int value);

private:
	Ui::MainWindow ui;

	FrameStreamer *streamer;
	FrameMovementExtractor *detector;
};

#endif /* _MAINWINDOWWIDGET_H */
