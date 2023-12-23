#pragma once

#include "cocos2d.h"
#include "StoreLayer.h"

#define MAX_LEVEL 5                // 最大等级
#define MAX_INTEREST 5              // 回合结算的最大利润
#define MONEY_FOR_REFRESH 2         // 每次刷新所需金币
#define EXP_FOR_UPGRADE 4           // 每次升级的经验
#define INIT_MONEY 100              // 初始钱
#define INIT_LEVEL 1                // 初始等级
#define INIT_EXP 0                  // 初始经验
#define INIT_INTEREST 0             // 初始利息
#define INIT_ADD_FOR_TURN 4          // 每回合自然增长的金币数
#define COST1_AMOUNT 3              // 一到三费卡对应的数量
#define COST2_AMOUNT 5
#define COST3_AMOUNT 3


// 棋子概率
const int cardPercent[MAX_LEVEL][4] = { {50, 100, 0, 0}, {25, 85, 100, 0}, {10, 60, 100, 0}, {0, 40, 80, 100}, {0, 30, 70, 100} };
// 升级所需经验(共四次升级)
const int levelExp[4] = { 4, 8, 14, 20 };

class StoreAttribute : public cocos2d::Node {
public:
    int money;
    int level;
    int exp;
    int interest;
    int idInStore[5];  // 5个卡槽

    static StoreAttribute* create();
    virtual bool init();
};

class Store : public cocos2d::Node {
public:
    int storeAreaHeight = STORE_HEIGHT;

    StoreAttribute* playerStore;

    // 用于显示的标签
    Label* moneyLabel;
    Label* levelAndExpLabel;
    Label* labelRefresh;
    Label* labelUpgrade;
    Label* fadingText;
    float elapsedTime;

    StoreLayer* storeLayers[5];

    int chessIdHaveBought;

    static Store* create(StoreAttribute* st);
    virtual bool init(StoreAttribute* st);
    void updateMoneyLabel();
    void updateLevelLabel();
    void updateForPlayer();
    void refreshStore();
    int whichCost(int pointer);
    void buyExp();
    void refresh();
    void upgrade();
    void renewInterest();
    void buyCard(int choice);
    void sellCard(int sellCardId, int star);
    void createText(const std::string& textContent);
    void updateText(float dt);
    void selectStore(Event* event, Vec2 mousePosition, bool isFull);
};
