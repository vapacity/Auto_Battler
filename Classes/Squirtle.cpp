#include "Squirtle.h"
//Squirtle1 µÈ¼¶1
Squirtle* Squirtle::create(const std::string& filename)
{
    Squirtle* squirtle = new (std::nothrow) Squirtle();
    if (squirtle && squirtle->initWithFile(filename) && squirtle->init(filename)) {
        squirtle->autorelease();
        return squirtle;
    }
    CC_SAFE_DELETE(squirtle);
    return nullptr;
}

bool Squirtle::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR2_GRADE1;
    originalCost = price;
    this->name = filename;
    this->id = 22;
    this->star = 1;

    isMelee = 0;
    ATK = 80;
    growATK = 80;
    health = 500;
    growHP = 600;
    blueBar = 100;
    attackSpeed = 0.9;
    attackRange = 4;
    moveSpeed = 1;
    return true;
}