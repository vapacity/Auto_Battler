// LittleHero.h
#ifndef __LITTLE_HERO_H__
#define __LITTLE_HERO_H__

#include "cocos2d.h"
#include "HealthBar.h"
#include"AudioEngine.h"
class LittleHero : public cocos2d::Sprite
{
public:
    static LittleHero* create(const std::string& filename,int id);
    virtual bool initWithFile(const std::string& filenam,int id);

    //移动
    void moveToClickLocation(cocos2d::EventMouse* event);

    //攻击
    virtual void attack(LittleHero* enemy);

    //受伤
    virtual void gethurt(float atkval);

    void setEnemey() { enemy = 1; };

    void enableMoving() { moving = 1; }
    void disableMoving() { moving = 0; }
    CREATE_FUNC(LittleHero);
public:
    int moving = 0;
    int isEnemy = 0;
    bool isAnimationPlaying = false;
    float percentage;//血量
    float atk;//攻击力
    int enemy;//敌人id
    HealthBar* healthBar;
};

#endif // __LITTLE_HERO_H__