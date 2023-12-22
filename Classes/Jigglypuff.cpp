#include "Jigglypuff.h"
//JigglypuffµÈ¼¶1
Jigglypuff* Jigglypuff::create(const std::string& filename)
{
    Jigglypuff* jigglypuff = new (std::nothrow) Jigglypuff();
    if (jigglypuff && jigglypuff->initWithFile(filename) && jigglypuff->init(filename)) {
        jigglypuff->autorelease();
        return jigglypuff;
    }
    CC_SAFE_DELETE(jigglypuff);
    return nullptr;
}

bool Jigglypuff::init(const std::string& filename)
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