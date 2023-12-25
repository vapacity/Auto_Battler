#include "Mewtwo.h"
Mewtwo* Mewtwo::create(const std::string& filename)
{
    Mewtwo* mewtwo = new (std::nothrow) Mewtwo();
    if (mewtwo && mewtwo->initWithFile(filename) && mewtwo->init(filename)) {
        mewtwo->autorelease();
        return mewtwo;
    }
    CC_SAFE_DELETE(mewtwo);
    return nullptr;
}

bool Mewtwo::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR3_GRADE1;
    originalCost = price;
    name = filename;
    id = 32;
    star = 1;

    isMelee = 0;
    ATK = 100;
    growATK = 100;
    health = 1000;
    growHP = 1200;
    blueBar = 50;
    attackSpeed = 1.2;
    attackRange = 2;
    moveSpeed = 3.5;
    return true;
}