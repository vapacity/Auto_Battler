#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "PlayerManager.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "Store.h"
#include "LittleHero.h"
#include "AudioManager.h"
#include "PrepareScene.h"
#include "GameOverScene.h"
USING_NS_CC;

class FightScene :public cocos2d::Scene
{
public:
    Player* myPlayer;
    Player* enemyPlayer;

    Sprite* backgroundImg;//背景图片
    GridMap* gridMap;//棋盘
    //Chess* selectedChess;
    //EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;//备战席
    Store* store;//商店
    LittleHero* myLittleHero;//我方小小英雄
    LittleHero* enemyLittleHero;//敌方小小英雄，这个感觉不需要

    Vector<FiniteTimeAction*> actions;
public:
    // 创建场景的静态方法
    static cocos2d::Scene* createScene();

    // 初始化场景的方法
    virtual bool init() override;

    //创建玩家
    void initPlayer();

    //添加背景图片
    void initBackground();

    // 创建棋格
    void initGridMap();

    //创建备战席
    void initPreparationSeats();

    //创建小小英雄
    void initLittleHero();

    //创建商店
    void initStore();

   //建立棋盘上的棋子
    void createChessOnGrids();


    //在战斗场景中每帧更新
    void update(float dt);

    //判定单场结果
    void updateWin(float dt);

    //回到准备界面
    void goToPrepareScene();

    //游戏结束界面
    void goToGameOverScene();
    CREATE_FUNC(FightScene);

};
#endif