// LittleHero.h
#ifndef __LITTLE_HERO_H__
#define __LITTLE_HERO_H__

#include "cocos2d.h"
#include "HealthBar.h"

class LittleHero : public cocos2d::Sprite
{
public:
    static LittleHero* create(const std::string& filename);
    virtual bool initWithFile(const std::string& filenam);
    CREATE_FUNC(LittleHero);
    float percentage;
    HealthBar* healthBar;
};

#endif // __LITTLE_HERO_H__