#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>
#include <QString>
#include <QStringLiteral>
#include <QDebug>
#include "startmenu.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int fontid = QFontDatabase::addApplicationFont("./fonts/hk4e_zh-cn.ttf");
    qDebug() << QFontDatabase::applicationFontFamilies(fontid);
    StartMenu startMenu;
    startMenu.showFullScreen();
    a.exec();
}
