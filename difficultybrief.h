//
// Created by 34668 on 2023/5/17.
//

#ifndef LLKUI_DIFFICULTYBRIEF_H
#define LLKUI_DIFFICULTYBRIEF_H

#include <QWidget>
#include <QString>
#include <QKeyEvent>
#include <QEvent>
#include <QObject>
#include "QPainter"


QT_BEGIN_NAMESPACE
namespace Ui { class DifficultyBrief; }
QT_END_NAMESPACE

class DifficultyBrief : public QWidget {
Q_OBJECT

public:
    explicit DifficultyBrief(QWidget *parent = nullptr, int difficulty = 0);

    ~DifficultyBrief() override;

protected:
    void paintEvent(QPaintEvent *event) override;


private:
    Ui::DifficultyBrief *ui;
    int difficulty;

    void keyPressEvent(QKeyEvent *event) override;
};


#endif //LLKUI_DIFFICULTYBRIEF_H
