/*#include "Rabbit.h"

//RabbitµÈ¼¶1
Rabbit* Rabbit::create(const std::string& filename)
{
    Rabbit* rabbit = new (std::nothrow) Rabbit();
    if (rabbit && rabbit->initWithFile(filename) && rabbit->init(filename)) {
        rabbit->autorelease();
        return rabbit;
    }
    CC_SAFE_DELETE(rabbit);
    return nullptr;
}

bool Rabbit::init(const std::string& filename)
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
}*/