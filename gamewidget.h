//
// Created by 34668 on 2023/5/21.
//

#ifndef LLKUI_GAMEWIDGET_H
#define LLKUI_GAMEWIDGET_H

#include <QWidget>
#include<QPainter>
#include<QTimer>
#include<QObject>
#include <QFile>
#include<QGridLayout>
#include<queue>
#include<vector>
#include<iostream>
#include <QPushButton>
#include "Themes.h"
#include "CountdownWidget.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE

class GameWidget : public QWidget {
Q_OBJECT

public:
    QPixmap *easyBackground;
    QPixmap *normalBackground;
    QPixmap *hardBackground;


public:
    explicit GameWidget(QWidget *parent = nullptr, int difficulty = 0);

    ~GameWidget() override;

    void born();

    int left(int row, int col);

    int right(int row, int col);

    int up(int row, int col);

    int down(int row, int col);

    bool judge(int row1, int col1, int row2, int col2, bool);

    void easyPosition();

    void normalPosition();

    void hardPosition();

    void drawLine(const int &row1, const int &col1, const int &row2, const int &col2, const int &row3, const int &col3);

    void checkButton(QPushButton *button);

    void uncheckButton(QPushButton *button, const QString &oldStyleSheet);


protected:
    void paintEvent(QPaintEvent *event) override;

    CountdownWidget *countdownWidget;

private:
    Ui::GameWidget *ui;
    int difficulty;
    queue<pair<int, int>> xy;
    queue<QPushButton *> firstButton;
    vector<vector<int>> position;
    QGridLayout *layout{};
    QPolygon polyline;
    int score;
    int winJudge;
    Theme theme;


signals:

    void getxy(int row, int col);

public slots:

    void Delete(int row, int col);

    void buttonClicked();

    void clearPolyline();

    void rearrange();

    void prompt();

private:
    void generate(QWidget *widget, QString &styleSheet);

    void reGenerate();
};


#endif //LLKUI_GAMEWIDGET_H
