#pragma once

#ifndef __SETMENU_SCENE_H__
#define __SETMENU_SCENE_H__

#include "cocos2d.h"

class SetMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//创建场景

    virtual bool init();//初始化
    void initMusic();//初始化音量滑动条
    void initAudio();//初始化音效
    void initBack();//初始化返回按钮
    void initTopic();//初始化标题
    void initBackground();//初始化背景

    void menuFirstCallback(Ref* pSender);//返回初始场景
    CREATE_FUNC(SetMenu);
};

#endif // __SETMENU_SCENE_H__