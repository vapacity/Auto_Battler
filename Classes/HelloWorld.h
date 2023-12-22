// HelloWorld.h

#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include "cocos2d.h"
#include "network/WebSocket.h"
#include "LittleHero.h"
class HelloWorld : public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate {
public:
    HelloWorld();
    ~HelloWorld();

    // WebSocket»Øµ÷º¯Êý
    void onOpen(cocos2d::network::WebSocket* ws);
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    void onClose(cocos2d::network::WebSocket* ws);
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    void setLittleHero();
    void sendLittleHeroPosition();
    void syncUpdateLittleHero(const std::string& message);
    void moveToClickLocation(cocos2d::EventMouse* event);
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::network::WebSocket* webSocket_;
    LittleHero* littleHero;
    LittleHero* enemyHero;
};

#endif // __HELLOWORLD_H__
