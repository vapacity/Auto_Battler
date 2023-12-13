// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "storeLayer.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Sprite* backgroundImg;
    GridMap* gridMap;
    Chess* selectedChess;
    EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;
    storeLayer* store;
public:
    // 创建场景的静态方法
    static cocos2d::Scene* createScene();
    
    // 初始化场景的方法
    virtual bool init();

    //添加背景图片
    void initBackground();

    // 创建棋格
    void initGridMap();

    //创建备战席
    void initPreparationSeats();

    //创建棋子样例
    void initChessExp();

    //创建商店
    void initStore();

    //以下是监听鼠标信息的函数
    //启用鼠标监听器
    void enableMouseListener();

    //禁用鼠标监听器
    void disableMouseListener();

  
    void prepareSceneOnMouseDown(Event* event);
    void prepareSceneOnMouseMove(Event* event);
    void prepareSceneOnMouseUp(Event* event);

    // 实现 "static create()" 方法，用于创建对象
    CREATE_FUNC(PrepareScene);

};

#endif // __PREPARE_SCENE_H__
