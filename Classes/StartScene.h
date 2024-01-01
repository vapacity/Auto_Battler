
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
    static cocos2d::Scene* createScene();//��������

    virtual bool init();//��ʼ��
    void initMenu();
    void initBackground();
    void initTopic();

    void menuStartCallback(Ref* pSender);//�л���Play����
    void menuSetCallback(Ref* pSender);//�л���set����

    void menuCloseCallback(cocos2d::Ref* pSender);//�ر�

    CREATE_FUNC(StartScene);
};

#endif // __HELLOWORLD_SCENE_H__
