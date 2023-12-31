#pragma once

#include "cocos2d.h"
#include "StoreLayer.h"

#define MAX_LEVEL 5                // ���ȼ�
#define MAX_INTEREST 5              // �غϽ�����������
#define MONEY_FOR_REFRESH 2         // ÿ��ˢ��������
#define EXP_FOR_UPGRADE 4           // ÿ�������ľ���
#define INIT_MONEY 10              // ��ʼǮ
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

/* ��������̵���Ϣ */
class StoreAttribute : public cocos2d::Node {
public:
    int money;//��ǰ��Ǯ
    int level;//�ȼ�
    int exp;//����
    int interest;//����
    int idInStore[5];  // 5������

    static StoreAttribute* create();
    virtual bool init();
};

/* �̵���� */
class Store : public cocos2d::Node {
public:
    int storeAreaHeight = STORE_HEIGHT;

    StoreAttribute* playerStore;

    // ������ʾ�ı�ǩ
    Label* moneyLabel;
    Label* levelAndExpLabel;
    Label* fadingText;

    Sprite* backGround;
    Sprite* gold;
    Sprite* reFresh;
    Sprite* upGrade;
    Sprite* leVel;
    float elapsedTime;

    StoreLayer* storeLayers[5];//5������

    int chessIdHaveBought;//�򵽵�����id

    static Store* create(StoreAttribute* st);
    virtual bool init(StoreAttribute* st);

    //����Ǯ�ı�ǩ��ʾ
    void updateMoneyLabel();

    //���µȼ��;���ı�ǩ��ʾ
    void updateLevelLabel();

    //���������Ϣ��ʾ����Ǯ���ȼ������顢���ۣ�
    void updateForPlayer();

    //ˢ���̵�
    void refreshStore();
    int whichCost(int pointer);

    //ˢ�½�Ǯ������Ϳ����ڵ�id
    void refresh();

    // �����������޸��˽�Ǯ�����飬�ȼ�
    void upgrade();

    //��������
    void renewInterest();

    //����
    void buyCard(int choice);

    //������
    void sellCard(int sellCardId, int star);

    //��ӡ��ʾ
    void createText(const std::string& textContent);
    void updateText(float dt);

    // �жϵ���¼���ִ��
    void selectStore(Event* event, Vec2 mousePosition, bool isFull);
};
