//
// Created by expli on 2023/5/14.
//

#include "Themes.h"

Theme::Theme() : characters_pixmap() {
    this->characters = {
            "images/GenshinCharacter/AiErHaiSen.png",
            "images/GenshinCharacter/DiLuKe.png",
            "images/GenshinCharacter/FaLuShan.png",
            "images/GenshinCharacter/GanYu.png",
            "images/GenshinCharacter/GuiZhong.png",
            "images/GenshinCharacter/MoNa.png",
            "images/GenshinCharacter/SaiNuo.png",
            "images/GenshinCharacter/ShenHe.png",
            "images/GenshinCharacter/WanYe.png",
            "images/GenshinCharacter/XiangLing.png"
    };
    for (const auto &i: this->characters) {
        this->characters_pixmap.emplace_back(i.c_str());
    }
};
