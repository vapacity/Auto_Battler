#pragma once
#ifndef __WAITING_ROOM_SCENE_H__
#define __WAITING_ROOM_SCENE_H__

#include "cocos2d.h"
#include "LittleHero.h"
#include "network/WebSocket.h"
#include "PlayerManager.h"
#include "PrepareScene.h"
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
    void WaitingRoomScene::onReadyButtonClick(cocos2d::Ref* sender);
    void goToPreparScne();
    CREATE_FUNC(WaitingRoomScene);
private:
    //Player* myPlayer = PlayerManager::getInstance()->getPlayer(0);
    //Player* enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
    cocos2d::network::WebSocket* webSocket_;
};

#endif // __WAITING_ROOM_SCENE_H__