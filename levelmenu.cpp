//
// Created by 34668 on 2023/5/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LevelMenu.h" resolved

#include <QFile>
#include "startmenu.h"
#include "levelmenu.h"
#include "ui_LevelMenu.h"

#include "QPushButtonWithHoverSignal.h"

#define EASY 0
#define NORMAL 1
#define HARD 2


LevelMenu::LevelMenu(QWidget *parent) :
        QWidget(parent), ui(new Ui::LevelMenu), difficultyBrief(nullptr) {
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFocusPolicy(Qt::StrongFocus);
    this->easyBack = new QPixmap("background/c.png");
    this->normalBack = new QPixmap("background/d.png");
    this->hardBack = new QPixmap("background/e.png");
    ui->setupUi(this);
    this->setFixedSize(1600, 900);
    QFile qssFile("startmenu.qss"); // 替换为你的QSS文件路径
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qssFile.readAll());
    qssFile.close();
    ui->title->setStyleSheet(styleSheet);
    auto *easyButton = new QPushButtonWithHoverSignal(this, EASY);
    easyButton->setObjectName("easyButton");
    easyButton->setStyleSheet(styleSheet);
    easyButton->setGeometry(150, 330, 101, 41);
    easyButton->setText("简单");
    connect(easyButton, &QPushButtonWithHoverSignal::mouseEntered, this, &LevelMenu::showBrief);
    connect(easyButton, &QPushButtonWithHoverSignal::mouseLeft, this, &LevelMenu::hideBrief);
    connect(easyButton, &QPushButton::clicked, this, &LevelMenu::easyClicked);
    auto *normalButton = new QPushButtonWithHoverSignal(this, NORMAL);
    normalButton->setStyleSheet(styleSheet);
    normalButton->setObjectName("normalButton");
    normalButton->setGeometry(150, 450, 101, 41);
    normalButton->setText("普通");
    connect(normalButton, &QPushButtonWithHoverSignal::mouseEntered, this, &LevelMenu::showBrief);
    connect(normalButton, &QPushButtonWithHoverSignal::mouseLeft, this, &LevelMenu::hideBrief);
    connect(normalButton, &QPushButton::clicked, this, &LevelMenu::normalClicked);
    auto *hardButton = new QPushButtonWithHoverSignal(this, HARD);
    hardButton->setStyleSheet(styleSheet);
    hardButton->setObjectName("hardButton");
    hardButton->setGeometry(150, 570, 101, 41);
    hardButton->setText("困难");
    connect(hardButton, &QPushButtonWithHoverSignal::mouseEntered, this, &LevelMenu::showBrief);
    connect(hardButton, &QPushButtonWithHoverSignal::mouseLeft, this, &LevelMenu::hideBrief);
    connect(hardButton, &QPushButton::clicked, this, &LevelMenu::hardClicked);
    auto *backToStart = new QPushButton("返回", this);
    backToStart->setStyleSheet(styleSheet);
    backToStart->setObjectName("backToStart");
    backToStart->setGeometry(150, 690, 101, 41);
    connect(backToStart, &QPushButton::clicked, this, &LevelMenu::backToStart);
    easyButton->show();
    normalButton->show();
    hardButton->show();
    backToStart->show();
    auto *startMenu = qobject_cast<StartMenu *>(parent);
    if (startMenu->isDifficultySelected()) {
        switch (startMenu->getDifficulty()) {
            case EASY:
                easyButton->setEnabled(false);
                break;
            case NORMAL:
                normalButton->setEnabled(false);
                break;
            case HARD:
                hardButton->setEnabled(false);
                break;
            default:
                break;
        }
    }

}

LevelMenu::~LevelMenu() {
    delete ui;
}

void LevelMenu::showBrief(int difficulty) {
    this->difficultyBrief = new DifficultyBrief(this, difficulty);
    this->difficultyBrief->setGeometry(470, 160, 1000, 600);
    this->difficultyBrief->show();

    update();
}

void LevelMenu::hideBrief(int difficulty) {
    this->difficultyBrief->hide();
    delete this->difficultyBrief;
}

void LevelMenu::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            this->hide();
            this->deleteLater();
        default:
            QWidget::keyPressEvent(event);
    }
}

void LevelMenu::changeButtonStatus(int difficulty) {
    switch (difficulty) {
        case EASY: {
            QPushButtonWithHoverSignal *button = this->findChild<QPushButtonWithHoverSignal *>("easyButton");
            if (button) {
                button->setEnabled(false);
            }
            button = this->findChild<QPushButtonWithHoverSignal *>("normalButton");
            if (button) {
                button->setEnabled(true);
            }
            button = this->findChild<QPushButtonWithHoverSignal *>("hardButton");
            if (button) {
                button->setEnabled(true);
            }
            break;
        }
        case NORMAL: {
            QPushButtonWithHoverSignal *button = this->findChild<QPushButtonWithHoverSignal *>("easyButton");
            if (button) {
                button->setEnabled(true);
            }
            button = this->findChild<QPushButtonWithHoverSignal *>("normalButton");
            if (button) {
                button->setEnabled(false);
            }
            button = this->findChild<QPushButtonWithHoverSignal *>("hardButton");
            if (button) {
                button->setEnabled(true);
            }
            break;
        }
        case HARD: {
            auto *button = this->findChild<QPushButtonWithHoverSignal *>("easyButton");
            if (button) {
                button->setEnabled(true);
            }
            button = this->findChild<QPushButtonWithHoverSignal *>("normalButton");
            if (button) {
                button->setEnabled(true);
            }
            button = this->findChild<QPushButtonWithHoverSignal *>("hardButton");
            if (button) {
                button->setEnabled(false);
            }
            break;
        }
        default:
            break;
    }
    this->setFocus();
}

void LevelMenu::easyClicked() {
    this->changeButtonStatus(EASY);
    this->setFocus();
    emit LevelMenu::difficultySelected(EASY);
}

void LevelMenu::normalClicked() {
    this->changeButtonStatus(NORMAL);
    this->setFocus();
    emit LevelMenu::difficultySelected(NORMAL);
}

void LevelMenu::hardClicked() {
    this->changeButtonStatus(HARD);
    this->setFocus();
    emit LevelMenu::difficultySelected(HARD);
}

void LevelMenu::backToStart() {
    this->hide();
//    this->deleteLater();
}

void LevelMenu::paintEvent(QPaintEvent *event) {

    {
        QPainter painter(this);
        QPixmap backgroundImage("background/b.png"); // 替换为您的背景图片路径

        painter.drawPixmap(rect(), backgroundImage);
    }
    QWidget::paintEvent(event);
}

