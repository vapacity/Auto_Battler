#include "Squirtle.h"
//Squirtle1 等级1
Squirtle1* Squirtle1::create(const std::string& filename)
{
    Squirtle1* squirtle = new (std::nothrow) Squirtle1();
    if (squirtle && squirtle->initWithFile(filename) && squirtle->init()) {
        squirtle->autorelease();
        return squirtle;
    }
    CC_SAFE_DELETE(squirtle);
    return nullptr;
}

bool Squirtle1::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE1;
    this->name = "Squirtle1";
    this->id = 2;
    return true;
}
//Squirtle2 等级2
Squirtle2* Squirtle2::create(const std::string& filename)
{
    Squirtle2* squirtle = new (std::nothrow) Squirtle2();
    if (squirtle && squirtle->initWithFile(filename) && squirtle->init()) {
        squirtle->autorelease();
        return squirtle;
    }
    CC_SAFE_DELETE(squirtle);
    return nullptr;
}

bool Squirtle2::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE2;
    this->name = "Squirtle2";
    this->id = 5;
    return true;
}

//Squirtle3 等级3
Squirtle3* Squirtle3::create(const std::string& filename)
{
    Squirtle3* squirtle = new (std::nothrow) Squirtle3();
    if (squirtle && squirtle->initWithFile(filename) && squirtle->init()) {
        squirtle->autorelease();
        return squirtle;
    }
    CC_SAFE_DELETE(squirtle);
    return nullptr;
}

bool Squirtle3::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR1_GRADE3;
    this->name = "Squirtle3";
    this->id = 8;
    return true;
}

