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
    // 初始化代码，例如设置金币和经验的初始值
    playerStore = StoreAttribute::create();
    //test
    for(int i=0;i<5;i++)
    playerStore->idInStore[i] = 1;
    //
    for (int i = 0; i < SEATS_NUM; i++) {
        mySeats[i] = nullptr;
    }
    gold = 10;
    experience = 1;
    return true;
}



