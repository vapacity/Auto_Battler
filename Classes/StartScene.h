
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "PlayMenuScene.h"
#include "SetMenuScene.h"
#include "AudioManager.h"

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//创建场景

    virtual bool init();//初始化
    void initMenu();
    void initBackground();
    void initTopic();

    void menuStartCallback(Ref* pSender);//切换到Play场景
    void menuSetCallback(Ref* pSender);//切换到set场景

    void menuCloseCallback(cocos2d::Ref* pSender);//关闭

    CREATE_FUNC(StartScene);
};

#endif // __HELLOWORLD_SCENE_H__
