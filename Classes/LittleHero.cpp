// LittleHero.cpp
#include "LittleHero.h"
USING_NS_CC;
const int HURT_ACTION_TAG = 1;
LittleHero* LittleHero::create(const std::string& filename,int id)
{
    try {
        LittleHero* sprite = new LittleHero();
        if (sprite && sprite->initWithFile(filename, id))
        {
            sprite->setContentSize(Size(150, 150));
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr; 
}
bool LittleHero::initWithFile(const std::string& filename,int id)
{
    if (!Sprite::initWithFile(filename))
    {
        throw std::runtime_error("LittleHero initialization failed: Sprite initialization with file failed");
    }
    atk = 10.0f;
    percentage = 10.0f;
    enemy = id;

    //添加血条
    healthBar = HealthBar::create("Blood1.png", "Blood2.png", 100.0f);
    healthBar->setPosition(Vec2(25, 150));
    this->addChild(healthBar);

    if (enemy)//如果当前有敌人，直接返回，不能控制角色移动
        return true;
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(LittleHero::moveToClickLocation, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    return true;
}

void LittleHero::attack(LittleHero* enemy)
{
    //检查是否正在播放动画，如果是，则直接返回，避免重复触发攻击
    if (isAnimationPlaying)
        return;

    //攻击前停止其他动作
    this->stopAllActions();
    enemy->moving = 0;
    enemy->stopAllActions();

    //获取角色和敌人的位置
    cocos2d::Vec2 spritePosition = this->getPosition();
    Vec2 enemyPosition = enemy->getPosition();

    //创建攻击物
    auto fireball = Sprite::create("kalaAttack.png");
    fireball->setScale(0.05);
    fireball->setPosition(spritePosition);
    this->getParent()->addChild(fireball);

    //创建一个移动到敌人位置的动作，然后将火球自身从场景中移除
    auto moveTo = MoveTo::create(1.0f, enemyPosition);
    auto removeSelf = RemoveSelf::create();
    auto sequence = Sequence::create(moveTo, removeSelf, nullptr);

    //火球到达敌人位置后调用敌人的gethurt
    auto callFunc = CallFunc::create([=]() {
        enemy->gethurt(atk);
        cocos2d::experimental::AudioEngine::play2d("attackEffect.mp3", false);
        });

    auto sequence1 = Sequence::create(sequence, callFunc, nullptr);
    fireball->runAction(sequence1);
    isAnimationPlaying = true;
}

void LittleHero::gethurt(float atkval)
{
    //受伤动作
    auto moveBackAction = MoveBy::create(0.25f, Vec2(-20, 0));  // 后退一步
    auto moveBackReverseAction = moveBackAction->reverse();  // 移回原始位置
    
    auto tintAction = TintTo::create(0.2f, 255, 0, 0);  // 变红色
    auto resetColorAction = TintTo::create(0.2f, 255, 255, 255);
    // 创建一个同时执行的动作组合
    auto damageSpawn = Spawn::create(
        Sequence::create(moveBackAction, moveBackReverseAction, nullptr),
        Sequence::create(tintAction, resetColorAction, nullptr),
        nullptr
    );
    damageSpawn->setTag(HURT_ACTION_TAG);//命名为受伤动作
    this->runAction(damageSpawn); // 运行动作组合

    //血量减少
    percentage -= atkval;
    healthBar->setPercentage(percentage);
    if (percentage <= 0) {
        this->removeFromParentAndCleanup(true);
    }
    this->moving = 1;
}

void LittleHero::moveToClickLocation(EventMouse* event)
{
    if (isEnemy)return;//如果存在敌人，不能移动
    if (!moving)return;//如果moving状态为0，不能移动
    Action* hurtAction = getActionByTag(HURT_ACTION_TAG);
    if (hurtAction)return;//如果正在完成受伤动作，不能移动

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
