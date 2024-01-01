#pragma once
#ifndef __WAITING_ROOM_SCENE_H__
#define __WAITING_ROOM_SCENE_H__

#include "cocos2d.h"
#include "LittleHero.h"
#include "network/WebSocket.h"
#include "PlayerManager.h"
#include "OnlinePrepareScene.h"

class WaitingRoomScene : public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate
{
public:
    // WebSocket回调函数
    void onOpen(cocos2d::network::WebSocket* ws);
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    void onClose(cocos2d::network::WebSocket* ws);
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

    // 场景初始化函数
    virtual bool init();
    
    // 初始化WebSocket连接
    void initWeb();
    
    // 初始化按钮
    void initButton();
    
    // 初始化背景
    void initBackground();
    
    // 初始化玩家
    void initPlayer();
    
    // 初始化玩家1
    void initPlayer1();
    
    // 初始化玩家2
    void initPlayer2();
    
    // 准备按钮点击回调函数
    void onReadyButtonClick(cocos2d::Ref* sender);
    
    // 切换到准备场景
    void goToPreparScne();

    // 创建场景的宏定义
    CREATE_FUNC(WaitingRoomScene);

private:
    Player* myPlayer;       // 玩家对象
    Player* enemyPlayer;    // 敌方玩家对象
    cocos2d::network::WebSocket* webSocket_;  // WebSocket连接对象
    int isPlayer1 = 0;      // 1表示玩家1已存在
    Sprite* backGround;     // 背景精灵
};

#endif // __WAITING_ROOM_SCENE_H__
