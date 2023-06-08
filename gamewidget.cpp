//
// Created by 34668 on 2023/5/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GameWidget.h" resolved


#include <QGridLayout>
#include <QPushButton>
#include <QFile>
#include <QPainter>
#include <random>
#include <QString>
#include <string>
#include "gamewidget.h"
#include "ui_GameWidget.h"


GameWidget::GameWidget(QWidget *parent, int difficulty) :
        QWidget(parent), ui(new Ui::GameWidget), difficulty(difficulty), score(0) {
    ui->setupUi(this);
    this->easyBackground = new QPixmap("images/backgrounds/landscape/1.0KV-2560x1440.png");
    this->normalBackground = new QPixmap("images/backgrounds/landscape/1.0KV-2560x1440.png");
    this->hardBackground = new QPixmap("images/backgrounds/landscape/1.0KV-2560x1440.png");
//    this->setFixedSize(1600, 900);
    this->theme = Theme();
    auto *rearrange = new QPushButton(this);
    auto *prompt = new QPushButton(this);
    QFile qssFile("startmenu.qss"); // 替换为你的QSS文件路径
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qssFile.readAll());
    qssFile.close();
    rearrange->setStyleSheet(styleSheet);
    prompt->setStyleSheet(styleSheet);
    rearrange->setText("重排");
    prompt->setText("提示");
    prompt->setGeometry(1300, 50, 100, 50);
    connect(prompt, &QPushButton::clicked, this, &GameWidget::prompt);
    rearrange->setGeometry(1300, 150, 100, 50);
    connect(rearrange, &QPushButton::clicked, this, &GameWidget::rearrange);
    prompt->show();
    rearrange->show();
    born();
    winJudge = position.size() * position.size();
    connect(this, &GameWidget::getxy, this, &GameWidget::Delete);

}

GameWidget::~GameWidget() {
    delete ui;
}

void GameWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    switch (this->difficulty) {
        case 0 : {
            painter.drawPixmap(rect(), *this->easyBackground);
            break;
        }
        case 1 : {
            painter.drawPixmap(rect(), *this->normalBackground);
            break;
        }
        case 2 : {
            painter.drawPixmap(rect(), *this->hardBackground);
            break;
        }
        default: {
            painter.drawPixmap(rect(), *this->easyBackground);
            break;
        }
    }
    painter.setPen(QPen(Qt::red, 4));
    painter.drawPolyline(polyline);
    QWidget::paintEvent(event);
}


void GameWidget::born() {
    auto *widget = new QWidget(this);
    layout = new QGridLayout(widget);
    QFile qssFile("gamewidget.qss");
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qssFile.readAll());
    qssFile.close();
    if (difficulty == 0) {
        position.resize(8, vector<int>(8));
        easyPosition();

        generate(widget, styleSheet);

        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setGeometry(200, 50, 800, 800);

    } else if (difficulty == 1) {
        position.resize(10, vector<int>(10));
        normalPosition();

        generate(widget, styleSheet);

        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setGeometry(200, 50, 800, 800);


    } else if (difficulty == 2) {
        position.resize(16, vector<int>(16));
        hardPosition();

        generate(widget, styleSheet);

        layout->setSpacing(0);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setGeometry(200, 50, 800, 800);


    }
}

void GameWidget::generate(QWidget *widget, QString &styleSheet) {
    for (int i = 0; i < position.size(); i++) {
        for (int j = 0; j < position[i].size(); j++) {
            auto *button = new QPushButton(widget);
            connect(button, &QPushButton::clicked, this, &GameWidget::buttonClicked);
            button->setFixedSize(800 / position.size(), 800 / position.size());
            auto size_hint = button->sizePolicy();
            size_hint.setRetainSizeWhenHidden(true);
            button->setSizePolicy(size_hint);

            auto &background = theme.characters_pixmap[position[i][j]];
            button->setIcon(QIcon(background.scaled(button->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation)));
            button->setIconSize(button->size());
            layout->addWidget(button, i, j);
        }
    }
}

void GameWidget::buttonClicked() {
    auto *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        if (layout) {
            int row, col, rowSpan, colSpan;
            layout->getItemPosition(layout->indexOf(button), &row, &col, &rowSpan, &colSpan);
            emit getxy(row, col);
        }
    }
}

void GameWidget::Delete(int row, int col) {
    QLayoutItem *item = layout->itemAtPosition(row, col);
    if (item) {
        if (QWidget *widget = item->widget()) {
            auto *button = qobject_cast<QPushButton *>(widget);
            if (xy.empty()) {
                xy.emplace(row, col);
                firstButton.emplace(button);
                button->setEnabled(false);
            } else {
                if (judge(xy.front().first, xy.front().second, row, col)) {
                    position[xy.front().first][xy.front().second] = -1;
                    position[row][col] = -1;
                    firstButton.front()->hide();
                    button->hide();
                    firstButton.pop();
                    xy.pop();
                    if (difficulty == 0)score += 50;
                    if (difficulty == 1)score += 75;
                    if (difficulty == 2)score += 100;
                    winJudge--;
                    if (winJudge == 0) {

                    }
                } else {
                    xy.pop();
                    firstButton.front()->setEnabled(true);
                    firstButton.pop();
                    button->setEnabled(false);
                    firstButton.emplace(button);
                    xy.emplace(row, col);
                }
            }
        }
    }
}

int GameWidget::up(int row, int col) {
    if (row == 0) return -1;
    else {
        int n = 0;
        for (int i = row;;) {
            if (position[--i][col] < 0) n--;
            else break;
            if (i == 0) {
                n--;
                break;
            }
        }
        return n;
    }
}

int GameWidget::down(int row, int col) {
    if (row == position.size() - 1) return 1;
    else {
        int n = 0;
        for (int i = row;;) {
            if (position[++i][col] < 0) n++;
            else break;
            if (i == position.size() - 1) {
                n++;
                break;
            }
        }
        return n;
    }
}

int GameWidget::left(int row, int col) {
    if (col == 0) return -1;
    else {
        int n = 0;
        for (int i = col;;) {
            if (position[row][--i] < 0) n--;
            else break;
            if (i == 0) {
                n--;
                break;
            }
        }
        return n;
    }
}

int GameWidget::right(int row, int col) {
    if (col == position.size() - 1) return 1;
    else {
        int n = 0;
        for (int i = col;;) {
            if (position[row][++i] < 0) n++;
            else break;
            if (i == position.size() - 1) {
                n++;
                break;
            }
        }
        return n;
    }
}

bool GameWidget::judge(int row1, int col1, int row2, int col2) {
    if (row1 == row2 && col1 == col2) return false;
    else if (position[row1][col1] != position[row2][col2]) return false;
    else if (row1 == row2 && abs(col1 - col2) == 1) {
        drawLine(row1, col1, row2, col2, row2, col2);
        return true;
    } else if (col1 == col2 && abs(row1 - row2) == 1) {
        drawLine(row1, col1, row2, col2, row2, col2);
        return true;
    } else {
        int right1 = right(row1, col1);
        int right2 = right(row2, col2);
        int left1 = left(row1, col1);
        int left2 = left(row2, col2);
        int down1 = down(row1, col1);
        int down2 = down(row2, col2);
        int up1 = up(row1, col1);
        int up2 = up(row2, col2);
        for (int i = (row1 + down1); i >= (row1 + up1); i--) {
            for (int j = (row2 + down2); j >= (row2 + up2); j--) {
                if (i == j) {
                    if (i == -1 || i == position.size()) {
                        drawLine(i, col1, i, col2, row2, col2);
                        return true;
                    }
                    int t = 0;
                    int s = col1 < col2 ? col1 : col2;
                    for (int k = abs(col1 - col2) - 1; k >= 1; k--) {
                        if (position[i][s + k] >= 0) {
                            t++;
                            break;
                        }
                    }
                    if (t == 0) {
                        drawLine(i, col1, i, col2, row2, col2);
                        return true;
                    }
                }
            }
        }
        for (int i = (col1 + right1); i >= (col1 + left1); i--) {
            for (int j = (col2 + right2); j >= (col2 + left2); j--) {
                if (i == j) {
                    if (i == -1 || i == position.size()) {
                        drawLine(row1, i, row2, i, row2, col2);
                        return true;
                    }
                    int t = 0;
                    int s = row1 < row2 ? row1 : row2;
                    for (int k = abs(row1 - row2) - 1; k >= 1; k--) {
                        if (position[s + k][i] != 0) {
                            t++;
                            break;
                        }
                    }
                    if (t == 0) {
                        drawLine(row1, i, row2, i, row2, col2);
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

void GameWidget::easyPosition() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            position[i][j] = j;
        }
    }

    random_device rd;
    mt19937 engine(rd());
    for (int i = 0; i < 8; i++) {
        shuffle(position[i].begin(), position[i].end(), engine);
    }
}

void GameWidget::normalPosition() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            position[i][j] = j;
        }
    }

    random_device rd;
    mt19937 engine(rd());
    for (int i = 0; i < 10; i++) {
        shuffle(position[i].begin(), position[i].end(), engine);
    }
}

void GameWidget::hardPosition() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            position[i][j] = j;
        }
    }

    random_device rd;
    mt19937 engine(rd());
    for (int i = 0; i < 16; i++) {
        shuffle(position[i].begin(), position[i].end(), engine);
    }
}

void GameWidget::drawLine(const int &row1, const int &col1, const int &row2, const int &col2, const int &row3,
                          const int &col3) {
    if (difficulty == 0) {
        int pictureSize = 100;
        polyline << QPoint((xy.front().second + 0.5) * pictureSize + 200, (xy.front().first + 0.5) * pictureSize + 50)
                 << QPoint((col1 + 0.5) * pictureSize + 200, (row1 + 0.5) * pictureSize + 50)
                 << QPoint((col2 + 0.5) * pictureSize + 200, (row2 + 0.5) * pictureSize + 50)
                 << QPoint((col3 + 0.5) * pictureSize + 200, (row3 + 0.5) * pictureSize + 50);
        update();
    } else if (difficulty == 1) {
        int pictureSize = 80;
        polyline << QPoint((xy.front().second + 0.5) * pictureSize + 200, (xy.front().first + 0.5) * pictureSize + 50)
                 << QPoint((col1 + 0.5) * pictureSize + 200, (row1 + 0.5) * pictureSize + 50)
                 << QPoint((col2 + 0.5) * pictureSize + 200, (row2 + 0.5) * pictureSize + 50)
                 << QPoint((col3 + 0.5) * pictureSize + 200, (row3 + 0.5) * pictureSize + 50);
        update();
    } else if (difficulty == 2) {
        int pictureSize = 50;
        polyline << QPoint((xy.front().second + 0.5) * pictureSize + 200, (xy.front().first + 0.5) * pictureSize + 50)
                 << QPoint((col1 + 0.5) * pictureSize + 200, (row1 + 0.5) * pictureSize + 50)
                 << QPoint((col2 + 0.5) * pictureSize + 200, (row2 + 0.5) * pictureSize + 50)
                 << QPoint((col3 + 0.5) * pictureSize + 200, (row3 + 0.5) * pictureSize + 50);
        update();
    }
    auto *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(clearPolyline()));
    timer->setSingleShot(true);
    timer->start(500);
}

void GameWidget::clearPolyline() {
    polyline.clear();
    update();
}

void GameWidget::rearrange() {
    random_device rd;
    mt19937 engine(rd());
    for (auto &i: position) {
        shuffle(i.begin(), i.end(), engine);
    }
    reGenerate();
}

void GameWidget::prompt() {
    for (int i = 0; i < position.size(); i++) {
        for (int j = 0; j < position.size(); j++) {
            if (position[i][j] >= 0) {
                if (j == position.size() - 1 && i != position.size() - 1) {
                    for (int s = i + 1; s < position.size(); s++) {
                        for (int t = 0; t < position.size(); t++) {
                            if (judge(i, j, s, t)) {
                                auto *item1 = layout->itemAtPosition(i, j);
                                auto *item2 = layout->itemAtPosition(s, t);
                                auto *button1 = qobject_cast<QPushButton *>(item1->widget());
                                auto *button2 = qobject_cast<QPushButton *>(item2->widget());
                                button1->setChecked(true);
                                button2->setChecked(true);
                                return;
                            }
                        }
                    }
                } else if (j != position.size() - 1) {
                    int o = 0;
                    for (int s = i; s < position.size(); s++) {
                        if (o == 0) {
                            for (int t = j + 1; t < position.size(); t++) {
                                if (judge(i, j, s, t)) {
                                    auto *item1 = layout->itemAtPosition(i, j);
                                    auto *item2 = layout->itemAtPosition(s, t);
                                    auto *button1 = qobject_cast<QPushButton *>(item1->widget());
                                    auto *button2 = qobject_cast<QPushButton *>(item2->widget());
                                    button1->setChecked(true);
                                    button2->setChecked(true);
                                    return;
                                }
                            }
                            o++;
                        } else {
                            for (int t = 0; t < position.size(); t++) {
                                if (judge(i, j, s, t)) {
                                    auto *item1 = layout->itemAtPosition(i, j);
                                    auto *item2 = layout->itemAtPosition(s, t);
                                    auto *button1 = qobject_cast<QPushButton *>(item1->widget());
                                    auto *button2 = qobject_cast<QPushButton *>(item2->widget());
                                    button1->setChecked(true);
                                    button2->setChecked(true);
                                    return;
                                }
                            }
                        }
                    }
                } else if (j == position.size() - 1 && i == position.size() - 1) {
                    return;
                }
            }
        }
    }
}

void GameWidget::reGenerate() {
    for (int i = 0; i < position.size(); i++) {
        for (int j = 0; j < position.size(); j++) {
            auto *item = layout->itemAtPosition(i, j);
            if (item) {
                auto *button = qobject_cast<QPushButton *>(item->widget());
                if (position[i][j] < 0) {
                    button->hide();
                } else {
                    auto &button_background = theme.characters_pixmap[position[i][j]];
                    button->setIcon(
                            button_background.scaled(button->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    button->setIconSize(button->size());
                    button->setEnabled(true);
                    button->show();
                }
            }
        }
    }
}




