#ifndef PLAYER_H
#define  PLAYER_H

#include "cocos2d.h"
#include "PreparationSeats.h"
#include "GridMap.h"
#include"Store.h"
#include "LittleHero.h"
USING_NS_CC;
class Player : public Ref {
public:
    StoreAttribute* myStore;//���ﾭ�顢��Ǯ���ȼ������̵���
    Chess* mySeats[SEATS_NUM];


    std::map<Vec2, Chess*, Vec2Compare>myChessMap;

    LittleHero* myHero;



private:
    //chess�����������ж����ĸ�����սϯ
    Vector<Chess*> meleeAttacks;
    Vector<Chess*>rangedAttacks;
    int chessNum;
public:
    static Player* create();

    bool init();



    //�ж����´�������,�Ƿ���Ժϳɸ߽�����
    bool canMerge(Chess* c,  bool isToMerge);

    // ��ӻ��ȡ�����Ϣ�ķ��������磺
    void addGold(int amount) { /* ... */ }
    void addExperience(int amount) { /* ... */ }
    // ���෽��...

    void ai();

    //�����̺ͱ�սϯ�ϵ����ӷ�ΪԶ�̺ͽ���
    //ͬʱ�������ȼ��жϺ���������Щ���ӽ�������
    void classify();

    //�����Ӱ�Զ�̺ͽ��̰ڷŵ�����
    void placeChessToBoard();

    //�ж��Ƿ�Ҫ����1������,��Ҫ,��ִ�г���
    void sellOneCost();

    //�ж��Ƿ�Ҫ����
    bool judgeForUpdate();

    //�ж��Ƿ�Ҫˢ��
    bool judgeForRefresh();

    //����һ�ξ���
    void buyExp();

    //�жϵ�ǰ�̵�����Ҫ��������ӣ�������
    void buyChess();

    //����ִ�й������Ӻͷ������ӵĲ���
    void buyAndPlace();


    //Ȼ��������ȼ������������Ӳ��뵽ָ������ĺ���λ��
    void insertWithPriority(Chess* c, Vector<Chess*> &array);

    //�������ȼ��ϸߵ�����
    Chess* judgePriority(Chess* c1, Chess* c2);


};

#endif