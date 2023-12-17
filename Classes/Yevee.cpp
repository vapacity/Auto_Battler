#include "Yevee.h"

//Yevee1等级1
Yevee1* Yevee1::create(const std::string& filename)
{
    Yevee1* yevee = new (std::nothrow) Yevee1();
    if (yevee && yevee->initWithFile(filename) && yevee->init()) {
        yevee->autorelease();
        return yevee;
    }
    CC_SAFE_DELETE(yevee);
    return nullptr;
}

bool Yevee1::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = "Yevee1";
    this->id = 0;
    return true;
}



//Yevee2等级2
Yevee2* Yevee2::create(const std::string& filename)
{
    Yevee2* yevee = new (std::nothrow) Yevee2();
    if (yevee && yevee->initWithFile(filename) && yevee->init()) {
        yevee->autorelease();
        return yevee;
    }
    CC_SAFE_DELETE(yevee);
    return nullptr;
}

bool Yevee2::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE2;
    this->name = "Yevee2";
    this->id = 3;
    return true;
}

//Yevee3等级3
Yevee3* Yevee3::create(const std::string& filename)
{
    Yevee3* yevee = new (std::nothrow) Yevee3();
    if (yevee && yevee->initWithFile(filename) && yevee->init()) {
        yevee->autorelease();
        return yevee;
    }
    CC_SAFE_DELETE(yevee);
    return nullptr;
}

bool Yevee3::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE3;
    this->name = "Yevee3";
    this->id = 6;
    return true;
}
