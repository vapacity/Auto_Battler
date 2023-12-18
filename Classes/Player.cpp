#include "Player.h"

Player * Player::create()
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

bool Player::init()
{
    // 初始化代码，例如设置金币和经验的初始值
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

void Player::addChess(Chess* chess)
{
    //在棋格上的棋子
    if (chess->isInGrid())
    {
        myChessMap.insert(std::make_pair(chess->atGridPosition, chess));
    }
    //在备战席上的棋子
    if (chess->isAtSeat())
    {
        mySeats[chess->atSeatPosition] = chess;
    }
    int chessType = chess->getId();
    chessCount[chessType]++;
    /*if (chessCount[chessType] == 3) {
        addChess(upgradeChess(chessType));
    }*/
}

//Chess* Player::upgradeChess(const int id)
//{
//    Chess* chess1=nullptr;
//    Chess* chess2 = nullptr;
//    Chess* chess3 = nullptr;
//    for (auto pair : myChessMap)
//    {
//        if (pair.second->getId() == id && !chess1)
//        {
//            chess1 = pair.second;
//        }
//        else if (pair.second->getId() == id && !chess2)
//        {
//            chess2 = pair.second;
//        }
//        //第三个棋子一定是商店新加入的，在Seat上新加入了棋子
//    }
//    for (int i = 0; i < SEATS_NUM; i++)
//    {
//        if (mySeats[i]->getId() == id&&!chess1)
//        {
//            chess1 = mySeats[i];
//        }
//        else if (mySeats[i]->getId() == id && !chess2)
//        {
//            chess2 = mySeats[i];
//        }
//        else if (mySeats[i]->getId() == id && !chess3)
//        {
//            chess3=mySeats[i];
//        }
//
//    }
//    auto upGrade = chess1->upgrade();
//    removeChess(chess1);
//    removeChess(chess2);
//    removeChess(chess3);
//    //此处有一个问题！无法对preSeats里面的Seats作增减操作，后续看是否影响
//    chess1->deleteChess();
//    chess2->deleteChess();
//    chess3->deleteChess();
//    return upGrade;
//
//}

void Player::removeChess(Chess* chess)
{
    if (!chess)
        return;
    if (chess->isInGrid())
    {
        myChessMap.erase(chess->atGridPosition);
        chessCount[chess->getId()]--;
    }
    else if (chess->isAtSeat())
    {
        mySeats[chess->atSeatPosition] = nullptr;
        chessCount[chess->getId()]--;
    }

}


