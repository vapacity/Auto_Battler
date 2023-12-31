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

    //�ƶ�
    void moveToClickLocation(cocos2d::EventMouse* event);

    //����
    virtual void attack(LittleHero* enemy);

    //����
    virtual void gethurt(float atkval);

    void setEnemey() { enemy = 1; };

    void enableMoving() { moving = 1; }
    void disableMoving() { moving = 0; }
    CREATE_FUNC(LittleHero);
public:
    int moving = 0;
    int isEnemy = 0;
    bool isAnimationPlaying = false;
    float percentage;//Ѫ��
    float atk;//������
    int enemy;//����id
    HealthBar* healthBar;
};

#endif // __LITTLE_HERO_H__