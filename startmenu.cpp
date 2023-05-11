//
// Created by expli on 2023/5/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartMenu.h" resolved

#include "startmenu.h"
#include "ui_StartMenu.h"


StartMenu::StartMenu(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StartMenu) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize screenSize = screen->geometry().size();
    ui->setupUi(this);
    qDebug() << screenSize.width();
}

StartMenu::~StartMenu() {
    delete ui;
}
