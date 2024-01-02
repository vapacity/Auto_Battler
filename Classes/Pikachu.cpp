#include "Pikachu.h"

Pikachu* Pikachu::create(const std::string& filename)
{
    try {
        Pikachu* pikachu = new Pikachu();
        if (pikachu && pikachu->initWithFile(filename) && pikachu->init(filename)) {
            pikachu->autorelease();
            return pikachu;
        }
        CC_SAFE_DELETE(pikachu);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Pikachu::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Pikachu initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR2_GRADE1;
    originalCost = price;
    name = filename;
    id = 25;
    star = 1;

    isMelee = 0;
    ATK = 50;
    growATK = 40;
    health = 700;
    growHP = 900;
    blueBar = 40;
    attackSpeed = 1.1;
    attackRange = 2;
    moveSpeed = 3;
    return true;
}

//攻击速度加20%
void Pikachu::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
    {
        attackSpeed *= 1.2;
    }
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        attackSpeed /= 1.2;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
    else
        cocos2d::experimental::AudioEngine::play2d("pikaEffect.mp3", false);
}