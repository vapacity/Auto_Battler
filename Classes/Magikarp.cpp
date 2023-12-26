#include "Magikarp.h"
Magikarp* Magikarp::create(const std::string& filename)
{
    Magikarp* magikarp = new (std::nothrow) Magikarp();
    if (magikarp && magikarp->initWithFile(filename) && magikarp->init(filename)) {
        magikarp->autorelease();
        return magikarp;
    }
    CC_SAFE_DELETE(magikarp);
    return nullptr;
}

bool Magikarp::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
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
    attackSpeed = 1.1;
    attackRange = 3;
    moveSpeed = 0.7;
    return true;
}
//��60*star
void Magikarp::useSkill()
{
    skillCount++;
    if (skillCount == 1)//��һ���ü���ʱ������ֵ��֮�󲻶�
    {
        ATK = 60 * star;
    }
    if (skillCount > 1) {//�����λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        ATK = 50;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}