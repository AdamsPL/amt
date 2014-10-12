#include "MainWindowWidget.h"

#include "Frame.h"
#include "FrameStreamer.h"
#include "CameraFrameSource.h"
#include "FileFrameSource.h"

#include <QFileDialog>

int iter = 0;

MainWindowWidget::MainWindowWidget(FrameStreamer *streamer)
	: streamer(streamer)
{
	ui.setupUi(this);
	connect(streamer, SIGNAL(frameReady(QSharedPointer<const Frame>)), this, SLOT(onNewFrame(QSharedPointer<const Frame>)));

	ui.graphicsView->setScene(&scene);
	scene.addItem(&item);
}

void MainWindowWidget::setFrameStreamer(FrameStreamer *streamer)
{
	this->streamer = streamer;
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
	item.setPixmap(pixmap);
}
