#include "Squirtle.h"
//Squirtle1 等级1
Squirtle* Squirtle::create(const std::string& filename)
{
    Squirtle* squirtle = new (std::nothrow) Squirtle();
    if (squirtle && squirtle->initWithFile(filename) && squirtle->init(filename)) {
        squirtle->autorelease();
        return squirtle;
    }
    CC_SAFE_DELETE(squirtle);
    return nullptr;
}

bool Squirtle::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR2_GRADE1;
    originalCost = price;
    this->name = filename;
    this->id = 22;
    this->star = 1;

    isMelee = 0;
    ATK = 80;
    growATK = 80;
    health = 500;
    growHP = 600;
    blueBar = 100;
    attackSpeed = 0.9;
    attackRange = 4;
    moveSpeed = 1;
    return true;
}

//打200*star
void Squirtle::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
    {
        ATK = 200 * star;
    }
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        ATK = 80;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}