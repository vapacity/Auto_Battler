#include "Magikarp.h"
Magikarp* Magikarp::create(const std::string& filename)
{
    try {
        Magikarp* magikarp = new Magikarp();
        if (magikarp && magikarp->initWithFile(filename) && magikarp->init(filename)) {
            magikarp->autorelease();
            return magikarp;
        }
        CC_SAFE_DELETE(magikarp);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Magikarp::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Magikarp initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    originalCost = price;
    name = filename;
    id = 11;
    star = 1;

    isMelee = 0;
    ATK = 50;
    growATK = 30;
    health = 300;
    growHP = 500;
    blueBar = 40;
    attackSpeed = 0.6;
    attackRange = 3;
    moveSpeed = 0.7;
    return true;
}
//打60*star
void Magikarp::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
    {
        ATK = 60 * star;
    }
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        ATK = 50+(star=1)*growATK;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}