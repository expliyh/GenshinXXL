//
// Created by expli on 2023/5/13.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GameWindow.h" resolved

#include "gamewindow.h"
#include "ui_GameWindow.h"


GameWindow::GameWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::GameWindow), entered(false) {
    QScreen *screen = QGuiApplication::primaryScreen();
    this->screenSize = screen->geometry().size();
    this->scaleRate = qobject_cast<QGuiApplication *>(QGuiApplication::instance())->devicePixelRatio();
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

void GameWindow::enterGame() {
    ui->labelStart->deleteLater();
    ui->labelTitle->deleteLater();
    int cwTop = int(0.1 * this->screenSize.height());
    int cwSide = this->screenSize.height() - cwTop - cwTop;
    int rowNum = 5;
    int columnNum = 5;
    int characterSide = cwSide / rowNum;
    auto *characterLayout = new QGridLayout;
    for (int n = 0; n < rowNum; n++) {
        for (int m = 0; m < columnNum; m++) {
            table_picture[n][m] = new QCharacter(this, n, m);
            table_picture[n][m]->setFixedSize(characterSide, characterSide);
//            table_picture[n][m]->setGeometry(240 + 216 * n, 216 * m, 216, 216);
//            table_picture[n][m]->resize(216, 216);
            QPixmap pix;
            pix.load("images/GenshinCharacter/AiErHaiSen.png");
            pix = pix.scaled(int(characterSide * this->scaleRate), int(characterSide * this->scaleRate),
                             Qt::KeepAspectRatio, Qt::SmoothTransformation);
            table_picture[n][m]->setPixmap(pix);
            connect(table_picture[n][m], &QCharacter::pressed, this, &GameWindow::characterPressed);
            characterLayout->addWidget(table_picture[n][m], n, m);
            //            table_picture[n][m]->show();
        }
    }
    auto *characterWidget = new QWidget(this);
    characterWidget->setGeometry(cwTop * 2, cwTop, cwSide, cwSide);
    characterWidget->setLayout(characterLayout);
    characterWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    ui->centralwidget->layout()->addWidget(characterWidget);
    characterWidget->show();
//    this->hide();
//    this->show();
    update();
}

void GameWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (!entered && event->button() == Qt::LeftButton) {
        enterGame();
        entered = true;
    } else {
        QWidget::mouseReleaseEvent(event);
    }
}

void GameWindow::characterPressed(int x, int y) {

}
