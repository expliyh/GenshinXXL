#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>
#include <QString>
#include <QStringLiteral>
#include <QDebug>
#include "startmenu.h"
#include "CountdownWidget.h"
#include <QMediaPlayer>
#include <QAudioOutput>

//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    int font_id = QFontDatabase::addApplicationFont("./fonts/hk4e_zh-cn.ttf");
//    qDebug() << QFontDatabase::applicationFontFamilies(font_id);
//    StartMenu startMenu;
//    startMenu.showFullScreen();
//    QApplication::exec();
//}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    int font_id = QFontDatabase::addApplicationFont("./fonts/hk4e_zh-cn.ttf");
    CountdownWidget widget;
    widget.startCountdown();

    // 连接倒计时结束信号的槽函数
    QObject::connect(&widget, SIGNAL(countdownFinished()), &app, SLOT(quit()));

    widget.show();
    return app.exec();
}
