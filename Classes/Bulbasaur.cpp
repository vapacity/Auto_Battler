#include "Bulbasaur.h"

Bulbasaur* Bulbasaur::create(const std::string& filename)
{
    Bulbasaur* bulbasaur = new (std::nothrow) Bulbasaur();
    if (bulbasaur && bulbasaur->initWithFile(filename) && bulbasaur->init(filename)) {
        bulbasaur->autorelease();
        return bulbasaur;
    }
    CC_SAFE_DELETE(bulbasaur);
    return nullptr;
}

bool Bulbasaur::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR2_GRADE1;
    originalCost = price;
    this->name = filename;
    this->id = 24;
    this->star = 1;

    isMelee = 0;
    ATK = 40;
    growATK = 30;
    health = 800;
    growHP = 1000;
    blueBar = 20;
    attackSpeed = 1;
    attackRange = 2;
    moveSpeed = 1;
    return true;
}

//范围2打30*star
void Bulbasaur::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
        ATK = 30*star;
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        ATK = 40;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}