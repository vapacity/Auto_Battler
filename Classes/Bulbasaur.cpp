#include "Bulbasaur.h"

Bulbasaur* Bulbasaur::create(const std::string& filename)
{
    Bulbasaur* bulbasaur = new (std::nothrow) Bulbasaur();
    if (bulbasaur && bulbasaur->initWithFile(filename) && bulbasaur->init(filename)) {
        bulbasaur->autorelease();
        return bulbasaur;
    }
    CC_SAFE_DELETE(bulbasaur);
    return nullptr;
}

bool Bulbasaur::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE2;
    this->name = filename;
    this->id = 24;
    this->star = 1;
    return true;
}