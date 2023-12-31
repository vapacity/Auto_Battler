#pragma once

#ifndef __PLAYMENU_SCENE_H__
#define __PLAYMENU_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "StartScene.h"
#include "AudioManager.h"
#include "PrepareScene.h"
#include "WaitingRoomScene.h"

class PlayMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//创建场景

    virtual bool init();//初始化
    void initMenu();
    void initTopic();
    void initBackground();

    void menuMachinePlayCallback(Ref* pSender);//切换到人机场景
    void menuMultiPlayCallback(Ref* pSender);//切换到联机场景-WaitingRoom
    void menuFirstCallback(Ref* pSender);//回到Play场景
    CREATE_FUNC(PlayMenu);
};

#endif // __PLAYMENU_SCENE_H__