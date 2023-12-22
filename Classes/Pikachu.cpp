#include "Pikachu.h"
Pikachu* Pikachu::create(const std::string& filename)
{
    Pikachu* pikachu = new (std::nothrow) Pikachu();
    if (pikachu && pikachu->initWithFile(filename) && pikachu->init(filename)) {
        pikachu->autorelease();
        return pikachu;
    }
    CC_SAFE_DELETE(pikachu);
    return nullptr;
}

bool Pikachu::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    name = filename;
    id = 25;
    star = 1;
    return true;
}