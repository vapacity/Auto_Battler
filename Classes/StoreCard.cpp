#include "StoreCard.h"

StoreCard::StoreCard() : sprite(nullptr), label1(nullptr), label2(nullptr), label3(nullptr) {
}

StoreCard::~StoreCard() {
}

StoreCard* StoreCard::create(const std::string& spriteFilename, const std::string& label1Text, const std::string& label2Text, const std::string& label3Text) {
    StoreCard* item = new StoreCard();
    if (item && item->init(spriteFilename, label1Text, label2Text, label3Text)) {
        item->autorelease();
        return item;
    }
    else {
        delete item;
        return nullptr;
    }
}

bool StoreCard::init(const std::string& spriteFilename, const std::string& label1Text, const std::string& label2Text, const std::string& label3Text) {
    if (!Node::init()) {
        return false;
    }

    // 创建精灵
    sprite = Sprite::create(spriteFilename);
    addChild(sprite);

    // 创建标签
    label1 = Label::createWithTTF(label1Text, "fonts/arial.ttf", 20);
    label1->setPosition(Vec2(0, -30));
    addChild(label1);

    label2 = Label::createWithTTF(label2Text, "fonts/arial.ttf", 20);
    label2->setPosition(Vec2(0, -50));
    addChild(label2);

    if (!label3Text.empty()) {
        label3 = Label::createWithTTF(label3Text, "fonts/arial.ttf", 20);
        label3->setPosition(Vec2(0, -70));
        addChild(label3);
    }

    return true;
}

void StoreCard::setLabelText(const std::string& label1Text, const std::string& label2Text, const std::string& label3Text) {
    label1->setString(label1Text);
    label2->setString(label2Text);

    if (label3) {
        label3->setString(label3Text);
    }
}