//
// Created by expli on 2023/5/11.
//

#ifndef GENSHINXXL_STARTMENU_H
#define GENSHINXXL_STARTMENU_H

#include <QMainWindow>
#include <QDebug>
#include <QScreen>
#include <QPixmap>
#include <QPicture>
#include <QPainter>
#include <QApplication>
#include <QGuiApplication>
#include <QGraphicsBlurEffect>
#include <QKeyEvent>
#include <QFile>
#include "gamewindow.h"
#include "levelmenu.h"


QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QMainWindow {
Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    ~StartMenu() override;

protected:

    int difficulty;

    bool diffcultySelected;

public:

    [[nodiscard]] int getDifficulty() const;

    void setDifficulty(int difficulty);

    bool isDifficultySelected();

private slots:

    void gameStart();

    void difficultySelect();

private:
    Ui::StartMenu *ui;

    QSize screenSize;

    void paintEvent(QPaintEvent *event) override;

    QPixmap backgroundPixmap;

    QImage backgroundImage;

    QMediaPlayer *player;

    QAudioOutput *audioOutput;

    GameWindow *game;

    LevelMenu *levelMenu;

    double scaleRate;
};


#endif //GENSHINXXL_STARTMENU_H
