#pragma once
#include"cocos2d.h"
#include"Store.h"
using namespace cocos2d;
const int pictureSize = 150;
#define storeHeight 200;

class StoreLayer :public Store,public cocos2d::Sprite{
public:
	int storeAreaHeight = storeHeight;
	int buyCardId = -1;
	int money = 10;
	int level = 1;
	int exp = 0;
	Label* moneyLabel;
	Label* levelAndExpLabel;
	Label* label1;
	Label* label2;
	Label* fadingText;
	std::vector<Sprite*> spriteArray;
	std::vector<Label*>labelArray;
	EventListenerMouse* StoreLayerMouseListener;//鼠标监听器
	// 禁用和启用鼠标监听器的方法
	void disableMouseListener();
	void enableMouseListener();

	static StoreLayer* create();

	void refresh();//刷新

	void updateMoneyLabel();

	void updateLevelLabel();

	virtual bool init();//初始化

	void showStore();

	void buyCard(int choice);//购买卡牌

	void sellCard(int sellCardId, int star);//售卖卡牌

	int layerId[5];//储存卡牌id

	void selectStore(Event* event);

	void upgrade();

	void alterMaxInteresr(int newInterest);//改变最大利润

	void alterExpPerUpgrade(int newExpPerUpgrade);//改变最大利润

	void alterMoneyPerRefresh(int newMoneyPerRefresh);//改变刷新商店花费

	void noMoneyText();

	float elapsedTime;

	void updateText(float dt);
};