#include "WaitingRoomScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
USING_NS_CC;


void WaitingRoomScene::onOpen(cocos2d::network::WebSocket* ws)
{
	CCLOG("WebSocket connection opened");
}
void WaitingRoomScene::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
	CCLOG("Received message: %s", data.bytes);
	std::string message(data.bytes, data.len);
	if (message == "Player1") {
		myPlayer->playerNumber = 0;
		enemyPlayer->playerNumber = 1;
		isPlayer1 = 1;
		initPlayer1();
		return;
	}
	if (message == "Player2") {
		if (isPlayer1 == 1) {
			initPlayer2();
			return;
		}
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
void WaitingRoomScene::onClose(cocos2d::network::WebSocket* ws)
{
	CCLOG("WebSocket connection closed");
}
void WaitingRoomScene::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
	CCLOG("WebSocket error: %d", static_cast<int>(error));
}
bool WaitingRoomScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	initBackground();
	initPlayer();
	initWeb();
	initButton();
	return true;
}

void WaitingRoomScene::initWeb()
{
	webSocket_ = new cocos2d::network::WebSocket();
	webSocket_->init(*this, "ws://100.81.177.2:3000");
}

void WaitingRoomScene::initButton()
{
	auto readyButton = cocos2d::MenuItemLabel::create(
		cocos2d::Label::createWithSystemFont("Ready", "fonts/Marker Felt.ttf", 24),
		CC_CALLBACK_1(WaitingRoomScene::onReadyButtonClick, this));
	auto menu = cocos2d::Menu::create(readyButton, nullptr);
	menu->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
	this->addChild(menu);
}
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
void WaitingRoomScene::initPlayer()
{
	myPlayer = PlayerManager::getInstance()->getPlayer(0);
	enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
}
void WaitingRoomScene::initPlayer1()
{
}
void WaitingRoomScene::initPlayer2()
{
}
void WaitingRoomScene::onReadyButtonClick(cocos2d::Ref* sender)
{
	if (webSocket_)
	{
		webSocket_->send("READY");
	}
}

void WaitingRoomScene::goToPreparScne()
{
	if (webSocket_ && webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
	{
		webSocket_->close();
	}
	auto prepareScene = OnlinePrepareScene::create();
	cocos2d::Director::getInstance()->replaceScene(prepareScene);
}

