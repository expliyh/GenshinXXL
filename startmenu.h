//
// Created by expli on 2023/5/11.
//

#ifndef GENSHINXXL_STARTMENU_H
#define GENSHINXXL_STARTMENU_H

#include <QMainWindow>
#include <QDebug>
#include <QScreen>


QT_BEGIN_NAMESPACE
namespace Ui { class StartMenu; }
QT_END_NAMESPACE

class StartMenu : public QMainWindow {
Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);

    ~StartMenu() override;

private:
    Ui::StartMenu *ui;
};


#endif //GENSHINXXL_STARTMENU_H
