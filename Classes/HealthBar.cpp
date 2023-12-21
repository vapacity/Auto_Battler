// HealthBar.cpp
#include "HealthBar.h"
#define HealthBarSize Size(100, 10) 
USING_NS_CC;


HealthBar* HealthBar::create()
{
    HealthBar* healthBar = new (std::nothrow) HealthBar();
    if (healthBar && healthBar->initWithFile()&&healthBar->init())
    {
        healthBar->autorelease();
        return healthBar;
    }
    else
    {
        delete healthBar;
        return nullptr;
    }
}
bool HealthBar::initWithFile()
{
    if (!Node::init())
    {
        return false;
    }

    // �������� Sprite
    auto backgroundSprite = Sprite::create("Blood1.png");
    backgroundSprite->setContentSize(HealthBarSize);
    backgroundSprite->setAnchorPoint(Vec2(0, 0));
    backgroundSprite->setPosition(Vec2(0, 0));
    this->addChild(backgroundSprite,-1);

    // ���� ProgressTimer������Դ Sprite ����Ϊ����ʾ����
    auto sprite = Sprite::create("Blood2.png");
    sprite->setContentSize(HealthBarSize);
    healthBar = ProgressTimer::create(sprite);
    healthBar->setAnchorPoint(Vec2(0, 0));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5));
    healthBar->setBarChangeRate(Vec2(1, 0));
    healthBar->setPosition(Vec2(0, 0));
    this->addChild(healthBar,0);
    return true;
}
bool HealthBar::init()
{
    healthBar->setPercentage(100.0f);
    this->setVisibility(true);
    return true;
}
void HealthBar::setPercentage(float percentage)
{
    // ����Ѫ���İٷֱ�
    // ��������attack��gethurt�Ⱥ����ڣ�ʵ��Ѫ������
    healthBar->setPercentage(percentage);
}
void HealthBar::recover()
{
    healthBar->setPercentage(100.0f);
}
void HealthBar::setVisibility(bool visible)
{
    if (isVisible != visible)
    {
        isVisible = visible;
        this->setVisible(visible);
    }
}
