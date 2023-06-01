//
// Created by 34668 on 2023/5/17.
//

#ifndef LLKUI_LEVELMENU_H
#define LLKUI_LEVELMENU_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include "difficultybrief.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LevelMenu; }
QT_END_NAMESPACE

class LevelMenu : public QWidget {
Q_OBJECT

public:
    explicit LevelMenu(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    QPixmap *easyBack;
    QPixmap *normalBack;
    QPixmap *hardBack;

    void changeButtonStatus(int difficulty);

    ~LevelMenu() override;


public slots:

    void showBrief(int difficulty);

    void hideBrief(int difficulty);

    void easyClicked();

    void normalClicked();

    void hardClicked();

    void backToStart();

signals:

    void difficultySelected(int difficulty);


protected:
//    void hideEvent(QHideEvent *event) override {
//        // 子窗口关闭事件的处理
//        // ...
//
//        // 关闭子窗口
//        QWidget::hideEvent(event);
//
//        //更新父窗口
//        auto *startMenu= qobject_cast<StartMenu*>(parent());
//        startMenu->updateLabel(startMenu->getDifficulty());
//
//    }

    void showEvent(QShowEvent *event) override {
        // 子窗口展示事件的处理
        // ...

        // 获取父窗口的左上角全局坐标
//        QPoint parentTopLeftGlobal = parentWidget()->mapToGlobal(QPoint(0, 0));
//
//        // 将全局坐标转换为子窗口的局部坐标
//        QPoint parentTopLeftLocal = mapFromGlobal(parentTopLeftGlobal);
//
//        // 将子窗口移动到父窗口的位置
//        move(parentTopLeftLocal);

        this->setFocus();

        QWidget::showEvent(event);
    }

private:
    Ui::LevelMenu *ui;
    DifficultyBrief *difficultyBrief;

    void keyPressEvent(QKeyEvent *event) override;
};


#endif //LLKUI_LEVELMENU_H
