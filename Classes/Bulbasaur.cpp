#include "Bulbasaur.h"

Bulbasaur* Bulbasaur::create(const std::string& filename)
{
    try {
        Bulbasaur* bulbasaur = new Bulbasaur();
        if (bulbasaur && bulbasaur->initWithFile(filename) && bulbasaur->init(filename)) {
            bulbasaur->autorelease();
            return bulbasaur;
        }
        CC_SAFE_DELETE(bulbasaur);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Bulbasaur::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Bulbasaur initialization failed: Node initialization failed");
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
        ATK = 40+(star-1)*growATK;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
    else
        cocos2d::experimental::AudioEngine::play2d("bulbasaurEffect.mp3", false); 
}