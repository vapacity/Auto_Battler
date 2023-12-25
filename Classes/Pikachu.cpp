#include "Pikachu.h"
Pikachu* Pikachu::create(const std::string& filename)
{
    Pikachu* pikachu = new (std::nothrow) Pikachu();
    if (pikachu && pikachu->initWithFile(filename) && pikachu->init(filename)) {
        pikachu->autorelease();
        return pikachu;
    }
    CC_SAFE_DELETE(pikachu);
    return nullptr;
}

bool Pikachu::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR2_GRADE1;
    originalCost = price;
    name = filename;
    id = 25;
    star = 1;

    isMelee = 0;
    ATK = 50;
    growATK = 40;
    health = 700;
    growHP = 900;
    blueBar = 40;
    attackSpeed = 1.1;
    attackRange = 2;
    moveSpeed = 3;
    return true;
}