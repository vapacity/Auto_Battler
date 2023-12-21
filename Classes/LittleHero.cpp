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
    cocos2d::Vec2 spritePosition = this->getPosition();//��ȡ��ǰλ��
    Vec2 enemyPosition = enemy->getPosition();//��ȡ����λ��
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
    auto moveBackAction = MoveBy::create(0.25f, Vec2(-20, 0));  // ����һ��
    auto moveBackReverseAction = moveBackAction->reverse();  // �ƻ�ԭʼλ��
    // ������ɫ����
    auto tintAction = TintTo::create(0.2f, 255, 0, 0);  // ���ɫ
    auto resetColorAction = TintTo::create(0.2f, 255, 255, 255);
    // ����һ��ͬʱִ�еĶ������
    auto damageSpawn = Spawn::create(
        Sequence::create(moveBackAction, moveBackReverseAction, nullptr),
        Sequence::create(tintAction, resetColorAction, nullptr),
        nullptr
    );
    // ���ж������
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
    // �ж��Ƿ����Ҽ����
    if (!mouseClickEnabled)return;
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        this->stopAllActions();
        // ����һ��MoveTo�������ƶ������λ��
        Vec2 currentPosition = this->getPosition();

        // ���������λ������ڵ�ǰλ�õ����λ��
        Vec2 targetPosition(event->getCursorX(), event->getCursorY());
        Vec2 moveDelta = targetPosition - currentPosition;

        float distance = moveDelta.length();

        // ���������ƶ���ʱ�䣨�����ٶ�Ϊ300����/�룩
        float speed = 300.0f;
        float duration = distance / speed;

        // ����MoveBy�����������ƶ������λ��λ��
        auto moveTo = MoveTo::create(duration, targetPosition);

        this->runAction(moveTo);
    }
}
