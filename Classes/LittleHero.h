// LittleHero.h
#ifndef __LITTLE_HERO_H__
#define __LITTLE_HERO_H__

#include "cocos2d.h"
#include "HealthBar.h"
#include "BlueBar.h"
class LittleHero : public cocos2d::Sprite
{
public:
    static LittleHero* create();
    virtual bool initWithFile(const std::string& filename);
    virtual bool init();
    //void moveToClickLocation(cocos2d::EventMouse* event);
    virtual void attack(LittleHero* enemy); // 攻击函数，需要攻击对象
    virtual void gethurt(float atkval);   // 受伤函数，需要攻击数值
    void enableMouseClick();
    void disableMouseClick();
    void setEnemy();
public:
    float percentage; // 血量
    float atk;        // 攻击值
    int isEnemy;        // 身份判断（暂定）
    bool mouseClickEnabled; // 鼠标事件控制
    HealthBar* healthBar;   // 血条
    BlueBar* blueBar;
};

#endif // __LITTLE_HERO_H__