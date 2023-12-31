#include "Player.h"

Player* Player::create()
{
    Player* p = new (std::nothrow) Player();
    if (p && p->init()) {
        p->retain();//player类不能被随意释放
        p->autorelease();
        return p;
    }
    else {
        delete p;
        return nullptr;
    }
}

void Player::deletePlayer()
{
    if (myStore)
        myStore->release();
    if (myHero)
        myStore->release();
    for (int i = 0; i < SEATS_NUM; i++)
    {
        if (mySeats[i])
            mySeats[i]->release();
    }
    for (auto iter : myChessMap)
    {
        if (iter.second)
            iter.second->release();
    }
    for (auto iter : transformedMap)
    {
        if (iter.second)
            iter.second->release();
    }
    for (auto iter : meleeAttacks)
    {
        if (iter)
            iter->release();
    }
    for (auto iter : rangedAttacks)
    {
        if (iter)
            iter->release();
    }
    init();
}
 void Player::deletePast()
{
    myChessMap.clear();
    transformedMap.clear();
    chessCount.clear();
    meleeAttacks.clear();
    rangedAttacks.clear();
    init();
}

bool Player::init()
{
    // 初始化代码，例如设置金币和经验的初始值
    myStore = StoreAttribute::create();
    myStore->retain();
    //test
    for (int i = 0; i < 5; i++) {
        myStore->idInStore[i] = -1;
    }
    //初始化备战席
    for (int i = 0; i < SEATS_NUM; i++) {
        mySeats[i] = nullptr;
    }
    //初始化小小英雄
    myHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    myHero->retain();
    return true;
}

void Player::addChess(Chess* chess)
{
    //在棋格上的棋子
    if (chess->isInGrid())
    {
        chess->retain();
        myChessMap.insert(std::make_pair(chess->atGridPosition, chess));
    }
    //在备战席上的棋子
    if (chess->isAtSeat())
    {
        chess->retain();
        mySeats[chess->atSeatPosition] = chess;
    }
    chess->playerNumber = this->playerNumber;//棋子的应该获得玩家的标识
    chessCount[std::make_pair(chess->getId(), chess->star)]++;
    /*if (chessCount[chessType] == 3) {
        addChess(upgradeChess(chessType));
    }*/
}


void Player::removeChess(Chess* chess)
{
    if (!chess)
        return;
    if (chess->isInGrid())
    {
        myChessMap.erase(chess->atGridPosition);
        chessCount[std::make_pair(chess->getId(), chess->star)]--;
    }
    else if (chess->isAtSeat())
    {
        mySeats[chess->atSeatPosition] = nullptr;
        chessCount[std::make_pair(chess->getId(), chess->star)]--;
    }

}

void Player::convertToEnemy()
{
    for (const auto& pair : myChessMap) {
        Vec2 key = pair.first;
        Chess* value = pair.second;
        //这里修改
        value->setTexture(value->name);
        // 计算对称位置
        float x = NUM_COLUMN - pair.first.x - 1;
        float y = NUM_LINE - pair.first.y - 1;

        // 在新映射中插入变换后的键值对
        transformedMap[Vec2(x, y)] = value;
    }
}


// 传入随机出的数据，返回在当前人物等级下，对应的棋子初始费用
int Player::whichCost(int pointer)
{
    if (pointer <= cardPercent[myStore->level - 1][0])
        return -2;
    else if (pointer <= cardPercent[myStore->level - 1][1])
        return 1;
    else if (pointer <= cardPercent[myStore->level - 1][2])
        return 2;
    else if (pointer <= cardPercent[myStore->level - 1][3])
        return 3;
    return -1;
}

void Player::refreshStore()
{
    srand((unsigned)time(NULL));

    for (int i = 0; i < 5; i++) {
        int costPointer = rand() % 100;
        switch (whichCost(costPointer)) {
        case -2:
            myStore->idInStore[i] = -2;
            break;
        case 1:
            myStore->idInStore[i] = 11 + rand() % COST1_AMOUNT;
            break;
        case 2:
            myStore->idInStore[i] = 21 + rand() % COST2_AMOUNT;
            break;
        case 3:
            myStore->idInStore[i] = 31 + rand() % COST3_AMOUNT;
            break;
        default:
            myStore->idInStore[i] = -2;
            break;
        }
    }
    return;
}

void Player::ai()
{

    this->myStore->money += 10;
    this->myStore->exp += 2;



    //先进行升级的判断,每个阶段只需要进行一次
    //暂时不考虑梭哈状态，在当前回合d到三星后马上升级的情况
    while (judgeForUpdate()) {
        buyExp();
    }

    //分类也只有一次，把棋盘和备战席数据复制进近战远程容器即可，之后的优先级排序另外调用函数
    //棋盘和备战席只有在开始,判断出售1费,摆放棋子的时候有用
    //classify();


    //购买,合成,并摆放
    buyAndPlace();


    //出售不需要的1费棋子
    //不会出售场上的棋子
    sellOneCost();



    //出售后,数组有变化,重新分析
    //classify();//可优化掉,大概

}

//返回优先级较高的棋子
Chess* Player::judgePriority(Chess* c1, Chess* c2) {
    if (c1->originalCost > c2->originalCost)
        return c1;
    if (c1->originalCost == c2->originalCost && c1->star > c2->star)
        return c1;

    return c2;
}


//然后根据优先级，将传入棋子插入到指定数组的合适位置
void Player::insertWithPriority(Chess* c, Vector<Chess*>& array) {
    int i = 0;
    //插入排序
    while (i < array.size() && array.at(i)) {
        if (judgePriority(c, array.at(i)) == c)
            break;
        i++;
    }


    array.insert(i, c);
}



//将棋盘和备战席上的棋子分为远程和近程
//同时调用优先级判断函数，对这些棋子进行排序
void Player::classify()
{

    for (auto a : myChessMap) {
        Chess* c = a.second;
        if (c) {
            if (c->isMelee) {
                insertWithPriority(c, meleeAttacks);
            }
            else {
                insertWithPriority(c, rangedAttacks);
            }
        }

    }
    for (Chess* c : mySeats) {
        if (c) {
            if (c->isMelee) {
                insertWithPriority(c, meleeAttacks);
            }
            else {
                insertWithPriority(c, rangedAttacks);
            }
        }

    }
}



//从已排序好的近战和远程棋子容器中，选择棋子放在棋盘和备战席上
void Player::placeChessToBoard()
{
    //-1才是索引
    int meleeIndex = myStore->level / 2;
    int rangedIndex = myStore->level / 2;
    if (meleeAttacks.size() < meleeIndex)
        meleeIndex = meleeAttacks.size();
    if (rangedAttacks.size() < rangedIndex)
        rangedIndex = rangedAttacks.size();



    //判断哪些棋子要上场

    //两个容器都不足一半，直接结束
    if (meleeIndex == meleeAttacks.size() && rangedIndex == rangedAttacks.size()) {
    }
    //各取一半，达到人口上限，结束
    else if (meleeIndex + rangedIndex == myStore->level) {
    }
    //某个容器中不足一半，在另一个容器中取，直至满人口或者满容器
    else if (meleeIndex == meleeAttacks.size()) {
        if (meleeIndex + rangedAttacks.size() > myStore->level) {
            rangedIndex = myStore->level - meleeIndex;
        }
        else {
            rangedIndex = rangedAttacks.size();
        }
    }
    else if (rangedIndex == rangedAttacks.size()) {
        if (rangedIndex + meleeAttacks.size() > myStore->level) {
            meleeIndex = myStore->level - rangedIndex;
        }
        else {
            meleeIndex = meleeAttacks.size();
        }
    }
    //各取一半，不到人口上限：取近战和远程中最优先的一个棋子
    else {
        meleeAttacks.at(meleeIndex) == judgePriority(meleeAttacks.at(meleeIndex), rangedAttacks.at(rangedIndex)) ? meleeIndex++ : rangedIndex++;
    }



    //摆棋子，从左到右，从高优先到低优先

    //ai中的棋子不会用到atCell等属性，所有没有更新
    //在传输进场景时，可能需要赋值
    //无需考虑怎么摆放的，只要知道放在哪里

    //把场上和备战席全部清空(视情况，棋盘那些的调度器可能会报错。破案了，调用调度器的场景中不会传入正在运行的ai)
    for (int i = 0; i < SEATS_NUM; i++) {
        mySeats[i] = nullptr;
    }
    myChessMap.clear();

    //将该放在棋盘上的棋子，放在棋盘的远程和近程区
    for (int i = 0; i < meleeIndex; i++) {
        myChessMap.insert(std::make_pair(Vec2(i, NUM_LINE / 2 - 1), meleeAttacks.at(i)));
    }
    for (int i = 0; i < rangedIndex; i++) {
        myChessMap.insert(std::make_pair(Vec2(i, 0), rangedAttacks.at(i)));
    }


    //将剩余的棋子放在备战席上
    //在执行这个函数时，备战席不可能会满。
    int seatsIndex = 0;
    for (int i = meleeIndex; i < meleeAttacks.size(); i++) {
        mySeats[seatsIndex++] = meleeAttacks.at(i);
    }
    for (int i = rangedIndex; i < rangedAttacks.size(); i++) {
        mySeats[seatsIndex++] = rangedAttacks.at(i);
    }

}



//判断是否要出售1费棋子,若要,则执行出售
void Player::sellOneCost()
{
    if (myStore->level < 4)
        return;

    Vector<Chess*> chessInBoard;
    for (auto a : myChessMap) {
        if (a.second->originalCost == 1) {
            chessInBoard.pushBack(a.second);
        }
    }

    for (auto a : mySeats) {
        if (a) {
            if (a->originalCost == 1) {
                if (chessInBoard.find(a) == chessInBoard.end()) {
                    myStore->money += a->price;
                    a = nullptr;
                }
            }
        }

    }



}





//判断是否要升级
bool Player::judgeForUpdate()
{
    if (myStore->money < 50 + EXP_FOR_UPGRADE)
        return false;
    else if (myStore->level < 5)
        return true;
    else
        return false;
}



//有隐患:不能升星的牌可能会把备战席卡满.暂不处理
//判断当前状态是否要刷新商店
//当前处理是:当备战席和棋盘都满了.仍继续d
bool Player::judgeForRefresh()
{

    bool isThreeStar = 1;
    if (!myChessMap.size())
        isThreeStar = 0;
    for (auto a : myChessMap) {
        if (a.second->star != 3)
            isThreeStar = 0;
    }

    //若棋盘上全是三星,则无需再d,退出
    if (isThreeStar)
        return false;

    //若剩余钱不够三次刷新，则无需再d,退出
    if (myStore->money < MONEY_FOR_REFRESH * 3)
        return false;

    //在全三星判断之后
    //若血量不足，进入梭哈状态，则每回合都d空
    if (myHero->percentage <= 30)
        return true;

    //若人数已满则不买，留一个格子用于三合一
  /*  if (myStore->level + SEATS_NUM - 1 <= meleeAttacks.size() + rangedAttacks.size())
        return false;*/

    //当前策略不是优先升级,则卡利息d牌
    if (!judgeForUpdate() && myStore->money > 50 + MONEY_FOR_REFRESH) {
        return true;
    }

    return false;



}


//只有StoreAttribute无法获取刷新后的商店结果,须改
//尚未执行刷新操作
void Player::buyAndPlace()
{
    //已将棋子尽可能摆上棋盘,备战席满则总人数满
    placeChessToBoard();

    refreshStore();
    buyChess();
    //进行刷新和购买的判断
    while (judgeForRefresh())
    {
        myStore->money -= 2;

        refreshStore();
        //买了的棋子按优先级塞进近战远程容器，不进入棋盘和备战席成员
        buyChess();

    }


    placeChessToBoard();


}



//判断当前商店,并购买所需
void Player::buyChess()
{
    //遍历商店的5个卡槽
    for (int i = 0; i < 5; i++) {

        if(myStore->idInStore[i]!=-1&& myStore->idInStore[i]!=-2)
        {
            //会被释放吗
            Chess* storeChess = ChessFactory::createChessById(myStore->idInStore[i]);


            //若已达人口上限
            //若当前卡槽的棋子买了后,不能合成,则不买
            if (meleeAttacks.size() + rangedAttacks.size() >= myStore->level + SEATS_NUM - 1) {
                if (!canMerge(storeChess, false))
                    continue;
            }


            //过渡阶段:等级小于3
            //一费棋子只用来过渡,有二星就不用再买
            if (storeChess->originalCost == 1 && myStore->level <= 3) {
                bool isExist = 0;

                for (Chess* c : meleeAttacks) {
                    if (c->id == storeChess->id && c->star >= storeChess->star) {
                        isExist = 1;
                        break;
                    }
                }
                for (Chess* c : rangedAttacks) {
                    if (c->id == storeChess->id && c->star >= storeChess->star) {
                        isExist = 1;
                        break;
                    }
                }
                if (isExist)
                    continue;

            }
            //非过渡阶段,不买1费牌
            else if (storeChess->originalCost == 1)
                continue;
            //ai不买3费高级棋子
            else if (storeChess->originalCost == 3) {
                continue;
            }
            //判断二费棋子
            else if (storeChess->originalCost == 2) {
                //如果已有当前卡槽中棋子的三星,则不买
                bool isExist = 0;
                for (Chess* c : meleeAttacks) {
                    if (c->id == storeChess->id && c->star == 3) {
                        isExist = 1;
                        break;
                    }
                }
                for (Chess* c : rangedAttacks) {
                    //如果已有当前卡槽中棋子的三星
                    if (c->id == storeChess->id && c->star == 3) {
                        isExist = 1;
                        break;
                    }
                }
                if (isExist)
                    continue;

            }

            //买下当前卡槽的棋子
            myStore->money -= storeChess->price;

            //执行合成操作
            canMerge(storeChess, true);

            if (storeChess->isMelee)
                insertWithPriority(storeChess, meleeAttacks);
            else
                insertWithPriority(storeChess, rangedAttacks);


            //不影响存在数组里的数据,只影响数组,大概
            myStore->idInStore[i] = -1;
            //有隐患,若第一次判断的时候, placeChessToBoard未将棋盘放满,之后也不会把棋子放在棋盘上.暂时忽略
        }
    }
}




//判断传入的棋子是否能和已有的棋子合成,若能,根据isToMerge执行合成
bool Player::canMerge(Chess* c, bool isToMerge)
{
    if (!c)
        return false;

    int count = 0;
    int index[2];
    //判断是否已有同星级同种类的两张棋子,并把索引存入index
    if (c->isMelee) {
        for (int i = 0; i < meleeAttacks.size(); i++) {
            Chess* a = meleeAttacks.at(i);
            if (a->id == c->id && a->star == c->star) {
                index[count] = i;
                count++;
            }
            if (count == 2)
                break;
        }
    }
    else {
        for (int i = 0; i < rangedAttacks.size(); i++) {
            Chess* a = rangedAttacks.at(i);
            if (a->id == c->id && a->star == c->star) {
                index[count] = i;
                count++;
            }
            if (count == 2)
                break;
        }
    }


    //若能合成
    if (count == 2) {
        //若要执行合成操作
        if (isToMerge) {
            if (c->isMelee) {

                meleeAttacks.erase(index[0]);

                meleeAttacks.erase(index[1] - 1);
                c->upgrade();
            }
            else {
                rangedAttacks.erase(index[0]);
                rangedAttacks.erase(index[1] - 1);
                c->upgrade();
            }
            count = 0;
            if (c->isMelee) {
                for (int i = 0; i < meleeAttacks.size(); i++) {
                    Chess* a = meleeAttacks.at(i);
                    if (a->id == c->id && a->star == c->star) {
                        index[count] = i;
                        count++;
                    }
                    if (count == 2)
                        break;
                }
            }
            else {
                for (int i = 0; i < rangedAttacks.size(); i++) {
                    Chess* a = rangedAttacks.at(i);
                    if (a->id == c->id && a->star == c->star) {
                        index[count] = i;
                        count++;
                    }
                    if (count == 2)
                        break;
                }
            }

            if (count == 2) {
                if (isToMerge) {
                    if (c->isMelee) {

                        meleeAttacks.erase(index[0]);

                        meleeAttacks.erase(index[1] - 1);
                        c->upgrade();
                    }
                    else {
                        rangedAttacks.erase(index[0]);
                        rangedAttacks.erase(index[1] - 1);
                        c->upgrade();
                    }


                }
            }

        }
        return true;
    }
    else {
        return false;
    }


}

//购买一次经验
void Player::buyExp()
{
    myStore->money -= EXP_FOR_UPGRADE;
    myStore->exp += EXP_FOR_UPGRADE;
    if (myStore->exp >= levelExp[myStore->level - 1]) {
        myStore->exp -= levelExp[myStore->level - 1];
        myStore->level++;
    }
}