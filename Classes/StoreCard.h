#pragma once

#include "cocos2d.h"

USING_NS_CC;

class StoreCard : public Node {
public:
    StoreCard();
    ~StoreCard();

    static StoreCard* create(int id);

    void setLabelText(const std::string& label1Text, const std::string& label2Text, const std::string& label3Text = "");

    Sprite* sprite;
    Label* label1;
    Label* label2;
    Label* label3;

    bool init(const std::string& spriteFilename, const std::string& label1Text, const std::string& label2Text, const std::string& label3Text);
};
