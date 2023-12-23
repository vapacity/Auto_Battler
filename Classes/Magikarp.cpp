#include "Magikarp.h"
Magikarp* Magikarp::create(const std::string& filename)
{
    Magikarp* magikarp = new (std::nothrow) Magikarp();
    if (magikarp && magikarp->initWithFile(filename) && magikarp->init(filename)) {
        magikarp->autorelease();
        return magikarp;
    }
    CC_SAFE_DELETE(magikarp);
    return nullptr;
}

bool Magikarp::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    initHealthBar();
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    originalCost = price;
    name = filename;
    id = 11;
    star = 1;

    isMelee = 0;
    ATK = 50;
    growATK = 30;
    health = 300;
    growHP = 500;
    blueBar = 40;
    attackSpeed = 1.1;
    attackRange = 3;
    moveSpeed = 0.7;
    return true;
}