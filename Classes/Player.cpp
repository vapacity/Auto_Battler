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
    for (int i = 0; i < 5; i++) {
        myStore->idInStore[i] = 1;
    }
    //��ʼ����սϯ
    for (int i = 0; i < SEATS_NUM; i++) {
        mySeats[i] = nullptr;
    }
    //��ʼ��ССӢ��
    myHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    return true;
}

void Player::addChess(Chess* chess)
{
    //������ϵ�����
    if (chess->isInGrid())
    {
        chess->retain();
        myChessMap.insert(std::make_pair(chess->atGridPosition, chess));
    }
    //�ڱ�սϯ�ϵ�����
    if (chess->isAtSeat())
    {
        chess->retain();
        mySeats[chess->atSeatPosition] = chess;
    }
    chess->playerNumber = this->playerNumber;//���ӵ�Ӧ�û����ҵı�ʶ
    chessCount[std::make_pair(chess->getId(), chess->star)]++;
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
//        //����������һ�����̵��¼���ģ���Seat���¼���������
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
//    //�˴���һ�����⣡�޷���preSeats�����Seats�������������������Ƿ�Ӱ��
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
        chessCount[std::make_pair(chess->getId(),chess->star)]--;
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
        //�����޸�
        value->setTexture(value->name);
        // ����Գ�λ��
        float x = NUM_COLUMN - pair.first.x;
        float y = NUM_LINE - pair.first.y;

        // ����ӳ���в���任��ļ�ֵ��
        transformedMap[Vec2(x,y)] = value;
    }
}


