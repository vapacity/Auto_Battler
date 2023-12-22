#include "Snorlax.h"
Snorlax* Snorlax::create(const std::string& filename)
{
    Snorlax* snorlax = new (std::nothrow) Snorlax();
    if (snorlax && snorlax->initWithFile(filename) && snorlax->init(filename)) {
        snorlax->autorelease();
        return snorlax;
    }
    CC_SAFE_DELETE(snorlax);
    return nullptr;
}

bool Snorlax::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    name = filename;
    id = 31;
    star = 1;
    return true;
}