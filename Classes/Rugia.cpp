#include "Rugia.h"
Rugia* Rugia::create(const std::string& filename)
{
    Rugia* rugia = new (std::nothrow) Rugia();
    if (rugia && rugia->initWithFile(filename) && rugia->init(filename)) {
        rugia->autorelease();
        return rugia;
    }
    CC_SAFE_DELETE(rugia);
    return nullptr;
}

bool Rugia::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR3_GRADE1;
    originalCost = price;
    name = filename;
    id = 33;
    star = 1;
    isMelee = 0;
    ATK = 130;
    growATK = 130;
    health = 700;
    growHP = 800;
    blueBar = 40;
    attackSpeed = 1.5;
    attackRange = 7;
    moveSpeed = 0.7;
    return true;
}