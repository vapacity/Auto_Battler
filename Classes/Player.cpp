#include "Player.h"

Player * Player::create()
{
    Player* p = new (std::nothrow) Player();
    if (p && p->init()) {
        p->retain();//player�಻�ܱ������ͷ�
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

void Player::addChess(Chess* chess)
{
    //������ϵ�����
    if (chess->atCell)
    {
        myChessMap.insert(std::make_pair(chess->atGridPosition, chess));
    }
    //�ڱ�սϯ�ϵ�����
    if (chess->atSeat)
    {
        mySeats[chess->atSeat->number] = chess;
    }
    int chessType = chess->getId();
    chessCount[chessType]++;
    if (chessCount[chessType] == 3) {
        upgradeChess(chessType);
        chessCount[chessType] -= 3;
    }
}

void Player::upgradeChess(const int id)
{
    Chess* chess1=nullptr;
    Chess* chess2 = nullptr;
    Chess* chess3 = nullptr;
    for (auto pair : myChessMap)
    {
        if (pair.second->getId() == id && !chess1)
        {
            chess1 = pair.second;
        }
        else if (pair.second->getId() == id && !chess2)
        {
            chess2 = pair.second;
        }
        //����������һ�����̵��¼���ģ���Seat���¼���������
    }
    for (int i = 0; i < SEATS_NUM; i++)
    {
        if (mySeats[i]->getId() == id&&!chess1)
        {
            chess1 = mySeats[i];
        }
        else if (mySeats[i]->getId() == id && !chess2)
        {
            chess2 = mySeats[i];
        }
        else if (mySeats[i]->getId() == id && !chess3)
        {
            chess3=mySeats[i];
        }

    }
    
    removeChess(chess2);
    removeChess(chess3);
           ////�˴���һ�����⣡�޷���preSeats�����Seats�������������������Ƿ�Ӱ��
    chess2->deleteChess();
    chess3->deleteChess();
    chess1->upgrade();
    chess1->deleteChess();

}

void Player::removeChess(Chess* chess)
{
    if (!chess)
        return;
    if (chess->atCell)
    {
        myChessMap.erase(chess->atGridPosition);
        chessCount[chess->getId()]--;
    }
    else if (chess->atSeat)
    {
        mySeats[chess->atSeat->number] = nullptr;
        chessCount[chess->getId()]--;
    }

}


