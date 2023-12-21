#include "BlueBar.h"

BlueBar* BlueBar::create()
{
    BlueBar* blueBar = new (std::nothrow) BlueBar();
    if (blueBar && blueBar->initWithFile() && blueBar->init())
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

bool BlueBar::initWithFile()
{
    if (!Node::init())
    {
        return false;
    }
    // �����ײ�
    auto backgroundSprite = Sprite::create("Blood1.png");
    backgroundSprite->setContentSize(HealthBarSize);
    backgroundSprite->setAnchorPoint(Vec2(0, 0));
    backgroundSprite->setPosition(Vec2(0, 0));
    this->addChild(backgroundSprite);

    // ����
    auto sprite = Sprite::create("Blood3.png");
    sprite->setContentSize(HealthBarSize);
    blueBar = ProgressTimer::create(sprite);
    blueBar->setAnchorPoint(Vec2(0, 0));
    blueBar->setType(ProgressTimer::Type::BAR);
    blueBar->setMidpoint(Vec2(0, 0.5));
    blueBar->setBarChangeRate(Vec2(1, 0));
    blueBar->setPercentage(0); // ��ʼ��Ϊ0%
    blueBar->setPosition(Vec2(0, 0));
    this->addChild(blueBar);
    // ��ʱ����ÿ������һ���ٷֱ�
    return true;
}

bool BlueBar::init()
{
    timerEnabled = true;
    this->schedule(schedule_selector(BlueBar::increaseBlue), 1.0f);
    this->setVisible(false);
    this->setVisibility(true);
    return true;
}

void BlueBar::setVisibility(bool visible)
{
    if (isVisible != visible)
    {
        isVisible = visible;
        this->setVisible(visible);
    }
    //if (!isVisible)disableTimer();
}

void BlueBar::enableTimer()
{
    if (!timerEnabled)
    {
        this->schedule(schedule_selector(BlueBar::increaseBlue), 1.0f);
        timerEnabled = true;
    }
}

void BlueBar::disableTimer()
{
    if (timerEnabled)
    {
        this->unschedule(schedule_selector(BlueBar::increaseBlue));
        timerEnabled = false;
    }
}

void BlueBar::increaseBlue(float dt)
{
    // ���������ٷֱ�
    float currentPercentage = blueBar->getPercentage();
    float newPercentage = currentPercentage + 10.0f; // ���磬ÿ������10%
    if (newPercentage > 100.0f)
    {
        newPercentage = 100.0f;
    }
    blueBar->setPercentage(newPercentage);
}
