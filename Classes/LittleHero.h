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
    virtual void attack(LittleHero* enemy); // ������������Ҫ��������
    virtual void gethurt(float atkval);   // ���˺�������Ҫ������ֵ
    void enableMouseClick();
    void disableMouseClick();
    void setEnemy();
public:
    float percentage; // Ѫ��
    float atk;        // ����ֵ
    int isEnemy;        // ����жϣ��ݶ���
    bool mouseClickEnabled; // ����¼�����
    HealthBar* healthBar;   // Ѫ��
    BlueBar* blueBar;
};

#endif // __LITTLE_HERO_H__