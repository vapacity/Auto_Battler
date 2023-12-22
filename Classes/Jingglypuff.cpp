#include "Jingglypuff.h"


Jingglypuff* Jingglypuff::create(const std::string& filename)
{
    Jingglypuff* jingglypuff = new (std::nothrow) Jingglypuff();
    if (jingglypuff && jingglypuff->initWithFile(filename) && jingglypuff->init(filename)) {
        jingglypuff->autorelease();
        return jingglypuff;
    }
    CC_SAFE_DELETE(jingglypuff);
    return nullptr;
}

bool Jingglypuff::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    name = filename;
    id = 13;
    star = 1;
    return true;
}