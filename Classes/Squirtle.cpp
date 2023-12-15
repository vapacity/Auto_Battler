#include "Squirtle.h"

Squirtle* Squirtle::create(const std::string& filename)
{
    Squirtle* squirtle = new (std::nothrow) Squirtle();
    if (squirtle && squirtle->initWithFile(filename) && squirtle->init()) {
        squirtle->autorelease();
        return squirtle;
    }
    CC_SAFE_DELETE(squirtle);
    return nullptr;
}

bool Squirtle::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = "Squirtle1";
    this->id = 2;
    return true;
}
