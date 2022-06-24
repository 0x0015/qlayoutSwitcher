#include <QtWidgets>
#include <QApplication>
#include <QProcess>
#include <QDesktopServices>
#include "layoutSwitcher.h"
#include "SimpleCppTextFileHandler/file.hpp"
#include "options.hpp"

layoutSwitcher::layoutSwitcher()
{
    //setStyleSheet("background:transparent;");
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setWindowFlags(Qt::FramelessWindowHint);
    
    trayIcon = new QSystemTrayIcon(QIcon(":/Icon.png"), this);

    //connect( trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_show_hide(QSystemTrayIcon::ActivationReason)) );

    QAction *quit_action = new QAction( "Exit", trayIcon );
    connect( quit_action, SIGNAL(triggered()), this, SLOT(exit()) );

    QAction *restart_action = new QAction( "Restart", trayIcon );
    connect( restart_action, SIGNAL(triggered()), this, SLOT(restart()) );

    QAction *hide_action = new QAction( "Show/Hide Options", trayIcon );
    connect( hide_action, SIGNAL(triggered()), this, SLOT(openOptions()) );

    std::vector<QAction*> switch_actions;
    for(unsigned int i=0;i<lSoptions::layouts.size();i++){
	    const auto& o = lSoptions::layouts[i];
	    QAction *switch_action = new QAction(("Activate " + o.first).c_str() , trayIcon );
	    connect( switch_action, &QAction::triggered, this, [this, i]{switchToLayout(i);});
	    switch_actions.push_back(switch_action);
    }

    QMenu *tray_icon_menu = new QMenu;

    for(auto& o : switch_actions){
	    tray_icon_menu->addAction(o);
    }

    tray_icon_menu->addAction( hide_action );
    tray_icon_menu->addAction( restart_action );
    tray_icon_menu->addAction( quit_action );


    trayIcon->setContextMenu( tray_icon_menu );

    trayIcon->show();

    hide();

    switchToLayout(0);
}




void layoutSwitcher::quit(){
	//exit(0);
	showNormal();
	hide();
	//QTimer::singleShot(1250, this, SLOT(hide()));
	//showMinimized();
	//this->close();
}

void layoutSwitcher::exit(){
	QApplication::quit();
}

void layoutSwitcher::restart(){
	qApp->quit();
	QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void layoutSwitcher::on_show_hide(){
	if(isVisible()){
		hide();
	}else{
		show();
	}
}


void layoutSwitcher::activateNextLayout(){
	unsigned int nextLayout = currentLayout + 1;
	if(nextLayout >= lSoptions::layouts.size()){
		nextLayout = 0;
	}
	switchToLayout(nextLayout);
}

void layoutSwitcher::openOptions(){
	std::filesystem::path p = lSoptions::filename;
	std::string absPath = std::filesystem::absolute(p).string();
	QDesktopServices::openUrl(QUrl(absPath.c_str(), QUrl::TolerantMode));
}

void layoutSwitcher::switchToLayout(unsigned int i){
	if(i >= lSoptions::layouts.size()){
		return;
	}
	//std::cout<<"Running: "<<lSoptions::baseCommand<<" with arguments: "<<lSoptions::layouts[i].second<<std::endl;
	std::string command = lSoptions::baseCommand + " " + lSoptions::layouts[i].second;
	std::cout<<"Running: \""<<command<<"\""<<std::endl;
	//int result = QProcess::execute(QString(lSoptions::baseCommand.c_str()), QStringList(QString(lSoptions::layouts[i].second.c_str())));
	int result = system(command.c_str());//definitely objectively worse, but definitely simpler
	if(result != 0){
		std::cout<<"ERROR: Layout switch failed with error code: "<<result<<std::endl;
	}
	currentLayout = i;
}
