#include "Charmander.h"

//Charmandeer1 等级1
Charmander1* Charmander1::create(const std::string& filename)
{
    Charmander1* charmander = new (std::nothrow) Charmander1();
    if (charmander && charmander->initWithFile(filename) && charmander->init()) {
        charmander->autorelease();
        return charmander;
    }
    CC_SAFE_DELETE(charmander);
    return nullptr;
}

bool Charmander1::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = "Charmander1";
    this->id = 1;
    return true;
}

void Charmander1::breateFire()
{
}

//Charmandeer1 等级1
Charmander2* Charmander2::create(const std::string& filename)
{
    Charmander2* charmander = new (std::nothrow) Charmander2();
    if (charmander && charmander->initWithFile(filename) && charmander->init()) {
        charmander->autorelease();
        return charmander;
    }
    CC_SAFE_DELETE(charmander);
    return nullptr;
}

bool Charmander2::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE2;
    this->name = "Charmander2";
    this->id = 4;
    return true;
}

//Charmandeer1 等级1
Charmander3* Charmander3::create(const std::string& filename)
{
    Charmander3* charmander = new (std::nothrow) Charmander3();
    if (charmander && charmander->initWithFile(filename) && charmander->init()) {
        charmander->autorelease();
        return charmander;
    }
    CC_SAFE_DELETE(charmander);
    return nullptr;
}

bool Charmander3::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE3;
    this->name = "Charmander3";
    this->id = 7;
    return true;
}
