//
// Created by 34668 on 2023/5/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DifficultyBrief.h" resolved

#include <QPushButton>
#include "difficultybrief.h"
#include "ui_DifficultyBrief.h"
#include "levelmenu.h"


#define EASY 0
#define NORMAL 1
#define HARD 2

DifficultyBrief::DifficultyBrief(QWidget *parent, int difficulty) :
        QWidget(parent), ui(new Ui::DifficultyBrief), difficulty(difficulty) {

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    this->setFocusPolicy(Qt::NoFocus);
}

DifficultyBrief::~DifficultyBrief() {
    delete ui;
}

void DifficultyBrief::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    auto *father = qobject_cast<LevelMenu *>(parent());
    QPainter painter(this);
    QFont font("HYWenHei-85W", 20, QFont::Bold);
    painter.setFont(font);
    painter.setPen(Qt::yellow);
    switch (this->difficulty) {
        case EASY: {
            painter.drawPixmap(rect(), *father->easyBack);
            QPixmap overlay("briefimage/EASY.png");
            painter.drawPixmap(0, 450, 300, 150, overlay);
            painter.drawText(rect(), Qt::AlignCenter, "哦，看来你选择了简单难度。这对我来说就像是小菜一碟。\n"
                                                      "你确定你能在这个级别上展现你的实力吗？\n"
                                                      "如果你准备好了，那就让我们开始吧。\n"
                                                      "希望你不会轻易地就放弃。\n");
            break;
        }
        case NORMAL: {
            painter.drawPixmap(rect(), *father->normalBack);
            QPixmap overlay("briefimage/NORMAL.png");
            painter.drawPixmap(0, 450, 300, 150, overlay);
            painter.drawText(rect(), Qt::AlignCenter, "你选择了普通难度，这是一个均衡的选择，既有挑战，又不会过于困难。\n"
                                                      "这个难度设定适合大多数玩家，你将面临一些考验.\n"
                                                      "这将是一个不错的游戏体验，希望你能享受这个过程。让我们开始吧。\n");
            break;
        }
        case HARD: {
            painter.drawPixmap(rect(), *father->hardBack);
            QPixmap overlay("briefimage/HARD.png");
            painter.drawPixmap(0, 450, 300, 150, overlay);
            painter.drawText(rect(), Qt::AlignCenter, "难度困难？哇，你是一个喜欢挑战极限的勇者！\n"
                                                      "这个级别的挑战将会超出你的想象，可能会让你感到灰心，甚至想要放弃。\n"
                                                      "你已经做好准备了吗？\n"
                                                      "让我们一起跃入深渊，看看你能否挑战成功，成为真正的游戏大师。\n");
            break;
        }
        default:
            painter.drawPixmap(rect(), *father->normalBack);
            painter.drawText(rect(), Qt::AlignCenter, "你选择了普通难度，这是一个均衡的选择，既有挑战，又不会过于困难。\n"
                                                      "这个难度设定适合大多数玩家，你将面临一些考验，但是只要你有恒心和策略，应该能够顺利通关。\n"
                                                      "这将是一个不错的游戏体验，希望你能享受这个过程。让我们开始吧。\n");
            break;
    }

}

void DifficultyBrief::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            qobject_cast<LevelMenu *>(parent())->hide();
            qobject_cast<LevelMenu *>(parent())->deleteLater();
        default:
            QWidget::keyPressEvent(event);
    }
}
