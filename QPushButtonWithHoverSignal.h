//
// Created by 34668 on 2023/5/17.
//

#ifndef LLKUI_QPUSHBUTTONWITHHOVERSIGNAL_H
#define LLKUI_QPUSHBUTTONWITHHOVERSIGNAL_H


#include <QPushButton>
#include <QObject>
#include "QDebug"

class QPushButtonWithHoverSignal : public QPushButton {
Q_OBJECT

signals:

    void mouseEntered(int difficulty);

    void mouseLeft(int difficulty);

protected:

    int difficulty;

    void enterEvent(QEnterEvent *event) override {
        emit mouseEntered(difficulty);
        QPushButton::enterEvent(event);
    }

public:
    explicit QPushButtonWithHoverSignal(QWidget *parent, int difficulty) : QPushButton(parent),
                                                                           difficulty(difficulty) {}

protected:

    void leaveEvent(QEvent *event) override {
        emit mouseLeft(difficulty);
        QPushButton::leaveEvent(event);
    }
};


#endif //LLKUI_QPUSHBUTTONWITHHOVERSIGNAL_H
