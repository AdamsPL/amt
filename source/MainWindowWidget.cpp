#include "MainWindowWidget.h"

#include "FrameStreamer.h"
#include "CameraFrameSource.h"
#include "FileFrameSource.h"
#include "FrameMovementExtractor.h"

#include <QFileDialog>

#include <QDebug>

MainWindowWidget::MainWindowWidget()
{
	ui.setupUi(this);
}

void MainWindowWidget::setFrameStreamer(FrameStreamer *streamer)
{
	this->streamer = streamer;
	on_fpsBox_valueChanged(ui.fpsBox->value());
}

void MainWindowWidget::setFrameMovementExtractor(FrameMovementExtractor *detector)
{
	this->detector = detector;
}

void MainWindowWidget::on_actionCamera_triggered()
{
	streamer->stopStreaming();
	streamer->setFrameSource(new CameraFrameSource());
	streamer->startStreaming();
}

void MainWindowWidget::on_actionFile_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open movie");
	if (filename.isNull())
		return;
	streamer->stopStreaming();
	streamer->setFrameSource(new FileFrameSource(filename));
	streamer->startStreaming();
}

void MainWindowWidget::on_actionExit_triggered()
{
	streamer->stopStreaming();
	QApplication::exit(0);
}

void MainWindowWidget::connectComponents()
{
	connect(streamer, SIGNAL(frameReady(QSharedPointer<const Frame>)), ui.viewport, SLOT(onNewFrame(QSharedPointer<const Frame>)));
	connect(detector, SIGNAL(movementDetected(QSharedPointer<const Frame>)), ui.viewport, SLOT(onMovementDetected(QSharedPointer<const Frame>)));
	streamer->addListener(detector);
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
	this->streamer->setFrameDelay(value);
}
