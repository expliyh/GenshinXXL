//
// Created by expli on 2023/5/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartMenu.h" resolved

#include <QAudioOutput>
#include <exception>
#include "startmenu.h"
#include "ui_StartMenu.h"


StartMenu::StartMenu(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StartMenu), difficulty(0) {
    this->diffcultySelected = 0;
    this->audioOutput = new QAudioOutput;
    this->player = new QMediaPlayer;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("musics/Take the Journey.mp3"));
    player->play();
    this->game = nullptr;
    QFile qssFile("startmenu.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        this->setStyleSheet(qssFile.readAll());
    } else {
        qDebug() << "CSS Load Failed!";
    }
    QScreen *screen = QGuiApplication::primaryScreen();
    this->screenSize = screen->geometry().size();
    auto *qApplication = qobject_cast<QGuiApplication *>(QGuiApplication::instance());
    this->scaleRate = qApplication->devicePixelRatio();
    qDebug() << screen->physicalDotsPerInch();
    QFont menuFont = QFont("HYWenHei-85W", 60);
//    QFont buttonFont = QFont("HYWenHei-85W", 40);
    QString back_path = "./images/backgrounds/landscape/1.0KV-2560x1440.png";
    this->backgroundImage = QImage(back_path).scaled(this->screenSize * this->scaleRate, Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation);
    this->backgroundPixmap = QPixmap(back_path).scaled(
            this->screenSize * this->scaleRate, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->setupUi(this);
//    Set title.
    ui->title->setText("消消乐");
    ui->title->setFont(menuFont);
    ui->title->setStyleSheet("color:#ffffff;");
    auto titleRect = ui->title->rect();
    titleRect.setLeft(250);
    titleRect.setTop(200);
    titleRect.setWidth(250);
    titleRect.setHeight(100);
    ui->title->setGeometry(titleRect);
//    Set new game button
    auto buttonBlurEffect = new QGraphicsBlurEffect;
    buttonBlurEffect->setBlurRadius(55);
    buttonBlurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
    QRect newGameButtonRect = QRect(275, 500, 190, 55);
    if (this->game == nullptr) {
        ui->newGameButton->setText("新游戏");
    } else {
        ui->newGameButton->setText("继续游戏");
    }
    ui->newGameButton->setGeometry(newGameButtonRect);
//    Set difficulty button
//    QRect difficultyButtonRect = QRect(275, 600, 190, 55);
    ui->buttonEasy->setText("简单");
    ui->buttonNormal->setText("普通");
    ui->buttonHard->setText("困难");
    ui->buttonCustomize->setText("自定义");
    ui->buttonEasy->setGeometry(275, 570, 90, 55);
    ui->buttonNormal->setGeometry(375, 570, 90, 55);
    ui->buttonHard->setGeometry(275, 630, 90, 55);
    ui->buttonCustomize->setGeometry(375, 630, 90, 55);
    ui->newGameButton->setEnabled(false);
    connect(ui->buttonEasy, &QPushButton::clicked, this, &StartMenu::on_buttonEasy_clicked);
    connect(ui->buttonNormal, &QPushButton::clicked, this, &StartMenu::on_buttonNormal_clicked);
    connect(ui->buttonHard, &QPushButton::clicked, this, &StartMenu::on_buttonHard_clicked);
    connect(ui->buttonCustomize, &QPushButton::clicked, this, &StartMenu::on_buttonCustomize_clicked);


//    Set continue button
    QRect continueButtonRect = QRect(275, 700, 190, 55);
    ui->continueButton->setText("继续游戏");
    ui->continueButton->setGeometry(continueButtonRect);
    qDebug() << "Screen screenSize: " << screenSize.width() * this->scaleRate << 'x'
             << screenSize.height() * this->scaleRate;
    connect(ui->newGameButton, &QPushButton::clicked, this, &StartMenu::gameStart);
}

StartMenu::~StartMenu() {
    delete ui;
}

void StartMenu::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(this->rect(), this->backgroundPixmap);
}

void StartMenu::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            exit(0);
        default:
            QWidget::keyPressEvent(event);
    }
}

void StartMenu::gameStart() {
    qDebug() << "Success";
    delete this->game;
    this->game = new GameWidget(nullptr, this->difficulty);
    game->showFullScreen();
    player->stop();
    this->hide();
}

int StartMenu::getDifficulty() const {
    return difficulty;
}

void StartMenu::setDifficulty(int difficulty) {
    StartMenu::difficulty = difficulty;
}

void StartMenu::on_buttonEasy_clicked() {
    ui->buttonEasy->setEnabled(false);
    ui->buttonNormal->setEnabled(true);
    ui->buttonHard->setEnabled(true);
    ui->buttonCustomize->setEnabled(true);
    ui->newGameButton->setEnabled(true);
    this->setDifficulty(0);
}

void StartMenu::on_buttonNormal_clicked() {
    ui->buttonEasy->setEnabled(true);
    ui->buttonNormal->setEnabled(false);
    ui->buttonHard->setEnabled(true);
    ui->buttonCustomize->setEnabled(true);
    ui->newGameButton->setEnabled(true);
    this->setDifficulty(1);
}

void StartMenu::on_buttonHard_clicked() {
    ui->buttonEasy->setEnabled(true);
    ui->buttonNormal->setEnabled(true);
    ui->buttonHard->setEnabled(false);
    ui->buttonCustomize->setEnabled(true);
    ui->newGameButton->setEnabled(true);
    this->setDifficulty(2);
}

void StartMenu::on_buttonCustomize_clicked() {
    ui->buttonEasy->setEnabled(true);
    ui->buttonNormal->setEnabled(true);
    ui->buttonHard->setEnabled(true);
    ui->buttonCustomize->setEnabled(false);
    ui->newGameButton->setEnabled(true);
}

