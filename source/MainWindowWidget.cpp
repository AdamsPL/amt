#include "MainWindowWidget.h"

#include "CameraFrameSource.h"
#include "FileFrameSource.h"
#include "Engine.h"

#include <QFileDialog>

#include <QDebug>

MainWindowWidget::MainWindowWidget(Engine &engine)
	: engine(engine)
{
	ui.setupUi(this);
}

void MainWindowWidget::on_actionCamera_triggered()
{
	engine.setSource(new CameraFrameSource());
	engine.iterate();
}

void MainWindowWidget::on_actionFile_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open movie");
	if (filename.isNull())
		return;
	engine.setSource(new FileFrameSource(filename));
	engine.iterate();
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
