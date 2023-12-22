/*#include "Mewtwo.h"

//MewtwoµÈ¼¶1
Mewtwo* Mewtwo::create(const std::string& filename)
{
    Mewtwo* mewtwo = new (std::nothrow) Mewtwo();
    if (mewtwo && mewtwo->initWithFile(filename) && mewtwo->init(filename)) {
        mewtwo->autorelease();
        return mewtwo;
    }
    CC_SAFE_DELETE(mewtwo);
    return nullptr;
}

bool Mewtwo::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = filename;
    this->id = 32;
    this->star = 1;
    return true;
}*/