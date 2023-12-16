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

    // 创建背景 Sprite
    auto backgroundSprite = Sprite::create("Blood1.png");
    backgroundSprite->setContentSize(HealthBarSize);
    backgroundSprite->setAnchorPoint(Vec2(0, 0));
    backgroundSprite->setPosition(Vec2(0, 0));
    this->addChild(backgroundSprite,-1);

    // 创建 ProgressTimer，并将源 Sprite 设置为其显示内容
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
    // 设置血条的百分比
    // 可以用于attack，gethurt等函数内，实现血量减少
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
