#include "Yevee.h"


Yevee* Yevee::create(const std::string& filename)
{
    Yevee* yevee = new (std::nothrow) Yevee();
    if (yevee && yevee->initWithFile(filename) && yevee->init()) {
        yevee->autorelease();
        return yevee;
    }
    CC_SAFE_DELETE(yevee);
    return nullptr;
}

bool Yevee::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = "Yevee1";
    this->id = 0;
    return true;
}

void Yevee::breateFire()
{
}
