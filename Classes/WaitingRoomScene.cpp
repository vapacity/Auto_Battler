#include "WaitingRoomScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;

// WebSocket���Ӵ�ʱ�Ļص�����
void WaitingRoomScene::onOpen(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket connection opened");
}

// ���յ�WebSocket��Ϣʱ�Ļص�����
void WaitingRoomScene::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
    CCLOG("Received message: %s", data.bytes);

    // �����յ�����Ϣת��Ϊ�ַ���
    std::string message(data.bytes, data.len);

    // ���ݲ�ͬ����Ϣ���ݽ��д���
    if (message == "Player1") {
        myPlayer->playerNumber = 0;
        enemyPlayer->playerNumber = 1;
        isPlayer1 = 1;
        initPlayer1();
        return;
    }
    if (message == "Player2") {
        //�����1���ڣ���ʼ�����2�ͷ���
        if (isPlayer1 == 1) {
            initPlayer2();
            return;
        }
        //�����ڣ���ʼ������
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

// WebSocket���ӹر�ʱ�Ļص�����
void WaitingRoomScene::onClose(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket connection closed");
}

// WebSocket��������ʱ�Ļص�����
void WaitingRoomScene::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    CCLOG("WebSocket error: %d", static_cast<int>(error));
}

// ������ʼ������
bool WaitingRoomScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ��ʼ����������ҡ�WebSocket���ӺͰ�ť
    initBackground();
    initPlayer();
    initWeb();
    initButton();

    return true;
}

// ��ʼ��WebSocket����
void WaitingRoomScene::initWeb()
{
    webSocket_ = new cocos2d::network::WebSocket();

    //���ӵ�������
    webSocket_->init(*this, "ws://192.168.43.182:3000");//ws://your_server_address:your_port
}

// ��ʼ��׼����ť
void WaitingRoomScene::initButton()
{
    auto readyButton = cocos2d::MenuItemLabel::create(
        cocos2d::Label::createWithSystemFont("Ready", "fonts/Marker Felt.ttf", 24),
        CC_CALLBACK_1(WaitingRoomScene::onReadyButtonClick, this));

    auto menu = cocos2d::Menu::create(readyButton, nullptr);
    menu->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(menu);
}

// ��ʼ������
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

// ��ʼ�����
void WaitingRoomScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
}

// ��ʼ�����1
void WaitingRoomScene::initPlayer1()
{
}

// ��ʼ�����2
void WaitingRoomScene::initPlayer2()
{
}

// ׼����ť����ص�����
void WaitingRoomScene::onReadyButtonClick(cocos2d::Ref* sender)
{
    if (isAudioEnabled)
    {// ������Ч
        playSoundEffect("myEffect.mp3");
    }
    if (webSocket_)
    {
        webSocket_->send("READY");
    }
}

// �л���׼������
void WaitingRoomScene::goToPreparScne()
{
    //�û��뿪ʱִ�У���ȷ����ȷ�عر���������
    if (webSocket_ && webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        webSocket_->close();
    }

    auto prepareScene = OnlinePrepareScene::create();
    cocos2d::Director::getInstance()->replaceScene(prepareScene);
}
