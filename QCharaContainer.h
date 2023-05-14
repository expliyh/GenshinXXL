//
// Created by expli on 2023/5/14.
//

#ifndef GENSHINXXL_QCHARACONTAINER_H
#define GENSHINXXL_QCHARACONTAINER_H

#include <QWidget>
#include <QEvent>


class QCharaContainer : public QWidget {

    void enterEvent(QEnterEvent *event) override;

public:
    explicit QCharaContainer(QWidget *parent) : QWidget(parent) {

    }
};


#endif //GENSHINXXL_QCHARACONTAINER_H
