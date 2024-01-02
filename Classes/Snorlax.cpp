#include "Snorlax.h"
Snorlax* Snorlax::create(const std::string& filename)
{
    try {
        Snorlax* snorlax = new Snorlax();
        if (snorlax && snorlax->initWithFile(filename) && snorlax->init(filename)) {
            snorlax->autorelease();
            return snorlax;
        }
        CC_SAFE_DELETE(snorlax);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Snorlax::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Snorlax initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR3_GRADE1;
    originalCost = price;
    name = filename;
    id = 31;
    star = 1;

    isMelee = 1;
    ATK = 70;
    growATK = 70;
    health = 1500;
    growHP = 1700;
    blueBar = 100;
    attackSpeed = 0.7;
    attackRange = 1;
    moveSpeed = 0.5;
    return true;
}

//满血
void Snorlax::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
    {
        health = maxHP;
        float percentage_health = 100.0 * health / maxHP;
        healthBar->setPercentage(percentage_health);
    }
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}