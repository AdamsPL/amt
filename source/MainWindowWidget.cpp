#include "MainWindowWidget.h"

#include "Frame.h"
#include "FrameStreamer.h"
#include "CameraFrameSource.h"
#include "FileFrameSource.h"
#include "MovementDetector.h"

#include <QFileDialog>

#include <QDebug>

int iter = 0;

MainWindowWidget::MainWindowWidget()
{
	ui.setupUi(this);
	ui.graphicsView->setScene(&scene);

	scene.addItem(&streamItem);
	scene.addItem(&movementItem);
}

void MainWindowWidget::setFrameStreamer(FrameStreamer *streamer)
{
	this->streamer = streamer;
}

void MainWindowWidget::setMovementDetector(MovementDetector *detector)
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

void MainWindowWidget::onNewFrame(QSharedPointer<const Frame> ptr)
{
	QPixmap pixmap;
	pixmap.convertFromImage(ptr->getImg());
	streamItem.setPixmap(pixmap);
	ui.graphicsView->fitInView(&streamItem);
}

void MainWindowWidget::onMovementDetected(QSharedPointer<const Frame> ptr)
{
	QPixmap pixmap;
	pixmap.convertFromImage(ptr->getImg());
	movementItem.setPixmap(pixmap);
	//ui.graphicsView->fitInView(&movementItem);
}

void MainWindowWidget::connectComponents()
{
	connect(streamer, SIGNAL(frameReady(QSharedPointer<const Frame>)), this, SLOT(onNewFrame(QSharedPointer<const Frame>)));
	connect(detector, SIGNAL(movementDetected(QSharedPointer<const Frame>)), this, SLOT(onMovementDetected(QSharedPointer<const Frame>)));
	streamer->addListener(detector);
}
