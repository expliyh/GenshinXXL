//
// Created by expli on 2023/5/13.
//

#ifndef GENSHINXXL_QCHARACTER_H
#define GENSHINXXL_QCHARACTER_H


#include <QLabel>
#include <QMouseEvent>

class QCharacter : public QLabel {
    Q_OBJECT;
public:
    QCharacter(QWidget *parent, int x, int y) : QLabel(parent), pos(x, y) {

    }

    std::pair<int, int> getPosition() {
        return this->pos;
    }


signals:

    void clicked();

    void pressed(int x, int y);

private:
    std::pair<int, int> pos;

    void mousePressEvent(QMouseEvent *event) override;

};


#endif //GENSHINXXL_QCHARACTER_H
