// BlueBar.cpp
#include "BlueBar.h"

USING_NS_CC;

BlueBar::BlueBar()
    : blueBar(nullptr)
{  
}

BlueBar* BlueBar::create(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    try {
        BlueBar* blueBar = new  BlueBar();
        if (blueBar && blueBar->init(backgroundFilename, barFilename, initialPercentage))
        {
            blueBar->autorelease();
            return blueBar;
        }
    }
    catch (const std::exception& e) {
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

bool BlueBar::init(const std::string& backgroundFilename, const std::string& barFilename, float initialPercentage)
{
    if (!Node::init())
    {
        throw std::runtime_error("BlueBar initialization failed: Node initialization failed");
    }

    // �������� Sprite
    auto backgroundSprite = Sprite::create(backgroundFilename); //ʹ�ø����� backgroundFilename ��Ϊ����
    backgroundSprite->setContentSize(Size(100, 10)); //�������СΪ(100, 10)
    backgroundSprite->setAnchorPoint(Vec2(0, 0));//ê��Ϊ���½ǣ�0, 0��
    backgroundSprite->setPosition(Vec2(0, 0));//λ��Ϊ(0, 0)
    this->addChild(backgroundSprite); //��������� Sprite ��ӵ� BlueBar ������

    // ���� ProgressTimer������Դ Sprite ����Ϊ����ʾ����
    auto sprite = Sprite::create(barFilename);
    sprite->setContentSize(Size(100, 10));
    blueBar = ProgressTimer::create(sprite);//����һ�����������󣬲�����ǰ������ Sprite ��������Ϊ����ʾ����
    blueBar->setAnchorPoint(Vec2(0, 0));
    blueBar->setType(ProgressTimer::Type::BAR);//ˮƽ������
    blueBar->setMidpoint(Vec2(0, 0.5));//������
    blueBar->setBarChangeRate(Vec2(1, 0));//�仯�ʣ�ֻ��ˮƽ�����ϳ���
    blueBar->setPosition(Vec2(0, 0));
    blueBar->setPercentage(initialPercentage);
    this->addChild(blueBar);

    return true;
}

void BlueBar::setPercentage(float percentage)
{
    // ���������İٷֱ�
    if (this)
        blueBar->setPercentage(percentage);
}