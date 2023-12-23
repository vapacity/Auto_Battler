#include "Yevee.h"

//YeveeµÈ¼¶1
Yevee* Yevee::create(const std::string& filename)
{
    Yevee* yevee = new (std::nothrow) Yevee();
    if (yevee && yevee->initWithFile(filename) && yevee->init(filename)) {
        yevee->autorelease();
        return yevee;
    }
    CC_SAFE_DELETE(yevee);
    return nullptr;
}

bool Yevee::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR2_GRADE1;
    originalCost = price;
    name = filename;
    id = 21;
    star = 1;

    isMelee = 1;
    ATK = 70;
    growATK = 50;
    health = 600;
    growHP = 700;
    blueBar = 40;
    attackSpeed = 1;
    attackRange = 1;
    return true;
}


