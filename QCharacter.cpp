//
// Created by expli on 2023/5/13.
//

#include "QCharacter.h"

void QCharacter::mousePressEvent(QMouseEvent *event) {
//    Q_UNUSED(event);
    if (event->button() == Qt::LeftButton) {
        emit(pressed(pos.first, pos.second));
    }
    if (this->selected) {
        this->selected = false;
        this->removeBorder();

    } else {
        this->selected = true;
        this->addBorder();
    }
    QLabel::mousePressEvent(event);
}

void QCharacter::addBorder() {
    this->setStyleSheet("border: 2px solid red");
}

void QCharacter::removeBorder() {
    this->setStyleSheet("");
}

void QCharacter::enterEvent(QEnterEvent *event) {
    this->setFocus();
    qDebug() << "Entered 01";
    qDebug() << this->size();
    QWidget::enterEvent(event);
}
