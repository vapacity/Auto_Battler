#pragma once

#ifndef __SETMENU_SCENE_H__
#define __SETMENU_SCENE_H__

#include "cocos2d.h"

class SetMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//��������

    virtual bool init();//��ʼ��
    void initMusic();//��ʼ������������
    void initAudio();//��ʼ����Ч
    void initBack();//��ʼ�����ذ�ť
    void initTopic();//��ʼ������
    void initBackground();//��ʼ������

    void menuFirstCallback(Ref* pSender);//���س�ʼ����
    CREATE_FUNC(SetMenu);
};

#endif // __SETMENU_SCENE_H__