// LittleHero.cpp
#include "LittleHero.h"

USING_NS_CC;

LittleHero* LittleHero::create(const std::string& filename,int id)
{
    LittleHero* sprite = new LittleHero();
    if (sprite && sprite->initWithFile(filename,id))
    {
        sprite->setContentSize(Size(150, 150));
        sprite->autorelease();
        //sprite->setContentSize(Size(100, 150));
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}
bool LittleHero::initWithFile(const std::string& filename,int id)
{
    if (!Sprite::initWithFile(filename))
    {
        return false;
    }
    atk = 10.0f;
    percentage = 100.0f;
    enemy = id;
    healthBar = HealthBar::create("Blood1.png", "Blood2.png", 100.0f);
    healthBar->setPosition(Vec2(25, 150));
    this->addChild(healthBar);
    if (enemy)return true;
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(LittleHero::moveToClickLocation, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    return true;
}

void LittleHero::attack(LittleHero* enemy)
{
    cocos2d::Vec2 spritePosition = this->getPosition();
    Vec2 enemyPosition = enemy->getPosition();
    auto fireball = Sprite::create("fire2.png");
    fireball->setPosition(spritePosition);
    this->getParent()->addChild(fireball);
    auto moveTo = MoveTo::create(1.0f, enemyPosition);
    auto removeSelf = RemoveSelf::create();
    auto sequence = Sequence::create(moveTo, removeSelf, nullptr);
    percentage -= atk;
    auto callFunc = CallFunc::create([=]() {
        enemy->gethurt(atk);
        });
    auto sequence1 = Sequence::create(sequence, callFunc, nullptr);
    fireball->runAction(sequence1);
}

void LittleHero::gethurt(float atkval)
{
    auto moveBackAction = MoveBy::create(0.25f, Vec2(-20, 0));  // 后退一步
    auto moveBackReverseAction = moveBackAction->reverse();  // 移回原始位置
    // 创建变色动作
    auto tintAction = TintTo::create(0.2f, 255, 0, 0);  // 变红色
    auto resetColorAction = TintTo::create(0.2f, 255, 255, 255);
    // 创建一个同时执行的动作组合
    auto damageSpawn = Spawn::create(
        Sequence::create(moveBackAction, moveBackReverseAction, nullptr),
        Sequence::create(tintAction, resetColorAction, nullptr),
        nullptr
    );
    // 运行动作组合
    this->runAction(damageSpawn);
    percentage -= atkval;
    healthBar->setPercentage(percentage);
    if (percentage <= 0) {
        this->removeFromParentAndCleanup(true);
    }
}

void LittleHero::moveToClickLocation(EventMouse* event)
{
    // 判断是否是右键点击
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        this->stopAllActions();
        // 创建一个MoveTo动作，移动到点击位置
        Vec2 currentPosition = this->getPosition();

        // 计算鼠标点击位置相对于当前位置的相对位移
        Vec2 targetPosition(event->getCursorX(), event->getCursorY());
        Vec2 moveDelta = targetPosition - currentPosition;

        float distance = moveDelta.length();

        // 计算匀速移动的时间（假设速度为300像素/秒）
        float speed = 300.0f;
        float duration = distance / speed;

        // 创建MoveBy动作，匀速移动到相对位移位置
        auto moveTo = MoveTo::create(duration, targetPosition);

        this->runAction(moveTo);
    }
}
