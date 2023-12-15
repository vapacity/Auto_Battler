#include "Charmander.h"


Charmander* Charmander::create(const std::string& filename)
{
    Charmander* charmander = new (std::nothrow) Charmander();
    if (charmander && charmander->initWithFile(filename) && charmander->init()) {
        charmander->autorelease();
        return charmander;
    }
    CC_SAFE_DELETE(charmander);
    return nullptr;
}

bool Charmander::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = "Charmander1";
    this->id = 1;
    return true;
}

void Charmander::breateFire()
{
}
