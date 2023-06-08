//
// Created by expli on 2023/6/8.
//

#ifndef GENSHINXXL_COUNTDOWNWIDGET_H
#define GENSHINXXL_COUNTDOWNWIDGET_H


#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QtSvg/QSvgRenderer>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE

class CountdownWidget : public QWidget {
Q_OBJECT

public:
    explicit CountdownWidget(QWidget *parent = nullptr);

    void startCountdown();

signals:

    void countdownFinished();

private slots:

    void updateCountdown();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int remainingTime;
    QLabel *timeLabel;
    QTimer *timer;
    QPixmap *icon;
    QSvgRenderer *icon_renderer;
    QLabel *iconLabel;
};



#endif //GENSHINXXL_COUNTDOWNWIDGET_H
