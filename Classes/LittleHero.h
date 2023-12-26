// LittleHero.h
#ifndef __LITTLE_HERO_H__
#define __LITTLE_HERO_H__

#include "cocos2d.h"
#include "HealthBar.h"

class LittleHero : public cocos2d::Sprite
{
public:
    static LittleHero* create(const std::string& filename,int id);
    virtual bool initWithFile(const std::string& filenam,int id);
    void moveToClickLocation(cocos2d::EventMouse* event);
    virtual void attack(LittleHero* enemy);
    virtual void gethurt(float atkval);
    CREATE_FUNC(LittleHero);
public:
    bool isAnimationPlaying = false;
    float percentage;//ÑªÁ¿
    float atk;
    int enemy;
    HealthBar* healthBar;
};

#endif // __LITTLE_HERO_H__