#include <QApplication>
#include <QScreen>

#include "layoutSwitcher.h"
#include "options.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    lSoptions::load();

    layoutSwitcher l;
   
    auto hotkey = new QHotkey(QKeySequence("ctrl+shift+space"), true, &app);//The hotkey will be automatically registered
	qDebug() << "Hotkey is Registered: " << hotkey->isRegistered();

	QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
		//qDebug() << "Hotkey Activated - the application will quit now";
		//qApp->quit();
		//Screenshot* screenshot = new Screenshot();
		l.activateNextLayout();
	});

    return app.exec();
}
