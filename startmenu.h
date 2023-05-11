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


QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QMainWindow {
Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    ~StartMenu() override;

private:
    Ui::StartMenu *ui;

    QSize screenSize;

    void paintEvent(QPaintEvent *event) override;

    QPixmap backgroundPixmap;

    QImage backgroundImage;

    double scaleRate;
};


#endif //GENSHINXXL_STARTMENU_H
