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
    StoreAttribute* myStore;//人物经验、金钱、等级都在商店里
    Chess* mySeats[SEATS_NUM];
    //包含整个棋盘
    std::map<Vec2, Chess*, Vec2Compare>myChessMap;
    std::map<std::pair<int,int>, int>chessCount;//建立从棋子id和star到棋子个数的映射
    LittleHero* myHero;
public:
    static Player* create();

    bool init();

    // 添加或获取玩家信息的方法，例如：
    void addGold(int amount) { /* ... */ }
    void addExperience(int amount) { /* ... */ }
    void addChess(Chess* chess);

    //返回新增一张该id的卡片后是否能合成
    bool canMerge();
    void removeChess(Chess* chess);

    // 更多方法...


};

#endif