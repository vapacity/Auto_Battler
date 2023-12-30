// BlueBar.cpp
#include "BlueBar.h"

USING_NS_CC;

BlueBar::BlueBar()
    : blueBar(nullptr)
{ 
}

BlueBar* BlueBar::create(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    BlueBar* blueBar = new (std::nothrow) BlueBar();
    if (blueBar && blueBar->init(backgroundFilename, barFilename, initialPercentage))
    {
        blueBar->autorelease();
        return blueBar;
    }
    else
    {
        delete blueBar;
        return nullptr;
    }
}

bool BlueBar::init(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    if (!Node::init())
    {
        return false;
    }

    // �������� Sprite
    auto backgroundSprite = Sprite::create(backgroundFilename);
    backgroundSprite->setContentSize(Size(100, 10));
    backgroundSprite->setAnchorPoint(Vec2(0, 0));
    backgroundSprite->setPosition(Vec2(0, 0));
    this->addChild(backgroundSprite);

    // ���� ProgressTimer������Դ Sprite ����Ϊ����ʾ����
    auto sprite = Sprite::create(barFilename);
    sprite->setContentSize(Size(100, 10));
    blueBar = ProgressTimer::create(sprite);
    blueBar->setAnchorPoint(Vec2(0, 0));
    blueBar->setType(ProgressTimer::Type::BAR);
    blueBar->setMidpoint(Vec2(0, 0.5));
    blueBar->setBarChangeRate(Vec2(1, 0));
    blueBar->setPosition(Vec2(0, 0));
    blueBar->setPercentage(initialPercentage);
    this->addChild(blueBar);

    return true;
}

void BlueBar::setPercentage(float percentage)
{
    // ����Ѫ���İٷֱ�
    if (this)
        blueBar->setPercentage(percentage);
}