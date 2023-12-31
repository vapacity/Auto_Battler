#include "Yevee.h"

//Yevee等级1
Yevee* Yevee::create(const std::string& filename)
{
    try {
        Yevee* yevee = new Yevee();
        if (yevee && yevee->initWithFile(filename) && yevee->init(filename)) {
            yevee->autorelease();
            return yevee;
        }
        CC_SAFE_DELETE(yevee);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Yevee::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Yevee initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR2_GRADE1;
    originalCost = price;
    name = filename;
    id = 21;
    star = 1;

    isMelee = 1;
    ATK = 70;
    growATK = 50;
    health = 600;
    growHP = 700;
    blueBar = 40;
    attackSpeed = 1;
    attackRange = 1;
    return true;
}

//防御两次攻击
void Yevee::useSkill()
{
    skillCount++;
    if (skillCount > 2) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}

void Yevee::getHurt(int ATK)
{
    if(!enable_skill)//放技能时不被伤害
    {
        this->health -= ATK;
        float percentage_health = 100.0 * health / maxHP;
        if (percentage_health < 0)
            percentage_health = 0;
        healthBar->setPercentage(percentage_health);

        this->currentBlueBar += 5;
        float percentage_blue = 100.0 * currentBlueBar / this->blueBar;
        if (currentBlueBar > this->blueBar)
        {
            this->enable_skill = true;
            percentage_blue = 100.0f;
        }
        bluebar->setPercentage(percentage_blue);
    }
}


