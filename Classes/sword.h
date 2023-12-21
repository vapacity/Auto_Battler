#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SwordEffect : public Node {
public:
    virtual bool init() override {
        if (!Node::init()) {
            return false;
        }

         //创建粒子系统
        auto particleSystem = ParticleSystemQuad::create("gala.png");
        //particleSystem->setAutoRemoveOnFinish(true);  // 粒子播放完毕后自动移除

         //设置粒子的位置
        particleSystem->setPosition(Vec2(0, 0));
        
        // 将粒子系统添加到当前节点
        this->addChild(particleSystem);

        return true;
    }

    // 静态创建函数
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