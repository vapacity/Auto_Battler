#pragma once

#ifndef __SETMENU_SCENE_H__
#define __SETMENU_SCENE_H__

#include "cocos2d.h"

class SetMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//��������

    virtual bool init();//��ʼ��
    void menuFirstCallback(Ref* pSender);//���س�ʼ����
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);//�ر�

    // implement the "static create()" method manually
    CREATE_FUNC(SetMenu);
};

#endif // __SETMENU_SCENE_H__