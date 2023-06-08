//
// Created by expli on 2023/6/8.
//

#include <QPainter>
#include <QPainterPath>
#include "CountdownWidget.h"

CountdownWidget::CountdownWidget(QWidget *parent) : QWidget(parent), remainingTime(300) {
    this->iconLabel = new QLabel;
    this->iconLabel->setFixedSize(25, 25);
    this->timeLabel = new QLabel();
    this->timeLabel->setAlignment(Qt::AlignCenter);
    this->timeLabel->setStyleSheet("font-family: \"HYWenHei-85W\";font: normal 22px;color: white;");

    this->icon_renderer = new QSvgRenderer;
    this->icon_renderer->load(QString("images/icons/alarm-clock.svg"));

    this->icon = new QPixmap(this->iconLabel->size());
    this->icon->fill(Qt::transparent);
    QPainter painter(this->icon);
    this->icon_renderer->render(&painter);
    painter.end();

    this->iconLabel->setPixmap(*this->icon);

    auto *layout = new QHBoxLayout();
    layout->addWidget(this->iconLabel);
    layout->addWidget(this->timeLabel);
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

    timeLabel->setText(
            QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));

    if (remainingTime == 0) {
        timer->stop();
        emit countdownFinished();
    }

    remainingTime--;
}

void CountdownWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(40, 40, 40, 90));

    // 绘制圆角矩形背景
    int cornerRadius = rect().height() / 2; // 圆角半径
    painter.drawRoundedRect(rect(), cornerRadius, cornerRadius);
}
