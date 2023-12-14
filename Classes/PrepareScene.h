// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "Store.h"
#include "LittleHero.h"
#include "Player.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Player* myPlayer;

    Sprite* backgroundImg;
    GridMap* gridMap;
    Chess* selectedChess;
    EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;
    Store* store;
    LittleHero* littleHero;
    LittleHero* littleHeroEnemy;
public:
    // 创建场景的静态方法
    cocos2d::Scene* createScene(Player* myPlayer);
    
    static PrepareScene* create(Player* myPlayer);

    // 初始化场景的方法
    virtual bool init(Player* myPlayer);

    //初始化玩家属性
    void initPlayer(Player* player);

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



};

#endif // __PREPARE_SCENE_H__
