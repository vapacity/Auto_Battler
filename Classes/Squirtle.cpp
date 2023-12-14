#include "Squirtle.h"

Squirtle* Squirtle::create(const std::string& filename)
{
    Squirtle* squirtle = new (std::nothrow) Squirtle();
    if (squirtle && squirtle->initWithFile(filename) && squirtle->init()) {
        squirtle->autorelease();
        return squirtle;
    }
    CC_SAFE_DELETE(squirtle);
    return nullptr;
}

bool Squirtle::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(0.15);
    name = "Squirtle1";
    return true;
}
