// LittleHero.cpp
#include "LittleHero.h"

USING_NS_CC;

LittleHero* LittleHero::create()
{
    LittleHero* littleHero = new LittleHero();
    if (littleHero && littleHero->initWithFile("kala.png") && littleHero->init())
    {
        littleHero->setContentSize(Size(150, 150));
        littleHero->retain();
        littleHero->autorelease();
        //sprite->setContentSize(Size(100, 150));
        return littleHero;
    }
    CC_SAFE_DELETE(littleHero);
    return nullptr;
}
bool LittleHero::initWithFile(const std::string& filename)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    healthBar = HealthBar::create();
    healthBar->setPosition(Vec2(25, 150));
    this->addChild(healthBar);
    blueBar = BlueBar::create();
    blueBar->setPosition(Vec2(25, 140));
    this->addChild(blueBar);
    return true;
}
bool LittleHero::init()
{
    isEnemy = 0;
    atk = 10.0f;
    percentage = 100.0f;
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(LittleHero::moveToClickLocation, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    enableMouseClick();
    return true;
}
void LittleHero::attack(LittleHero* enemy)
{
    cocos2d::Vec2 spritePosition = this->getPosition();//获取当前位置
    Vec2 enemyPosition = enemy->getPosition();//获取敌人位置
    auto fireball = Sprite::create("fire2.png");
    fireball->setScale(0.5);
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
void LittleHero::enableMouseClick()
{
    mouseClickEnabled = true;
}
void LittleHero::disableMouseClick()
{
    mouseClickEnabled = false;
}
void LittleHero::setEnemy()
{
    isEnemy = 1;
    disableMouseClick();
}
void LittleHero::moveToClickLocation(EventMouse* event)
{
    // 判断是否是右键点击
    if (!mouseClickEnabled)return;
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
