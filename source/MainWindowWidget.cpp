#include "MainWindowWidget.h"

#include "CameraFrameSource.h"
#include "FileFrameSource.h"

#include <QFileDialog>

#include <QDebug>

MainWindowWidget::MainWindowWidget()
{
	ui.setupUi(this);
}

void MainWindowWidget::on_actionCamera_triggered()
{
	//TODO:streamer->stop();
	//TODO:streamer->setFrameSource(new CameraFrameSource());
	//TODO:streamer->start();
}

void MainWindowWidget::on_actionFile_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open movie");
	if (filename.isNull())
		return;
	//TODO:streamer->stop();
	//TODO:streamer->setFrameSource(new FileFrameSource(filename));
	//TODO:streamer->start();
}

void MainWindowWidget::on_actionExit_triggered()
{
	//TODO:streamer->stop();
	QApplication::exit(0);
}

void MainWindowWidget::on_actionDisplayFrame_triggered()
{
	ui.actionDisplayDiff->setChecked(false);
	ui.actionDisplayNone->setChecked(false);
	ui.viewport->setMode(ViewportWidget::DisplayFrame);
}

void MainWindowWidget::on_actionDisplayDiff_triggered()
{
	ui.actionDisplayFrame->setChecked(false);
	ui.actionDisplayNone->setChecked(false);
	ui.viewport->setMode(ViewportWidget::DisplayDiff);
}

void MainWindowWidget::on_actionDisplayNone_triggered()
{
	ui.actionDisplayFrame->setChecked(false);
	ui.actionDisplayDiff->setChecked(false);
	ui.viewport->setMode(ViewportWidget::DisplayNone);
}

void MainWindowWidget::on_fpsBox_valueChanged(int value)
{
	//TODO:this->streamer->setFrameDelay(value);
}
