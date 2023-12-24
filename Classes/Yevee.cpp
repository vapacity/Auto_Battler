#include "Yevee.h"

//Yevee�ȼ�1
Yevee* Yevee::create(const std::string& filename)
{
    Yevee* yevee = new (std::nothrow) Yevee();
    if (yevee && yevee->initWithFile(filename) && yevee->init(filename)) {
        yevee->autorelease();
        return yevee;
    }
    CC_SAFE_DELETE(yevee);
    return nullptr;
}

bool Yevee::init(const std::string& filename)
{
    if (!Node::init()) {
        return false;
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

//�������ι���
void Yevee::useSkill()
{
    skillCount++;
    if (skillCount > 2) {//�����λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
}

void Yevee::getHurt(int ATK)
{
    if(!enable_skill)//�ż���ʱ�����˺�
    {
        this->health -= ATK;
        float percentage_health = 100.0 * health / maxHP;
        if (percentage_health < 0)
            percentage_health = 0;
        healthBar->setPercentage(percentage_health);

        if (!enable_skill)
        {
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
}


