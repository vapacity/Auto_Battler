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
    // WebSocket�ص�����
    void onOpen(cocos2d::network::WebSocket* ws);
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    void onClose(cocos2d::network::WebSocket* ws);
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

    // ������ʼ������
    virtual bool init();
    
    // ��ʼ��WebSocket����
    void initWeb();
    
    // ��ʼ����ť
    void initButton();
    
    // ��ʼ������
    void initBackground();
    
    // ��ʼ�����
    void initPlayer();
    
    // ��ʼ�����1
    void initPlayer1();
    
    // ��ʼ�����2
    void initPlayer2();
    
    // ׼����ť����ص�����
    void onReadyButtonClick(cocos2d::Ref* sender);
    
    // �л���׼������
    void goToPreparScne();

    // ���������ĺ궨��
    CREATE_FUNC(WaitingRoomScene);

private:
    Player* myPlayer;       // ��Ҷ���
    Player* enemyPlayer;    // �з���Ҷ���
    cocos2d::network::WebSocket* webSocket_;  // WebSocket���Ӷ���
    int isPlayer1 = 0;      // 1��ʾ���1�Ѵ���
    Sprite* backGround;     // ��������
};

#endif // __WAITING_ROOM_SCENE_H__
