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
USING_NS_CC;

class FightScene:public cocos2d::Scene
{
public:
	Player* myPlayer = PlayerManager::getInstance()->getPlayer(0);
	Player* enemyPlayer = PlayerManager::getInstance()->getPlayer(0);

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

    //创建棋子样例
    void initChessExp();

    //棋子移动函数
    void moveChess(Chess* chessToMove, bool& stopMoveFlag);

    //棋子判断是否有敌人进入了攻击范围
    bool judgeAttack(Vector<HexCell*> movePath);

    //判断棋子是否全部停止移动
    bool judgeAllStop();

    //对棋盘上的所有棋子遍历，开始索敌，直到有敌人进入了攻击范围
    void battleBegin();
    CREATE_FUNC(FightScene);

};
#endif