#include "Mewtwo.h"
Mewtwo* Mewtwo::create(const std::string& filename)
{
    try {
        Mewtwo* mewtwo = new Mewtwo();
        if (mewtwo && mewtwo->initWithFile(filename) && mewtwo->init(filename)) {
            mewtwo->autorelease();
            return mewtwo;
        }
        CC_SAFE_DELETE(mewtwo);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Mewtwo::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Mewtwo initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR3_GRADE1;
    originalCost = price;
    name = filename;
    id = 32;
    star = 1;

    isMelee = 0;
    ATK = 100;
    growATK = 100;
    health = 1000;
    growHP = 1200;
    blueBar = 50;
    attackSpeed = 1.2;
    attackRange = 2;
    moveSpeed = 3.5;
    return true;
}

//打300*star
void Mewtwo::useSkill()
{
    skillCount++;
    if (skillCount == 1)//第一次用技能时更新数值，之后不动
    {
        ATK = 300 * star;
    }
    if (skillCount > 1) {//超过次恢复原值，技能停用，蓝条清零，技能使用次数清零
        ATK = 100+(star-1)*growATK;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
    else
        cocos2d::experimental::AudioEngine::play2d("mewtwoEffect.mp3", false);
}