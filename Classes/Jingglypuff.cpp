#include "Jingglypuff.h"


Jingglypuff* Jingglypuff::create(const std::string& filename)
{
    try {
        Jingglypuff* jingglypuff = new Jingglypuff();
        if (jingglypuff && jingglypuff->initWithFile(filename) && jingglypuff->init(filename)) {
            jingglypuff->autorelease();
            return jingglypuff;
        }
        CC_SAFE_DELETE(jingglypuff);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Jingglypuff::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Jingglypuff initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    originalCost = price;
    name = filename;
    id = 13;
    star = 1;

    isMelee = 1;
    ATK = 20;
    growATK = 30;
    health = 600;
    growHP = 700;
    blueBar = 70;
    attackSpeed = 0.8;
    attackRange = 1;
    moveSpeed = 1;
    return true;
}
 
//回血50%
void Jingglypuff::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
    {
        health = (health + maxHP / 2) > maxHP ? maxHP : health + maxHP / 2;
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