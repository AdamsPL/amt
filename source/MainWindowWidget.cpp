#include "MainWindowWidget.h"

#include "CameraFrameSource.h"
#include "FileFrameSource.h"
#include "Engine.h"

#include <QFileDialog>

#include <QDebug>

MainWindowWidget::MainWindowWidget(Engine &engine)
	: EventHandler(*engine.getEventMonitor()), engine(engine)
{
	ui.setupUi(this);

	int size = 9;
	for (int i = 0; i < size; ++i) {
		Area *area = new Area();
		areas << area;
		ui.viewport->addArea(area);
	}

}

void MainWindowWidget::on_actionCamera_triggered()
{
	FrameSource *src = new CameraFrameSource();
	engine.setSource(src);
	engine.schedule();
}

void MainWindowWidget::on_actionFile_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open movie");
	if (filename.isNull())
		return;
	FrameSource *src = new FileFrameSource(filename);
	engine.setSource(src);
	engine.schedule();
}

void MainWindowWidget::on_actionExit_triggered()
{
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
	engine.setFrameDelay(value);
}

void MainWindowWidget::handleNewFrame(QSharedPointer<const Frame> framePtr)
{
	ui.viewport->updateFrame(framePtr);
	engine.schedule();
}

void MainWindowWidget::handleNewDiffFrame(QSharedPointer<const Frame> framePtr)
{
	ui.viewport->updateDiffFrame(framePtr);
}

void MainWindowWidget::on_areaSelectBox_activated(int index)
{
	Area *area;

	if (index <= 0 || index > areas.size())
		area = 0;
	else
		area = areas[index - 1];

	ui.viewport->selectArea(area);
}

void MainWindowWidget::on_areaClearButton_clicked()
{
	ui.viewport->clearSelectedArea();
}
