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
    int playerNumber;//玩家序号
    StoreAttribute* myStore;//人物经验、金钱、等级都在商店里
    Chess* mySeats[SEATS_NUM];//我方备战席


    std::map<Vec2, Chess*, Vec2Compare>myChessMap;//我方棋盘上的棋子
    std::map<Vec2, Chess*, Vec2Compare> transformedMap;//我方在对方棋盘上的棋子（主要更改了坐标和贴图方向）
    std::map<std::pair<int, int>, int>chessCount;//建立从棋子(id,star)到棋子个数的映射
    LittleHero* myHero;

    int isAi;//


private:
    //chess中有属性来判断在哪个棋格或备战席
    Vector<Chess*> meleeAttacks;
    Vector<Chess*>rangedAttacks;
    int chessNum;
public:
    static Player* create();

    void deletePast();//删除原数据
    void deletePlayer();
    bool init();

    // 玩家执行添加和删除棋子的操作
    void addChess(Chess* chess);
    // Chess* upgradeChess(const int id);//返回升级后的棋子
    void removeChess(Chess* chess);

    //判断买下传入棋子,是否可以合成高阶棋子
    bool canMerge(Chess* c, bool isToMerge);

    //对于敌方player，他的所有棋子的都是与正常情况相对称的,棋子贴图也需要改变
    void convertToEnemy();

    // 添加或获取玩家信息的方法，例如：
    void addGold(int amount) { /* ... */ }
    void addExperience(int amount) { /* ... */ }
    // 更多方法...


    /* AI功能 */
    void ai();//调用逻辑

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

    //Player只有StoreAttribute无法获取刷新后的商店结果,因此在Player里添加了两个Store的工具函数
    void refreshStore();
    int whichCost(int pointer);

};

#endif