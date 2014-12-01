#include "MainWindowWidget.h"

#include "CameraFrameSource.h"
#include "FileFrameSource.h"
#include "Engine.h"
#include "DiffAlgorithm.h"

#include <QFileDialog>

#include <QDebug>

MainWindowWidget::MainWindowWidget(Engine &engine)
	: EventHandler(*engine.getEventMonitor()), engine(engine), algorithm(0), frameSource(0)
{
	ui.setupUi(this);

}

void MainWindowWidget::on_actionCamera_triggered()
{
	frameSource = new CameraFrameSource();
	engine.setSource(frameSource);
	engine.fetchFrame();
	ui.playButton->setChecked(false);
}

void MainWindowWidget::on_actionFile_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open movie");
	if (filename.isNull())
		return;
	frameSource = new FileFrameSource(filename);
	engine.setSource(frameSource);
	engine.fetchFrame();
	ui.playButton->setChecked(false);
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
}

void MainWindowWidget::handleNewDiffFrame(QSharedPointer<const Frame> framePtr)
{
	ui.viewport->updateDiffFrame(framePtr);
	updateAreaTiming();
	if (ui.playButton->isChecked())
		engine.schedule();
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

void MainWindowWidget::on_playButton_toggled(bool val)
{
	if (val)
		engine.schedule();
}

void MainWindowWidget::addArea(Area *area)
{
	areas << area;
	ui.viewport->addArea(area);
}

void MainWindowWidget::updateAreaTiming()
{
	if (!frameSource || !algorithm)
		return;

	float fps = frameSource->getFps();

	ui.g1a1Box->setValue(algorithm->getAreaTicks(areas[0]) / fps);
	ui.g1a2Box->setValue(algorithm->getAreaTicks(areas[1]) / fps);
	ui.g1a3Box->setValue(algorithm->getAreaTicks(areas[2]) / fps);

	ui.g2a1Box->setValue(algorithm->getAreaTicks(areas[3]) / fps);
	ui.g2a2Box->setValue(algorithm->getAreaTicks(areas[4]) / fps);
	ui.g2a3Box->setValue(algorithm->getAreaTicks(areas[5]) / fps);

	ui.g3a1Box->setValue(algorithm->getAreaTicks(areas[6]) / fps);
	ui.g3a2Box->setValue(algorithm->getAreaTicks(areas[7]) / fps);
	ui.g3a3Box->setValue(algorithm->getAreaTicks(areas[8]) / fps);
}
