
#include "HelloWorld.h"

USING_NS_CC;

HelloWorld::HelloWorld() {
    // ����WebSocket����
    webSocket_ = new cocos2d::network::WebSocket();
    webSocket_->init(*this, "ws://100.81.177.2:3000"); // �滻Ϊ��ķ�������ַ�Ͷ˿ں�
}

HelloWorld::~HelloWorld() {
    // �ر�WebSocket����
    webSocket_->close();
}

// WebSocket�ص�������ʵ��
void HelloWorld::onOpen(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket connected");
}

void HelloWorld::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
    // �����յ�����Ϣ
    CCLOG("Received message: %s", data.bytes);
}

void HelloWorld::onClose(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket closed");
}

void HelloWorld::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
    CCLOG("WebSocket error: %d", static_cast<int>(error));
}
