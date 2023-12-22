#include "Bulbasaur.h"

//BulbasaurµÈ¼¶1
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
    price = PRICE_STAR1_GRADE2;
    name = filename;
    id = 24;
    star = 1;
    return true;
}