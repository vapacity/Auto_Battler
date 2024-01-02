#include "Jingglypuff.h"


Jingglypuff* Jingglypuff::create(const std::string& filename)
{
    try {
        Jingglypuff* jingglypuff = new Jingglypuff();
        if (jingglypuff && jingglypuff->initWithFile(filename) && jingglypuff->init(filename)) {
            jingglypuff->autorelease();
            return jingglypuff;
        }
        CC_SAFE_DELETE(jingglypuff);
    }
    catch (const std::exception& e) {
        // �����쳣ʱ�Ĵ����߼�
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Jingglypuff::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Jingglypuff initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    price = PRICE_STAR1_GRADE1;
    originalCost = price;
    name = filename;
    id = 13;
    star = 1;

    isMelee = 1;
    ATK = 20;
    growATK = 30;
    health = 600;
    growHP = 700;
    blueBar = 70;
    attackSpeed = 0.8;
    attackRange = 1;
    moveSpeed = 1;
    return true;
}
 
//��Ѫ50%
void Jingglypuff::useSkill()
{
    skillCount++;
    if (skillCount == 1)//��һ���ü���ʱ������ֵ��֮�󲻶�
    {
        health = (health + maxHP / 2) > maxHP ? maxHP : health + maxHP / 2;
        float percentage_health = 100.0 * health / maxHP;
        healthBar->setPercentage(percentage_health);
    }
    if (skillCount > 1) {//�����λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}