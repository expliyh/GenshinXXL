//
// Created by expli on 2023/6/8.
//

#include "CountdownWidget.h"

CountdownWidget::CountdownWidget(QWidget *parent) : QWidget(parent), remainingTime(60) {
    label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-family: \"HYWenHei-85W\";");

    auto *layout = new QVBoxLayout();
    layout->addWidget(label);
    setLayout(layout);

    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));
}

void CountdownWidget::startCountdown() {
    timer->start();
}

void CountdownWidget::updateCountdown() {
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;

    label->setText(
            QString("Remaining Time: %1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));

    if (remainingTime == 0) {
        timer->stop();
        emit countdownFinished();
    }

    remainingTime--;
}
