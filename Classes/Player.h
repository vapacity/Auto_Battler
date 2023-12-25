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
    StoreAttribute* myStore;//人物经验、金钱、等级都在商店里
    Chess* mySeats[SEATS_NUM];


    std::map<Vec2, Chess*, Vec2Compare>myChessMap;
    std::map<Vec2, Chess*, Vec2Compare> transformedMap;
    std::map<std::pair<int, int>, int>chessCount;//建立从棋子id到棋子个数的映射
    LittleHero* myHero;

    int isAi;

private:
    //chess中有属性来判断在哪个棋格或备战席
    Vector<Chess*> meleeAttacks;
    Vector<Chess*>rangedAttacks;
    int chessNum;
public:
    static Player* create();

    void deletePast();//删除原数据

    bool init();

    // 添加或获取玩家信息的方法，例如：
    void addChess(Chess* chess);
    // Chess* upgradeChess(const int id);//返回升级后的棋子
    void removeChess(Chess* chess);

    //判断买下传入棋子,是否可以合成高阶棋子
    bool canMerge(Chess* c, bool isToMerge);

    // 添加或获取玩家信息的方法，例如：
    void addGold(int amount) { /* ... */ }
    void addExperience(int amount) { /* ... */ }
    // 更多方法...
    //对于敌方player，他的所有棋子的都是与正常情况相对称的,棋子贴图也需要改变
    void convertToEnemy();

    void ai();

    //将棋盘和备战席上的棋子分为远程和近程
    //同时调用优先级判断函数，对这些棋子进行排序
    void classify();

    //将棋子按远程和近程摆放到场上
    void placeChessToBoard();

    //判断是否要出售1费棋子,若要,则执行出售
    void sellOneCost();

    //判断是否要升级
    bool judgeForUpdate();

    //判断是否要刷新
    bool judgeForRefresh();

    //购买一次经验
    void buyExp();

    //判断当前商店中需要购买的棋子，并购买
    void buyChess();

    //反复执行购买棋子和放置棋子的操作
    void buyAndPlace();


    //然后根据优先级，将传入棋子插入到指定数组的合适位置
    void insertWithPriority(Chess* c, Vector<Chess*>& array);

    //返回优先级较高的棋子
    Chess* judgePriority(Chess* c1, Chess* c2);

    void refreshStore();

    int whichCost(int pointer);

};

#endif