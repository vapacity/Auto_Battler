#include "Jingglypuff.h"


Jingglypuff* Jingglypuff::create(const std::string& filename)
{
    Jingglypuff* jingglypuff = new (std::nothrow) Jingglypuff();
    if (jingglypuff && jingglypuff->initWithFile(filename) && jingglypuff->init(filename)) {
        jingglypuff->autorelease();
        return jingglypuff;
    }
    CC_SAFE_DELETE(jingglypuff);
    return nullptr;
}

bool Jingglypuff::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    originalCost = price;
    name = filename;
    id = 13;
    star = 1;

    isMelee = 1;
    ATK = 20;
    growATK = 30;
    health = 600;
    growHP = 700;
    blueBar = 70;
    attackSpeed = 0.8;
    attackRange = 1;
    moveSpeed = 1;
    return true;
}