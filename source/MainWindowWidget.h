#ifndef _MAINWINDOWWIDGET_H
#define _MAINWINDOWWIDGET_H 

#include "ui_mainwindow.h"
#include "EventHandler.h"

#include "Area.h"

#include <QMainWindow>
#include <QVector>

class Engine;

class MainWindowWidget : public QMainWindow, public EventHandler
{
Q_OBJECT

public:
	MainWindowWidget(Engine &engine);

	virtual void handleNewFrame(QSharedPointer<const Frame> framePtr);
	virtual void handleNewDiffFrame(QSharedPointer<const Frame> framePtr);

protected slots:
	void on_actionCamera_triggered();
	void on_actionFile_triggered();
	void on_actionExit_triggered();
	void on_actionDisplayFrame_triggered();
	void on_actionDisplayDiff_triggered();
	void on_actionDisplayNone_triggered();
	void on_fpsBox_valueChanged(int value);
	void on_areaSelectBox_activated(int index);
	void on_areaClearButton_clicked();
	void on_playButton_toggled(bool val);

private:
	Ui::MainWindow ui;
	Engine &engine;

	QVector<Area*> areas;
};

#endif /* _MAINWINDOWWIDGET_H */
