#pragma once


#include"cocos2d.h"

using namespace cocos2d;

class Store
{
public:
	int maxInterest = 5;//回合结算的最大利润

	int expPerUpgrade = 4;//每次升级的经验

	int moneyPerRefresh = 2;//每次刷新所需金币

	int cardId[5];

	int level = 1;

	int exp = 0;

	void init();//初始化

	void refreshStore();//刷新商店

	int whichCost(int pointer);

	void getStoreId(int chessId[]);

	void buyExp(int& money);//购买经验值

	void getInterest(int& money);//利润结算

	int getLevel();//返回此时level

	int getExp();//返回此时exp

};