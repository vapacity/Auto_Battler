#pragma once

#ifndef __HUMAN_PLAY_H__
#define __HUMAN_PLAY_H__

#include "cocos2d.h"

class HumanPlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//��������

    virtual bool init();//��ʼ��
    void menuPlayMenuCallback(Ref* pSender);//�ص�play����
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);//�ر�

    // implement the "static create()" method manually
    CREATE_FUNC(HumanPlayScene);
};

#endif // __HUMAN_PLAY_H__