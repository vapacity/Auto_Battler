#pragma once

#include "cocos2d.h"
#include "StoreLayer.h"

#define MAX_LEVEL 5                // 最大等级
#define MAX_INTEREST 5              // 回合结算的最大利润
#define MONEY_FOR_REFRESH 2         // 每次刷新所需金币
#define EXP_FOR_UPGRADE 4           // 每次升级的经验
#define INIT_MONEY 10              // 初始钱
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

/* 个人玩家商店信息 */
class StoreAttribute : public cocos2d::Node {
public:
    int money;//当前的钱
    int level;//等级
    int exp;//经验
    int interest;//利润
    int idInStore[5];  // 5个卡槽

    static StoreAttribute* create();
    virtual bool init();
};

/* 商店管理 */
class Store : public cocos2d::Node {
public:
    int storeAreaHeight = STORE_HEIGHT;

    StoreAttribute* playerStore;

    // 用于显示的标签
    Label* moneyLabel;
    Label* levelAndExpLabel;
    Label* fadingText;

    Sprite* backGround;
    Sprite* gold;
    Sprite* reFresh;
    Sprite* upGrade;
    Sprite* leVel;
    float elapsedTime;

    StoreLayer* storeLayers[5];//5个卡槽

    int chessIdHaveBought;//买到的棋子id

    static Store* create(StoreAttribute* st);
    virtual bool init(StoreAttribute* st);

    //更新钱的标签显示
    void updateMoneyLabel();

    //更新等级和经验的标签显示
    void updateLevelLabel();

    //更新玩家信息显示（金钱、等级、经验、卡槽）
    void updateForPlayer();

    //刷新商店
    void refreshStore();
    int whichCost(int pointer);

    //刷新金钱、利润和卡槽内的id
    void refresh();

    // 买经验升级，修改了金钱，经验，等级
    void upgrade();

    //更新利润
    void renewInterest();

    //买卡牌
    void buyCard(int choice);

    //卖卡牌
    void sellCard(int sellCardId, int star);

    //打印提示
    void createText(const std::string& textContent);
    void updateText(float dt);

    // 判断点击事件并执行
    void selectStore(Event* event, Vec2 mousePosition, bool isFull);
};
