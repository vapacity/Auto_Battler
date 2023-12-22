#include "Buneary.h"


Buneary* Buneary::create(const std::string& filename)
{
    Buneary* buneary = new (std::nothrow) Buneary();
    if (buneary && buneary->initWithFile(filename) && buneary->init(filename)) {
        buneary->autorelease();
        return buneary;
    }
    CC_SAFE_DELETE(buneary);
    return nullptr;
}

bool Buneary::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    name = filename;
    id = 12;
    star = 1;
    return true;
}