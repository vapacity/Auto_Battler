#include "WaitingRoomScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;

// WebSocket连接打开时的回调函数
void WaitingRoomScene::onOpen(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket connection opened");
}

// 接收到WebSocket消息时的回调函数
void WaitingRoomScene::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
    CCLOG("Received message: %s", data.bytes);

    // 将接收到的消息转换为字符串
    std::string message(data.bytes, data.len);

    // 根据不同的消息内容进行处理
    if (message == "Player1") {
        myPlayer->playerNumber = 0;
        enemyPlayer->playerNumber = 1;
        isPlayer1 = 1;
        initPlayer1();
        return;
    }
    if (message == "Player2") {
        //若玩家1存在，初始化玩家2就返回
        if (isPlayer1 == 1) {
            initPlayer2();
            return;
        }
        //不存在，初始化两个
        myPlayer->playerNumber = 1;
        enemyPlayer->playerNumber = 0;
        initPlayer2();
        initPlayer1();
        return;
    }
    if (message == "ENTERGAME") {
        goToPreparScne();
        return;
    }
}

// WebSocket连接关闭时的回调函数
void WaitingRoomScene::onClose(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket connection closed");
}

// WebSocket发生错误时的回调函数
void WaitingRoomScene::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    CCLOG("WebSocket error: %d", static_cast<int>(error));
}

// 场景初始化函数
bool WaitingRoomScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 初始化背景、玩家、WebSocket连接和按钮
    initBackground();
    initPlayer();
    initWeb();
    initButton();

    return true;
}

// 初始化WebSocket连接
void WaitingRoomScene::initWeb()
{
    webSocket_ = new cocos2d::network::WebSocket();

    //连接到服务器
    webSocket_->init(*this, "ws://192.168.43.182:3000");//ws://your_server_address:your_port
}

// 初始化准备按钮
void WaitingRoomScene::initButton()
{
    auto readyButton = cocos2d::MenuItemLabel::create(
        cocos2d::Label::createWithSystemFont("Ready", "fonts/Marker Felt.ttf", 24),
        CC_CALLBACK_1(WaitingRoomScene::onReadyButtonClick, this));

    auto menu = cocos2d::Menu::create(readyButton, nullptr);
    menu->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(menu);
}

// 初始化背景
void WaitingRoomScene::initBackground()
{
    backGround = Sprite::create("WaitingRoomBackground.jpg");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backGround->setScaleX(visibleSize.width / backGround->getContentSize().width);
    backGround->setScaleY(visibleSize.height / backGround->getContentSize().height);
    this->addChild(backGround);
}

// 初始化玩家
void WaitingRoomScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
}

// 初始化玩家1
void WaitingRoomScene::initPlayer1()
{
}

// 初始化玩家2
void WaitingRoomScene::initPlayer2()
{
}

// 准备按钮点击回调函数
void WaitingRoomScene::onReadyButtonClick(cocos2d::Ref* sender)
{
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    if (webSocket_)
    {
        webSocket_->send("READY");
    }
}

// 切换到准备场景
void WaitingRoomScene::goToPreparScne()
{
    //用户离开时执行，以确保正确地关闭网络连接
    if (webSocket_ && webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        webSocket_->close();
    }

    auto prepareScene = OnlinePrepareScene::create();
    cocos2d::Director::getInstance()->replaceScene(prepareScene);
}
