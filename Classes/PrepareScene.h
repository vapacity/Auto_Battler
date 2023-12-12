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
    // 创建场景的静态方法
    static cocos2d::Scene* createScene();
    

    // 初始化场景的方法
    virtual bool init();
    //添加背景图片
    void initBackground();

    // 实现 "static create()" 方法，用于创建对象
    CREATE_FUNC(PrepareScene);

    void onMouseMove(Event* event);
};

#endif // __PREPARE_SCENE_H__
