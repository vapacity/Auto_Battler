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
		Player* player0 = Player::create();
		PlayerManager::getInstance()->addPlayer(player0);
		player0->playerNumber = 0;
		Player* player1 = Player::create();
		PlayerManager::getInstance()->addPlayer(player0);
		player1->playerNumber = 1;
		return;
	}
	if (message == "Player2") {
		Player* player0 = Player::create();
		PlayerManager::getInstance()->addPlayer(player0);
		player0->playerNumber = 1;
		Player* player1 = Player::create();
		PlayerManager::getInstance()->addPlayer(player0);
		player1->playerNumber = 0;
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
	initWeb();
	initButton();
	return true;
}

void WaitingRoomScene::initWeb()
{
	webSocket_ = new cocos2d::network::WebSocket();
	webSocket_->init(*this, "ws://192.168.43.182:3000");
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
void WaitingRoomScene::onReadyButtonClick(cocos2d::Ref* sender)
{
	if (webSocket_)
	{
		webSocket_->send("READY");
	}
}

void WaitingRoomScene::goToPreparScne()
{
	webSocket_->close();

}

