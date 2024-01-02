// BlueBar.cpp
#include "BlueBar.h"

USING_NS_CC;

BlueBar::BlueBar()
    : blueBar(nullptr)
{  
}

BlueBar* BlueBar::create(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    try {
        BlueBar* blueBar = new  BlueBar();
        if (blueBar && blueBar->init(backgroundFilename, barFilename, initialPercentage))
        {
            blueBar->autorelease();
            return blueBar;
        }
    }
    catch (const std::exception& e) {
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool BlueBar::init(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    if (!Node::init())
    {
        throw std::runtime_error("BlueBar initialization failed: Node initialization failed");
    }

    // 创建背景 Sprite
    auto backgroundSprite = Sprite::create(backgroundFilename); //使用给定的 backgroundFilename 作为纹理
    backgroundSprite->setContentSize(Size(100, 10)); //设置其大小为(100, 10)
    backgroundSprite->setAnchorPoint(Vec2(0, 0));//锚点为左下角（0, 0）
    backgroundSprite->setPosition(Vec2(0, 0));//位置为(0, 0)
    this->addChild(backgroundSprite); //将这个背景 Sprite 添加到 BlueBar 对象中

    // 创建 ProgressTimer，并将源 Sprite 设置为其显示内容
    auto sprite = Sprite::create(barFilename);
    sprite->setContentSize(Size(100, 10));
    blueBar = ProgressTimer::create(sprite);//创建一个进度条对象，并将先前创建的 Sprite 对象设置为其显示内容
    blueBar->setAnchorPoint(Vec2(0, 0));
    blueBar->setType(ProgressTimer::Type::BAR);//水平进度条
    blueBar->setMidpoint(Vec2(0, 0.5));//填充起点
    blueBar->setBarChangeRate(Vec2(1, 0));//变化率，只在水平方向上充满
    blueBar->setPosition(Vec2(0, 0));
    blueBar->setPercentage(initialPercentage);
    this->addChild(blueBar);

    return true;
}

void BlueBar::setPercentage(float percentage)
{
    // 设置蓝条的百分比
    if (this)
        blueBar->setPercentage(percentage);
}