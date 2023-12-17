// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "PlayerManager.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "Store.h"
#include "LittleHero.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Player* myPlayer = PlayerManager::getInstance()->getPlayer(0);

    Sprite* backgroundImg;
    GridMap* gridMap;
    Chess* selectedChess;
    EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;
    Store* store;
    LittleHero* littleHero;
    LittleHero* littleHeroEnemy;
public:
    //输出人口上限不足的提示，并在一段时间后自动移除
    void noPopulationText();
    float elapsedTime = 0.0f;
    Label* fadingText;
    //noPopulationText的调度器用，使提示逐渐淡出
    void updateText(float dt);

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

    //创建小小英雄
    void initLittleHero();

    //创建棋子样例
    void initChessExp();

    //创建商店
    void initStore();

    //以下是监听鼠标信息的函数
    //启用鼠标监听器
    void enableMouseListener();

    //禁用鼠标监听器
    void disableMouseListener();

    //鼠标监听函数
    void prepareSceneOnMouseDown(Event* event);
    void prepareSceneOnMouseMove(Event* event);
    void prepareSceneOnMouseUp(Event* event);

    //对拖拽chess类的prepareScene监听函数拆分
    void chessOnMouseDown(Vec2 mousePosition);
    void chessOnMouseMove(Vec2 mousePosition);
    void chessOnMouseUp(Vec2 mousePosition);

    //检查三合一并合成
    void checkAndMerge(Chess* chess);
    Chess* upgradeChess(const int chessId);
    // 实现 "static create()" 方法，用于创建对象
    CREATE_FUNC(PrepareScene);

};

#endif // __PREPARE_SCENE_H__
