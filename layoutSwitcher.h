 #ifndef SCREENSHOT_H
 #define SCREENSHOT_H

 #include <QWidget>
 #include <QPainter>
 #include <QKeyEvent>
 #include <QSystemTrayIcon>
 #include <QHotkey>
 #include <iostream>
 
 class QCheckBox;
 class QGridLayout;
 class QGroupBox;
 class QHBoxLayout;
 class QLabel;
 class QPushButton;
 class QSpinBox;
 class QVBoxLayout;

 class layoutSwitcher : public QWidget
 {
     Q_OBJECT

 public:
     layoutSwitcher();
     void on_show_hide();
     void activateNextLayout();
 protected:

 private slots:
     //void newScreenshot();
     void quit();
     void exit();
     void restart();
     void openOptions();
     void switchToLayout(unsigned int i);
     //void on_show_hide(QSystemTrayIcon::ActivationReason reason);
 private:
     unsigned int currentLayout;

     QSystemTrayIcon* trayIcon;

     QVBoxLayout *mainLayout;
     //QHBoxLayout *buttonsLayout;
 };

 #endif
