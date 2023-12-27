// LittleHero.cpp
#include "LittleHero.h"
USING_NS_CC;
const int HURT_ACTION_TAG = 1;
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
    if (isAnimationPlaying)
        return;
    this->stopAllActions();
    enemy->moving = 0;
    enemy->stopAllActions();
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
    isAnimationPlaying = true;
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
    damageSpawn->setTag(HURT_ACTION_TAG);
    // ���ж������
    this->runAction(damageSpawn);
    percentage -= atkval;
    healthBar->setPercentage(percentage);
    if (percentage <= 0) {
        this->removeFromParentAndCleanup(true);
    }
    this->moving = 1;
}

void LittleHero::setEnemey()
{
    isEnemy = 1;
}

void LittleHero::disableMoving()
{
    moving = 0;
}

void LittleHero::enableMoving()
{
    moving = 1;
}

void LittleHero::moveToClickLocation(EventMouse* event)
{
    // �ж��Ƿ����Ҽ����
    if (isEnemy)return;
    if (!moving)return;
    Action* hurtAction = getActionByTag(HURT_ACTION_TAG);
    if (hurtAction)return;
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
