// LittleHero.cpp
#include "LittleHero.h"

USING_NS_CC;

LittleHero* LittleHero::create(const std::string& filename)
{
    LittleHero* sprite = new LittleHero();
    if (sprite && sprite->initWithFile(filename))
    {
        sprite->autorelease();
        //sprite->setContentSize(Size(100, 150));
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool LittleHero::initWithFile(const std::string& filename)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }
    healthBar = HealthBar::create("Blood1.png", "Blood2.png", 100.0f);
    healthBar->setPosition(Vec2(0, 170));
    this->addChild(healthBar);
    healthBar->setPercentage(75.0f);
    //auto mysprite = Sprite::create(filename);
    //mysprite->setContentSize(Size(100, 150));
    //this->addChild(mysprite);
    return true;
}
