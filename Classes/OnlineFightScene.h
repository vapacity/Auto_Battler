#ifndef __ONLINE_FIGHT_SCENE_H__
#define __ONLINE_FIGHT_SCENE_H__

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
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/WebSocket.h"
#include "OnlinePrepareScene.h"

USING_NS_CC;

class OnlineFightScene :public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate
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

    //创建棋子
    void createChessOnGrids();

    //在战斗场景中每帧更新
    void update(float dt);

    void enableMouseListener();

    //判定单场结果
    void updateWin(float dt);

    //回到准备界面
    void goToPrepareScene();

    //游戏结束界面
    void goToGameOverScene();

    //初始化WebSocket连接
    void initWeb();

    //发送棋子信息到服务器
    void sendChessInfoToServer();

    //处理WebSocket连接打开时的事件
    void onOpen(cocos2d::network::WebSocket* ws);

    //处理接收到WebSocket消息时的事件
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    
    //处理WebSocket连接关闭时的事件
    void onClose(cocos2d::network::WebSocket* ws);
    
    //处理WebSocket错误时的事件
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    
    //处理战斗场景中鼠标点击事件
    void fightSceneOnMouseDown(Event* event);
    
    CREATE_FUNC(OnlineFightScene);
private:
    
    cocos2d::network::WebSocket* webSocket_;//存储WebSocket连接的指针
   
    EventListenerMouse* prepareSceneMouseListener;//存储鼠标事件监听器的指针
};
#endif