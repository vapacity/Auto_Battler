#include "Mewtwo.h"
Mewtwo* Mewtwo::create(const std::string& filename)
{
    Mewtwo* mewtwo = new (std::nothrow) Mewtwo();
    if (mewtwo && mewtwo->initWithFile(filename) && mewtwo->init(filename)) {
        mewtwo->autorelease();
        return mewtwo;
    }
    CC_SAFE_DELETE(mewtwo);
    return nullptr;
}

bool Mewtwo::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
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

//��300*star
void Mewtwo::useSkill()
{
    skillCount++;
    if (skillCount == 1)//��һ���ü���ʱ������ֵ��֮�󲻶�
    {
        ATK = 300 * star;
    }
    if (skillCount > 1) {//�����λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        ATK = 100;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}