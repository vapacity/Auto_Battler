#ifndef PLAYER_H
#define  PLAYER_H

#include "cocos2d.h"
#include "PreparationSeats.h"
#include "GridMap.h"
#include"Store.h"
#include "LittleHero.h"
#include"ChessFactory.h"
USING_NS_CC;
class Player : public Ref {
public:
    int playerNumber;
    StoreAttribute* myStore;//���ﾭ�顢��Ǯ���ȼ������̵���
    Chess* mySeats[SEATS_NUM];


    std::map<Vec2, Chess*, Vec2Compare>myChessMap;
    std::map<Vec2, Chess*, Vec2Compare> transformedMap;
    std::map<std::pair<int, int>, int>chessCount;//����������id�����Ӹ�����ӳ��
    LittleHero* myHero;

    int isAi;

private:
    //chess�����������ж����ĸ�����սϯ
    Vector<Chess*> meleeAttacks;
    Vector<Chess*>rangedAttacks;
    int chessNum;
public:
    static Player* create();

    void deletePast();//ɾ��ԭ����

    bool init();

    // ��ӻ��ȡ�����Ϣ�ķ��������磺
    void addChess(Chess* chess);
    // Chess* upgradeChess(const int id);//���������������
    void removeChess(Chess* chess);

    //�ж����´�������,�Ƿ���Ժϳɸ߽�����
    bool canMerge(Chess* c, bool isToMerge);

    // ��ӻ��ȡ�����Ϣ�ķ��������磺
    void addGold(int amount) { /* ... */ }
    void addExperience(int amount) { /* ... */ }
    // ���෽��...
    //���ڵз�player�������������ӵĶ��������������ԳƵ�,������ͼҲ��Ҫ�ı�
    void convertToEnemy();

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
    void insertWithPriority(Chess* c, Vector<Chess*>& array);

    //�������ȼ��ϸߵ�����
    Chess* judgePriority(Chess* c1, Chess* c2);

    void refreshStore();

    int whichCost(int pointer);

};

#endif