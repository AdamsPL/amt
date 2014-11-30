#include <QApplication>

#include "MainWindowWidget.h"
#include "Engine.h"
#include "QtEventMonitor.h"
#include "LockingTimer.h"
#include "DiffAlgorithm.h"

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
	mainWidget.show();

	return app.exec();
}
