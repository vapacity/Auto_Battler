#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SwordEffect : public Node {
public:
    virtual bool init() override {
        if (!Node::init()) {
            return false;
        }

         //��������ϵͳ
        auto particleSystem = ParticleSystemQuad::create("gala.png");
        //particleSystem->setAutoRemoveOnFinish(true);  // ���Ӳ�����Ϻ��Զ��Ƴ�

         //�������ӵ�λ��
        particleSystem->setPosition(Vec2(0, 0));
        
        // ������ϵͳ��ӵ���ǰ�ڵ�
        this->addChild(particleSystem);

        return true;
    }

    // ��̬��������
    static SwordEffect* create() {
        SwordEffect* effect = new SwordEffect();
        if (effect && effect->init()) {
            effect->autorelease();
            return effect;
        }
        CC_SAFE_DELETE(effect);
        return nullptr;
    }
};