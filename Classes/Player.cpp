#include "Player.h"

Player * Player::create()
{
    Player* p = new (std::nothrow) Player();
    if (p && p->init()) {
        /*p->retain();
        p->autorelease();*/
        return p;
    }
    else {
        delete p;
        return nullptr;
    }
}

bool Player::init()
{
    // ��ʼ�����룬�������ý�Һ;���ĳ�ʼֵ
    myStore = StoreAttribute::create();
    //test
    for(int i=0;i<5;i++)
    myStore->idInStore[i] = 1;
    //
    for (int i = 0; i < SEATS_NUM; i++) {
        mySeats[i] = nullptr;
    }

    return true;
}



