//
// Created by expli on 2023/5/14.
//

#ifndef GENSHINXXL_THEMES_H
#define GENSHINXXL_THEMES_H

#include <string>
#include <vector>
#include <QPixmap>


struct Theme {
    Theme();

    std::string name;
    std::string name_cn;
    std::vector<std::string> menu_songs;
    std::vector<std::string> slow_fight_songs;
    std::vector<std::string> normal_fight_songs;
    std::vector<std::string> fast_fight_songs;
    std::vector<std::string> menu_backgrounds;
    std::vector<std::string> fight_backgrounds;
    std::vector<std::string> characters;
    std::vector<QPixmap> characters_pixmap;
};


#endif //GENSHINXXL_THEMES_H
