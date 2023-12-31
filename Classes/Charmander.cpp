#include "Charmander.h"

//Charmandeer1 等级1
Charmander* Charmander::create(const std::string& filename)
{
    try {
        Charmander* charmander = new Charmander();
        if (charmander && charmander->initWithFile(filename) && charmander->init(filename)) {
            charmander->autorelease();
            return charmander;
        }
        CC_SAFE_DELETE(charmander);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Charmander::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Charmander initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR2_GRADE1;
    originalCost = price;
    this->name = filename;
    this->id = 23;
    this->star = 1;

    isMelee = 1;
    ATK = 60;
    growATK = 40;
    health = 800;
    growHP = 900;
    blueBar = 50;
    attackSpeed = 1;
    attackRange = 1;
    moveSpeed = 1.5;
    return true;
}
//打100*star
void Charmander::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
        ATK = 100 * star;
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        ATK = 60+ (star - 1) * growATK;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}