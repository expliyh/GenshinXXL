//
// Created by expli on 2023/5/13.
//

#include "QCharacter.h"

void QCharacter::mousePressEvent(QMouseEvent *event) {
//    Q_UNUSED(event);
    if (event->button() == Qt::LeftButton) {
        emit(pressed(pos.first, pos.second));
    }
    QLabel::mousePressEvent(event);
}
