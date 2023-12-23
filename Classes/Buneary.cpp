#include "Buneary.h"


Buneary* Buneary::create(const std::string& filename)
{
    Buneary* buneary = new (std::nothrow) Buneary();
    if (buneary && buneary->initWithFile(filename) && buneary->init(filename)) {
        buneary->autorelease();
        return buneary;
    }
    CC_SAFE_DELETE(buneary);
    return nullptr;
}

bool Buneary::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    originalCost = price;
    name = filename;
    id = 12;
    star = 1;

    isMelee = 1;
    ATK = 40;
    growATK = 30;
    health = 500;
    growHP = 600;
    blueBar = 50;
    attackSpeed = 1;
    attackRange = 1;
    moveSpeed = 2;
    return true;
}

//3�ι���+20%
void Buneary::useSkill()
{
    skillCount++;
    if (skillCount == 1)//��һ���ü���ʱ������ֵ��֮�󲻶�
        ATK *= 1.2;
    if (skillCount > 3) {//�������λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        ATK /= 1.2;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}