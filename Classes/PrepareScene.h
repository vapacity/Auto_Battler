// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "PreparationSeats.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Sprite* backgroundImg;
   
public:
    // ���������ľ�̬����
    static cocos2d::Scene* createScene();
    

    // ��ʼ�������ķ���
    virtual bool init();
    //��ӱ���ͼƬ
    void initBackground();

    // ʵ�� "static create()" ���������ڴ�������
    CREATE_FUNC(PrepareScene);

    void onMouseMove(Event* event);
};

#endif // __PREPARE_SCENE_H__
