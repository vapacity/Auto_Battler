#include "Squirtle.h"
//Squirtle1 �ȼ�1
Squirtle* Squirtle::create(const std::string& filename)
{
    try {
        Squirtle* squirtle = new Squirtle();
        if (squirtle && squirtle->initWithFile(filename) && squirtle->init(filename)) {
            squirtle->autorelease();
            return squirtle;
        }
        CC_SAFE_DELETE(squirtle);
    }
    catch (const std::exception& e) {
        // �����쳣ʱ�Ĵ����߼�
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool Squirtle::init(const std::string& filename)
{
    if (!Node::init()) {
        throw std::runtime_error("Squirtle initialization failed: Node initialization failed");
    }
    this->setScale(SET_SCALE);
    this->price = PRICE_STAR2_GRADE1;
    originalCost = price;
    this->name = filename;
    this->id = 22;
    this->star = 1;

    isMelee = 0;
    ATK = 80;
    growATK = 80;
    health = 500;
    growHP = 600;
    blueBar = 100;
    attackSpeed = 0.9;
    attackRange = 4;
    moveSpeed = 1;
    return true;
}

//��200*star
void Squirtle::useSkill()
{
    skillCount++;
    if (skillCount == 1)//��һ���ü���ʱ������ֵ��֮�󲻶�
    {
        ATK = 200 * star;
    }
    if (skillCount > 1) {//�����λָ�ԭֵ������ͣ�ã��������㣬����ʹ�ô�������
        ATK = 80+(star-1)*growATK;
        enable_skill = false;
        currentBlueBar = 0;
        bluebar->setPercentage(0);
        skillCount = 0;
    }
    else
        cocos2d::experimental::AudioEngine::play2d("squirtleEffect.mp3", false);
}