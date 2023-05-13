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


QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow {
Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);

    ~GameWindow() override;

private:
    Ui::GameWindow *ui;

    void keyPressEvent(QKeyEvent* event) override;

    QPixmap backgroundPixmap;

    void paintEvent(QPaintEvent *event) override;
};


#endif //GENSHINXXL_GAMEWINDOW_H
