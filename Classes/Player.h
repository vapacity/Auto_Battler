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
    static Player* create();

    bool init();

    // ��ӻ��ȡ�����Ϣ�ķ��������磺
    void addGold(int amount) { /* ... */ }
    void addExperience(int amount) { /* ... */ }
    // ���෽��...

//private:
    StoreAttribute* playerStore;//���ﾭ�顢��Ǯ���ȼ������̵���
    Chess* mySeats[SEATS_NUM];
    //������������
    std::map<Vec2, Chess*, Vec2Compare>myChessMap;

    int gold;
    int experience;
    // ���ӵļ��ϵ�
};

#endif