//
// Created by expli on 2023/5/13.
//

#ifndef GENSHINXXL_GAMEWINDOW_H
#define GENSHINXXL_GAMEWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QScreen>
#include <QSizePolicy>
#include <QGridLayout>
#include "QCharacter.h"
#include "QCharaContainer.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow {
Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

    ~GameWindow() override;

private slots:

    void enterGame();

    void characterPressed(int x, int y);

private:
    Ui::GameWindow *ui;

    QCharacter *table_picture[500][500]{};

    void keyPressEvent(QKeyEvent *event) override;

    bool entered;

    void mouseReleaseEvent(QMouseEvent *event) override;


    QPixmap backgroundPixmap;

    void paintEvent(QPaintEvent *event) override;

    QSize screenSize;
    double scaleRate;
};


#endif //GENSHINXXL_GAMEWINDOW_H
