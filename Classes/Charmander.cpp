#include "Charmander.h"

//Charmandeer1 �ȼ�1
Charmander* Charmander::create(const std::string& filename)
{
    Charmander* charmander = new (std::nothrow) Charmander();
    if (charmander && charmander->initWithFile(filename) && charmander->init(filename)) {
        charmander->autorelease();
        return charmander;
    }
    CC_SAFE_DELETE(charmander);
    return nullptr;
}

bool Charmander::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR2_GRADE1;
    originalCost = price;
    this->name = filename;
    this->id = 23;
    this->star = 1;

    isMelee = 1;
    ATK = 60;
    growATK = 40;
    health = 800;
    growHP = 900;
    blueBar = 50;
    attackSpeed = 1;
    attackRange = 1;
    moveSpeed = 1.5;
    return true;
}
//��100*star
void Charmander::useSkill()
{
    skillCount++;
    if (skillCount == 1)//��һ���ü���ʱ������ֵ��֮�󲻶�
        ATK = 100 * star;
    if (skillCount > 1) {//�����λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        ATK = 60;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}