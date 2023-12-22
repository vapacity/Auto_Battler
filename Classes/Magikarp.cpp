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
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    name = filename;
    id = 11;
    star = 1;
    return true;
}