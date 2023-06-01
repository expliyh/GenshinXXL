//
// Created by expli on 2023/5/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartMenu.h" resolved

#include <QAudioOutput>
#include "startmenu.h"
#include "ui_StartMenu.h"


StartMenu::StartMenu(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::StartMenu),
        diffcultySelected(false), difficulty(0) {
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
    QRect difficultyButtonRect = QRect(275, 600, 190, 55);
    ui->difficultyButton->setText("难度选择");
    ui->difficultyButton->setGeometry(difficultyButtonRect);
    connect(ui->difficultyButton, &QPushButton::clicked, this, &StartMenu::difficultySelect);

//    Set continue button
    QRect continueButtonRect = QRect(275, 700, 190, 55);
    ui->continueButton->setText("继续游戏");
    ui->continueButton->setGeometry(continueButtonRect);
    qDebug() << "Screen screenSize: " << screenSize.width() * this->scaleRate << 'x'
             << screenSize.height() * this->scaleRate;
    connect(ui->newGameButton, &QPushButton::clicked, this, &StartMenu::gameStart);
    this->levelMenu = new LevelMenu;
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
    this->game = new GameWindow;
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

void StartMenu::difficultySelect() {
    this->levelMenu->showFullScreen();
}

bool StartMenu::isDifficultySelected() {
    return this->diffcultySelected;
}

