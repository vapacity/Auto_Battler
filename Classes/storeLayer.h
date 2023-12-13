#pragma once
#include"cocos2d.h"
#include"store.h"
using namespace cocos2d;


class storeLayer :public store,public cocos2d::Sprite{
public:
	int money = 0;
	int level = 1;
	int exp = 0;
	Label* moneyLabel;
	Label* levelAndExpLabel;
	Label* label1;
	Label* label2;
	std::vector<Sprite*> spriteArray;
	EventListenerMouse* storeLayerMouseListener;//鼠标监听器
	// 禁用和启用鼠标监听器的方法
	void disableMouseListener();
	void enableMouseListener();

	static storeLayer* create();

	void refresh();//刷新

	void updateMoneyLabel();

	void updateLevelLabel();

	virtual bool init();//初始化

	void showStore();

	void buyCard(int choice);//购买卡牌

	int layerId[5];//储存卡牌id

	void selectStore(Event* event);

	void upgrade();
};