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
    static cocos2d::Scene* createScene();//��������

    virtual bool init();//��ʼ��

    void menuMachinePlayCallback(Ref* pSender);//�л����˻�����
    void menuMultiPlayCallback(Ref* pSender);//�л�����������-WaitingRoom
    void menuFirstCallback(Ref* pSender);//�ص�Play����
    CREATE_FUNC(PlayMenu);
};

#endif // __PLAYMENU_SCENE_H__