#include <QApplication>
#include <QScreen>

#include "layoutSwitcher.h"
#include "options.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if(auto r = lSoptions::load() != 0){
	    return r;
    }

    layoutSwitcher l;

    if(lSoptions::hotkey){
	    auto hotkey = new QHotkey(QKeySequence(QString(lSoptions::hotkey.value().c_str())), true, &app);//The hotkey will be automatically registered
	    qDebug() << "Hotkey is Registered: " << hotkey->isRegistered();
	    QObject::connect(hotkey, &QHotkey::activated, qApp, [&](){
			l.activateNextLayout();
		});
    }

    return app.exec();
}
