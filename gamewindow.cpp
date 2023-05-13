//
// Created by expli on 2023/5/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GameWindow.h" resolved

#include "gamewindow.h"
#include "ui_GameWindow.h"



GameWindow::GameWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::GameWindow) {
    this->backgroundPixmap = QPixmap("images/backgrounds/landscape/1.0KV-2560x1440.png");
    ui->setupUi(this);
}

GameWindow::~GameWindow() {
    delete ui;
}

void GameWindow::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(this->rect(), this->backgroundPixmap);
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            exit(0);
        default:
            QWidget::keyPressEvent(event);
    }
}
