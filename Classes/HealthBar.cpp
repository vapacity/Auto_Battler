// HealthBar.cpp
#include "HealthBar.h"

USING_NS_CC;

HealthBar::HealthBar()
    : healthBar(nullptr)
{
}

HealthBar* HealthBar::create(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    HealthBar* healthBar = new (std::nothrow) HealthBar();
    if (healthBar && healthBar->init(backgroundFilename, barFilename, initialPercentage))
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

bool HealthBar::init(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    if (!Node::init())
    {
        return false;
    }

    // 创建背景 Sprite
    auto backgroundSprite = Sprite::create(backgroundFilename);
    backgroundSprite->setContentSize(Size(100, 10));
    backgroundSprite->setAnchorPoint(Vec2(0, 0));
    backgroundSprite->setPosition(Vec2(0, 0));
    this->addChild(backgroundSprite);

    // 创建 ProgressTimer，并将源 Sprite 设置为其显示内容
    auto sprite = Sprite::create(barFilename);
    sprite->setContentSize(Size(100, 10));
    healthBar = ProgressTimer::create(sprite);
    healthBar->setAnchorPoint(Vec2(0, 0));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5));
    healthBar->setBarChangeRate(Vec2(1, 0));
    healthBar->setPosition(Vec2(0, 0));
    healthBar->setPercentage(initialPercentage);
    this->addChild(healthBar);

    return true;
}

void HealthBar::setPercentage(float percentage)
{
    // 设置血条的百分比
    if(this)
        healthBar->setPercentage(percentage);
}