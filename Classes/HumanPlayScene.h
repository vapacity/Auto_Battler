#pragma once

#ifndef __HUMAN_PLAY_H__
#define __HUMAN_PLAY_H__

#include "cocos2d.h"

class HumanPlayScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//创建场景

    virtual bool init();//初始化
    void menuPlayMenuCallback(Ref* pSender);//回到play场景
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);//关闭

    // implement the "static create()" method manually
    CREATE_FUNC(HumanPlayScene);
};

#endif // __HUMAN_PLAY_H__