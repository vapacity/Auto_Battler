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
    void onOpen(cocos2d::network::WebSocket* ws);
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    void onClose(cocos2d::network::WebSocket* ws);
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    virtual bool init();
    void initWeb();
    void initButton();
    void initBackground();
    void initPlayer();
    void initPlayer1();
    void initPlayer2();
    void WaitingRoomScene::onReadyButtonClick(cocos2d::Ref* sender);
    void goToPreparScne();
    CREATE_FUNC(WaitingRoomScene);
private:
    Player* myPlayer ;
    Player* enemyPlayer ;
    cocos2d::network::WebSocket* webSocket_;
    int isPlayer1 = 0;
};

#endif // __WAITING_ROOM_SCENE_H__