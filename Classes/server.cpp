#include "cocos2d.h"
#include "network/WebSocket.h"

class HelloWorld : public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate {
public:
    HelloWorld() {
        // 创建WebSocket连接
        webSocket_ = new cocos2d::network::WebSocket();
        webSocket_->init(*this, "ws://100.81.177.2:3000"); // 替换为你的服务器地址和端口号
    }

    ~HelloWorld() {
        // 关闭WebSocket连接
        webSocket_->close();
    }

    // WebSocket回调函数
    void onOpen(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket connected");
    }

    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
        // 处理收到的消息
        CCLOG("Received message: %s", data.bytes);
    }

    void onClose(cocos2d::network::WebSocket* ws) {
        CCLOG("WebSocket closed");
    }

    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
        CCLOG("WebSocket error: %d", static_cast<int>(error));
    }

private:
    cocos2d::network::WebSocket* webSocket_;
};