#pragma once


#include"cocos2d.h"

using namespace cocos2d;

class store
{
public:
	int maxInterest = 5;

	int cardId[5];

	int level = 1;

	int exp = 0;

	void init();//初始化

	void refreshStore();//刷新商店

	int whichCost(int pointer);

	void getStoreId(int chessId[]);

	void buyExp(int& money);//购买经验值

	void getInterest(int& money);//利润结算

	int getLevel();

	int getExp();
};