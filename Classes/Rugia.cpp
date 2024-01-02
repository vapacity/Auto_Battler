#include "Rugia.h"
Rugia* Rugia::create(const std::string& filename)
{
    try {
        Rugia* rugia = new Rugia();
        if (rugia && rugia->initWithFile(filename) && rugia->init(filename)) {
            rugia->autorelease();
            return rugia;
        }
        CC_SAFE_DELETE(rugia);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Rugia::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Rugia initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR3_GRADE1;
    originalCost = price;
    name = filename;
    id = 33;
    star = 1;
    isMelee = 0;
    ATK = 130;
    growATK = 130;
    health = 700;
    growHP = 800;
    blueBar = 40;
    attackSpeed = 1.5;
    attackRange = 7;
    moveSpeed = 0.7;
    return true;
}

//打500*star
void Rugia::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
    {
        ATK = 500 * star;
    }
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        ATK = 130+(star-1)*growATK;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}