/*#include "Rugia.h"

//RugiaµÈ¼¶1
Rugia* Rugia::create(const std::string& filename)
{
    Rugia* rugia = new (std::nothrow) Rugia();
    if (rugia && rugia->initWithFile(filename) && rugia->init(filename)) {
        rugia->autorelease();
        return rugia;
    }
    CC_SAFE_DELETE(rugia);
    return nullptr;
}

bool Rugia::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    name = filename;
    id = 33;
    star = 1;
    return true;
}*/