#include <QApplication>

#include "MainWindowWidget.h"
#include "Engine.h"
#include "QtEventMonitor.h"
#include "LockingTimer.h"
#include "DiffAlgorithm.h"
#include "Area.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	
	QtEventMonitor monitor;
	Engine engine;
	LockingTimer timer(engine);
	DiffAlgorithm alg(monitor);

	engine.setTimer(&timer);
	engine.setEventMonitor(&monitor);
	engine.setFrameDelay(50);

	MainWindowWidget mainWidget(engine);

	for (int i = 0; i < 9; ++i) {
		int group = i / 3 + 1;
		int id = i % 3 + 1;
		Area *area = new Area();
		area->setGroup(QString("G%1").arg(group));
		area->setName(QString("G%1A%2").arg(group).arg(id));
		alg.addArea(area);
		mainWidget.addArea(area);
	}

	mainWidget.setDiffAlgorithm(&alg);
	mainWidget.show();

	return app.exec();
}
