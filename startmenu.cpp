//
// Created by expli on 2023/5/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartMenu.h" resolved

#include "startmenu.h"
#include "ui_StartMenu.h"


StartMenu::StartMenu(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StartMenu) {
    QScreen *screen = QGuiApplication::primaryScreen();
    this->screenSize = screen->geometry().size();
    QFont menuFont = QFont("HYWenHei-85W", 50);
    ui->setupUi(this);
    ui->title->setText("消消乐");
    ui->title->setFont(menuFont);
    ui->title->setStyleSheet("color:#ffffff;");
    auto titleRect = ui->title->rect();
    titleRect.setLeft(250);
    titleRect.setTop(200);
    titleRect.setWidth(200);
    titleRect.setHeight(70);
    ui->title->setGeometry(titleRect);
    qDebug() << "Screen screenSize: " << screenSize.width() << 'x' << screenSize.height();
    qDebug()
            << tr("If this screenSize doesn't match your screen screenSize, maybe you zoom your display. You don't need to fix it.");

}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap pixmap("./images/backgrounds/landscape/1.0KV-2560x1440.png");
    painter.drawPixmap(this->rect(), pixmap);
}
