#pragma once
#include"cocos2d.h"
#include"StoreLayer.h"

#define MAX_INTEREST 5//回合结算的最大利润
#define MONEY_FOR_REFRESH 2//每次刷新所需金币
#define EXP_FOR_UPGRADE 4//每次升级的经验
#define INIT_MONEY 100//初始钱
#define INIT_LEVEL 1//初始等级
#define INIT_EXP 0//初始经验
#define INIT_INTEREST 0//初始利息
#define INIT_ADD_FOR_TURN 4 //每回合自然增长的金币数

//包括人物的等级、经验、金钱、回合利润，商店5个卡槽id
class StoreAttribute : public cocos2d::Node{
public:
	int money ;
	int level;
	int exp;
	int interest;
	int idInStore[5];//5个卡槽
public:
	static StoreAttribute* create();
	virtual bool init();
};

class Store:public cocos2d::Node
{
public:
	int storeAreaHeight = STORE_HEIGHT;


	StoreAttribute* playerStore;//存储当前的player数据


	//待挂
	Label* moneyLabel;//显示金钱数
	Label* levelAndExpLabel;//显示经验和等级

	Label* labelRefresh;//显示刷新的标签
	Label* labelUpgrade;//显示更新的标签

	//提示文本
	Label* fadingText;
	float elapsedTime;

	StoreLayer* storeLayers[5];//5个卡槽

	int chessIdHaveBought;//买到的棋子id。放下后要置-1。非-1时不可买

public:
	static Store* create(StoreAttribute* st);

	virtual bool init(StoreAttribute* st);//初始化

	void updateMoneyLabel();//更新金钱标签

	void updateLevelLabel();//更新经验标签


	//根据玩家信息更新商店显示
	void updateForPlayer();

	//要改：一种棋子有5个不同费用
	//刷新商店，更新5个playerStore->storeLayers中的id
	void refreshStore();

	//传入随机出的数据，返回在当前人物等级下，对应的棋子初始费用
	int whichCost(int pointer);


	//购买经验。改钱、经验、等级
    //要改：把金钱作为store的成员
	void buyExp();


	//刷新，修改了金钱和卡槽内的id，但没有动显示
	void refresh();

	//升级，修改了金钱，经验，等级及相关标签
	void upgrade();


	//根据传入金钱，计算利息等当前回合的金钱增长，并直接改动金钱
	//要改：利息的计算方法。
	void renewInterest();


	//购买传入编号卡槽的棋子，更新卡槽信息，更新金钱标签，修改chessIdHaveBought为买到的棋子id
	void buyCard(int choice);


	//根据传入的棋子id和星级，更新出售后的money数值。只动了money
	void sellCard(int sellCardId, int star);


	//输出金钱不足的提示，并在一段时间后自动移除
	void noMoneyText();


	//noMoneyText的调度器用，使提示逐渐淡出
	void updateText(float dt);


	//判断点击事件并执行
	void selectStore(Event* event,Vec2 mousePosition,bool isFull);


	//读到改变后更新显示

};