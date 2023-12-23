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

//��Χ2��30*star
void Bulbasaur::useSkill()
{
    skillCount++;
    if (skillCount == 1)//��һ���ü���ʱ������ֵ��֮�󲻶�
        ATK = 30*star;
    if (skillCount > 1) {//�����λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        ATK = 40;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}