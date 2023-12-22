#include "Charmander.h"

//Charmandeer1 µÈ¼¶1
Charmander* Charmander::create(const std::string& filename)
{
    Charmander* charmander = new (std::nothrow) Charmander();
    if (charmander && charmander->initWithFile(filename) && charmander->init(filename)) {
        charmander->autorelease();
        return charmander;
    }
    CC_SAFE_DELETE(charmander);
    return nullptr;
}

bool Charmander::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = filename;
    this->id = 23;
    this->star = 1;
    return true;
}
