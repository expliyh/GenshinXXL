#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>
#include <QString>
#include <QStringLiteral>
#include <QDebug>
#include "startmenu.h"
#include <QMediaPlayer>
#include <QAudioOutput>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int font_id = QFontDatabase::addApplicationFont("./fonts/hk4e_zh-cn.ttf");
    qDebug() << QFontDatabase::applicationFontFamilies(font_id);
    StartMenu startMenu;
    startMenu.showFullScreen();
    QApplication::exec();
}
