#include <QApplication>
#include <QPushButton>
#include "startmenu.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    StartMenu startMenu;
    startMenu.showFullScreen();
    a.exec();
}
