#include "Charmander.h"


Charmander* Charmander::create(const std::string& filename)
{
    Charmander* charmander = new (std::nothrow) Charmander();
    if (charmander && charmander->initWithFile(filename) && charmander->init()) {
        charmander->autorelease();
        return charmander;
    }
    CC_SAFE_DELETE(charmander);
    return nullptr;
}

bool Charmander::init()
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(0.15);
    name = "Charmander1";
    return true;
}

void Charmander::breateFire()
{
}
