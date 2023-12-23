#pragma once

#include "cocos2d.h"
#include "StoreLayer.h"

#define MAX_LEVEL 5                // ���ȼ�
#define MAX_INTEREST 5              // �غϽ�����������
#define MONEY_FOR_REFRESH 2         // ÿ��ˢ��������
#define EXP_FOR_UPGRADE 4           // ÿ�������ľ���
#define INIT_MONEY 100              // ��ʼǮ
#define INIT_LEVEL 1                // ��ʼ�ȼ�
#define INIT_EXP 0                  // ��ʼ����
#define INIT_INTEREST 0             // ��ʼ��Ϣ
#define INIT_ADD_FOR_TURN 4          // ÿ�غ���Ȼ�����Ľ����
#define COST1_AMOUNT 3              // һ�����ѿ���Ӧ������
#define COST2_AMOUNT 5
#define COST3_AMOUNT 3


// ���Ӹ���
const int cardPercent[MAX_LEVEL][4] = { {50, 100, 0, 0}, {25, 85, 100, 0}, {10, 60, 100, 0}, {0, 40, 80, 100}, {0, 30, 70, 100} };
// �������辭��(���Ĵ�����)
const int levelExp[4] = { 4, 8, 14, 20 };

class StoreAttribute : public cocos2d::Node {
public:
    int money;
    int level;
    int exp;
    int interest;
    int idInStore[5];  // 5������

    static StoreAttribute* create();
    virtual bool init();
};

class Store : public cocos2d::Node {
public:
    int storeAreaHeight = STORE_HEIGHT;

    StoreAttribute* playerStore;

    // ������ʾ�ı�ǩ
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
