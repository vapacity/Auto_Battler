
#include "HelloWorld.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#define  Midpoint Vec2(640,360)
USING_NS_CC;
HelloWorld::HelloWorld() {
    // 创建WebSocket连接
    webSocket_ = new cocos2d::network::WebSocket();
    webSocket_->init(*this, "ws://100.81.177.2:3000"); // 替换为你的服务器地址和端口号
    //webSocket_->send(message);
}

HelloWorld::~HelloWorld() {
    // 关闭WebSocket连接
    webSocket_->close();
}

// WebSocket回调函数的实现
void HelloWorld::onOpen(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket connected");
    setLittleHero();
    //sendLittleHeroPosition();
}

void HelloWorld::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) {
    // 处理收到的消息
    CCLOG("Received message: %s", data.bytes);
    std::string message(data.bytes, data.len);
    syncUpdateLittleHero(message);
}

void HelloWorld::onClose(cocos2d::network::WebSocket* ws) {
    CCLOG("WebSocket closed");
}

void HelloWorld::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) {
    CCLOG("WebSocket error: %d", static_cast<int>(error));
}

void HelloWorld::setLittleHero()
{
    enemyHero = LittleHero::create();
    enemyHero->setEnemy();
    enemyHero->setPosition(Vec2(1180, 470));
    this->addChild(enemyHero);
    littleHero = LittleHero::create();
    littleHero->setPosition(Vec2(100, 250));
    this->addChild(littleHero);
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(HelloWorld::moveToClickLocation, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void HelloWorld::sendLittleHeroPosition()
{
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("type", "position_update", allocator);
    doc.AddMember("x", littleHero->getPositionX(), allocator);
    doc.AddMember("y", littleHero->getPositionY(), allocator);

    // 将 JSON 转为字符串
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::string message = buffer.GetString();

    // 发送消息给服务器
    if (webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN) {
        webSocket_->send(message);
    }
}

void HelloWorld::syncUpdateLittleHero(const std::string& message)
{
    rapidjson::Document doc;
    doc.Parse(message.c_str());

    if (!doc.HasParseError() && doc.IsObject()) {
        // 确保消息类型是位置更新
        if (doc.HasMember("type") && doc["type"].IsString() && doc["type"] == "position_update") {
            // 确保 JSON 中有 x 和 y 属性
            if (doc.HasMember("x") && doc.HasMember("y") && doc["x"].IsFloat() && doc["y"].IsFloat()) {
                // 从 JSON 中读取属性并更新 LittleHero 的位置
                float x = doc["x"].GetFloat();
                float y = doc["y"].GetFloat();
                x = 2 * Midpoint.x - x;
                y = 2 * Midpoint.y - y;
                // 假设 LittleHero 有 setPosition 方法
                enemyHero->stopAllActions();
                float speed = 500.0f;
                Vec2 currentposition = littleHero->getPosition();
                // 计算鼠标点击位置相对于当前位置的相对位移
                Vec2 targetposition = Vec2(x, y);
                Vec2 movedelta = targetposition - currentposition;
                float distance = movedelta.length();
                float duration = distance / speed;
                auto moveto = MoveTo::create(duration, targetposition);
                enemyHero->runAction(moveto);
            }
        }
    }
}

void HelloWorld::moveToClickLocation(cocos2d::EventMouse* event)
{
  
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        littleHero->stopAllActions();
        // 创建一个moveto动作，移动到点击位置
        Vec2 currentposition = littleHero->getPosition();

        // 计算鼠标点击位置相对于当前位置的相对位移
        Vec2 targetposition(event->getCursorX(), event->getCursorY());
        Vec2 movedelta = targetposition - currentposition;

        float distance = movedelta.length();

        // 计算匀速移动的时间（假设速度为300像素/秒）
        float speed = 500.0f;
        float duration = distance / speed;

        // 创建moveby动作，匀速移动到相对位移位置
        auto moveto = MoveTo::create(duration, targetposition);

        littleHero->runAction(moveto);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

        doc.AddMember("type", "position_update", allocator);
        doc.AddMember("x", targetposition.x, allocator);
        doc.AddMember("y", targetposition.y, allocator);

        // 将 JSON 转为字符串
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::string message = buffer.GetString();

        // 发送消息给服务器
        if (webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN) {
            webSocket_->send(message);
        }
    }
}

//bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
//{
//    cocos2d::Vec2 touchPos = touch->getLocation();
//    rapidjson::Document doc;
//    doc.SetObject();
//    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
//
//    doc.AddMember("type", "position_update", allocator);
//    doc.AddMember("x", touchPos.x, allocator);
//    doc.AddMember("y", touchPos.y, allocator);
//
//    // 将 JSON 转为字符串
//    rapidjson::StringBuffer buffer;
//    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//    doc.Accept(writer);
//    std::string message = buffer.GetString();
//
//    // 发送消息给服务器
//    if (webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN) {
//        webSocket_->send(message);
//    }
//    return true;
//}
