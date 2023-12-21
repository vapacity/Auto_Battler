// HelloWorld.h

#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include "cocos2d.h"
#include "network/WebSocket.h"

class HelloWorld : public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate {
public:
    HelloWorld();
    ~HelloWorld();

    // WebSocket»Øµ÷º¯Êý
    void onOpen(cocos2d::network::WebSocket* ws);
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    void onClose(cocos2d::network::WebSocket* ws);
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);

    CREATE_FUNC(HelloWorld);

private:
    cocos2d::network::WebSocket* webSocket_;
};

#endif // __HELLOWORLD_H__
