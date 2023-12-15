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

    // 添加或获取玩家信息的方法，例如：
    void addGold(int amount) { /* ... */ }
    void addExperience(int amount) { /* ... */ }
    // 更多方法...

//private:
    StoreAttribute* playerStore;//人物经验、金钱、等级都在商店里
    Chess* mySeats[SEATS_NUM];
    //包含整个棋盘
    std::map<Vec2, Chess*, Vec2Compare>myChessMap;

    int gold;
    int experience;
    // 棋子的集合等
};

#endif