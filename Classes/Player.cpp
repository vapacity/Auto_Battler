#include "Player.h"



Player* Player::create()
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
    myHero->retain();
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
        //�����޸�
        value->setTexture(value->name);
        // ����Գ�λ��
        float x = NUM_COLUMN - pair.first.x - 1;
        float y = NUM_LINE - pair.first.y - 1;

        // ����ӳ���в���任��ļ�ֵ��
        transformedMap[Vec2(x, y)] = value;
    }
}


// ��������������ݣ������ڵ�ǰ����ȼ��£���Ӧ�����ӳ�ʼ����
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



    //�Ƚ����������ж�,ÿ���׶�ֻ��Ҫ����һ��
    //��ʱ���������״̬���ڵ�ǰ�غ�d�����Ǻ��������������
    while (judgeForUpdate()) {
        buyExp();
    }

    //����Ҳֻ��һ�Σ������̺ͱ�սϯ���ݸ��ƽ���սԶ���������ɣ�֮������ȼ�����������ú���
    //���̺ͱ�սϯֻ���ڿ�ʼ,�жϳ���1��,�ڷ����ӵ�ʱ������
    //classify();


    //����,�ϳ�,���ڷ�
    buyAndPlace();


    //���۲���Ҫ��1������
    //������۳��ϵ�����
    sellOneCost();



    //���ۺ�,�����б仯,���·���
    //classify();//���Ż���,���

}

//�������ȼ��ϸߵ�����
Chess* Player::judgePriority(Chess* c1, Chess* c2) {
    if (c1->originalCost > c2->originalCost)
        return c1;
    if (c1->originalCost == c2->originalCost && c1->star > c2->star)
        return c1;

    return c2;
}


//Ȼ��������ȼ������������Ӳ��뵽ָ������ĺ���λ��
void Player::insertWithPriority(Chess* c, Vector<Chess*>& array) {
    int i = 0;
    //��������
    while (i < array.size() && array.at(i)) {
        if (judgePriority(c, array.at(i)) == c)
            break;
        i++;
    }


    array.insert(i, c);
}



//�����̺ͱ�սϯ�ϵ����ӷ�ΪԶ�̺ͽ���
//ͬʱ�������ȼ��жϺ���������Щ���ӽ�������
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



//��������õĽ�ս��Զ�����������У�ѡ�����ӷ������̺ͱ�սϯ��
void Player::placeChessToBoard()
{
    //-1��������
    int meleeIndex = myStore->level / 2;
    int rangedIndex = myStore->level / 2;
    if (meleeAttacks.size() < meleeIndex)
        meleeIndex = meleeAttacks.size();
    if (rangedAttacks.size() < rangedIndex)
        rangedIndex = rangedAttacks.size();



    //�ж���Щ����Ҫ�ϳ�

    //��������������һ�룬ֱ�ӽ���
    if (meleeIndex == meleeAttacks.size() && rangedIndex == rangedAttacks.size()) {
    }
    //��ȡһ�룬�ﵽ�˿����ޣ�����
    else if (meleeIndex + rangedIndex == myStore->level) {
    }
    //ĳ�������в���һ�룬����һ��������ȡ��ֱ�����˿ڻ���������
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
    //��ȡһ�룬�����˿����ޣ�ȡ��ս��Զ���������ȵ�һ������
    else {
        meleeAttacks.at(meleeIndex) == judgePriority(meleeAttacks.at(meleeIndex), rangedAttacks.at(rangedIndex)) ? meleeIndex++ : rangedIndex++;
    }



    //�����ӣ������ң��Ӹ����ȵ�������

    //ai�е����Ӳ����õ�atCell�����ԣ�����û�и���
    //�ڴ��������ʱ��������Ҫ��ֵ
    //���迼����ô�ڷŵģ�ֻҪ֪����������

    //�ѳ��Ϻͱ�սϯȫ�����(�������������Щ�ĵ��������ܻᱨ���ư��ˣ����õ������ĳ����в��ᴫ���������е�ai)
    for (int i = 0; i < SEATS_NUM; i++) {
        mySeats[i] = nullptr;
    }
    myChessMap.clear();


    //���÷��������ϵ����ӣ��������̵�Զ�̺ͽ�����
    for (int i = 0; i < meleeIndex; i++) {
        myChessMap.insert(std::make_pair(Vec2(i, 0), meleeAttacks.at(i)));
    }
    for (int i = 0; i < rangedIndex; i++) {
        myChessMap.insert(std::make_pair(Vec2(i, NUM_LINE / 2 - 1), rangedAttacks.at(i)));
    }

    //��ʣ������ӷ��ڱ�սϯ��
    //��ִ���������ʱ����սϯ�����ܻ�����
    int seatsIndex = 0;
    for (int i = meleeIndex; i < meleeAttacks.size(); i++) {
        mySeats[seatsIndex++] = meleeAttacks.at(i);
    }
    for (int i = rangedIndex; i < rangedAttacks.size(); i++) {
        mySeats[seatsIndex++] = rangedAttacks.at(i);
    }

}



//�ж��Ƿ�Ҫ����1������,��Ҫ,��ִ�г���
void Player::sellOneCost()
{
    //4��ǰ����1����
    if (myStore->level < 4)
        return;

    //��¼�ϳ���1������
    Vector<Chess*> chessInBoard;
    for (auto a : myChessMap) {
        if (a.second->originalCost == 1) {
            chessInBoard.pushBack(a.second);
        }
    }

    for (auto a : mySeats) {
        if (a) {
            //�����1��,��δ�ϳ�,�����
            if (a->originalCost == 1) {
                if (chessInBoard.find(a) == chessInBoard.end()) {
                    myStore->money += a->price;
                    a = nullptr;
                }
            }
        }

    }



}




//�ж��Ƿ�Ҫ����
bool Player::judgeForUpdate()
{
    if (myStore->money < 50 + EXP_FOR_UPGRADE)
        return false;
    else if (myStore->level < 4)
        return true;
    else
        return false;
}



//������:�������ǵ��ƿ��ܻ�ѱ�սϯ����.�ݲ�����
//�жϵ�ǰ״̬�Ƿ�Ҫˢ���̵�
//��ǰ������:����սϯ�����̶�����.�Լ���d
bool Player::judgeForRefresh()
{

    bool isThreeStar = 1;
    if (!myChessMap.size())
        isThreeStar = 0;
    for (auto a : myChessMap) {
        if (a.second->star != 3)
            isThreeStar = 0;
    }

    //��������ȫ������,��������d,�˳�
    if (isThreeStar)
        return false;

    //��ʣ��Ǯ��������ˢ�£���������d,�˳�
    if (myStore->money < MONEY_FOR_REFRESH * 3)
        return false;

    //��ȫ�����ж�֮��
    //��Ѫ�����㣬�������״̬����ÿ�غ϶�d��
    if (myHero->percentage <= 30)
        return true;

    //����������������һ��������������һ
    if (myStore->level + SEATS_NUM - 1 <= meleeAttacks.size() + rangedAttacks.size())
        return false;

    //��ǰ���Բ�����������,����Ϣd��
    if (!judgeForUpdate() && myStore->money > 50 + MONEY_FOR_REFRESH) {
        return true;
    }

    return false;



}


//ֻ��StoreAttribute�޷���ȡˢ�º���̵���,���
//��δִ��ˢ�²���
void Player::buyAndPlace()
{
    //�ѽ����Ӿ����ܰ�������,��սϯ������������
    placeChessToBoard();

    refreshStore();
    buyChess();
    //����ˢ�º͹�����ж�
    while (judgeForRefresh())
    {
        myStore->money -= 2;

        refreshStore();
        //���˵����Ӱ����ȼ�������սԶ�����������������̺ͱ�սϯ��Ա
        buyChess();

    }


    placeChessToBoard();


}



//�жϵ�ǰ�̵�,����������
void Player::buyChess()
{
    //�����̵��5������
    for (int i = 0; i < 5; i++) {


        //�ᱻ�ͷ���
        Chess* storeChess = ChessFactory::createChessById(myStore->idInStore[i]);


        //���Ѵ��˿�����
        //����ǰ���۵��������˺�,���ܺϳ�,����
        if (meleeAttacks.size() + rangedAttacks.size() >= myStore->level + SEATS_NUM - 1) {
            if (!canMerge(storeChess, false))
                continue;
        }


        //���ɽ׶�:�ȼ�С��3
        //һ������ֻ��������,�ж��ǾͲ�������
        if (storeChess->originalCost == 1 && myStore->level <= 3) {
            bool isExist = 0;

            for (Chess* c : meleeAttacks) {
                //������е�ǰ���������ӵĸ߽�
                if (c->id == storeChess->id && c->star >= storeChess->star) {
                    isExist = 1;
                    break;
                }
            }
            for (Chess* c : rangedAttacks) {
                //������е�ǰ���������ӵĸ߽�
                if (c->id == storeChess->id && c->star >= storeChess->star) {
                    isExist = 1;
                    break;
                }
            }
            if (isExist)
                continue;

        }
        //�ǹ��ɽ׶�,����1����
        else if (storeChess->originalCost == 1)
            continue;
        //ai����3�Ѹ߼�����
        else if (storeChess->originalCost == 3) {
            continue;
        }
        //�ж϶�������
        else if (storeChess->originalCost == 2) {
            //������е�ǰ���������ӵ�����,����
            bool isExist = 0;
            for (Chess* c : meleeAttacks) {
                if (c->id == storeChess->id && c->star == 3) {
                    isExist = 1;
                    break;
                }
            }
            for (Chess* c : rangedAttacks) {
                //������е�ǰ���������ӵ�����
                if (c->id == storeChess->id && c->star == 3) {
                    isExist = 1;
                    break;
                }
            }
            if (isExist)
                continue;

        }

        //���µ�ǰ���۵�����
        myStore->money -= storeChess->price;

        //ִ�кϳɲ���
        canMerge(storeChess, true);

        if (storeChess->isMelee)
            insertWithPriority(storeChess, meleeAttacks);
        else
            insertWithPriority(storeChess, rangedAttacks);


        //��Ӱ����������������,ֻӰ������,���
        myStore->idInStore[i] = -1;
        //������,����һ���жϵ�ʱ��, placeChessToBoardδ�����̷���,֮��Ҳ��������ӷ���������.��ʱ����
    }
}




//�жϴ���������Ƿ��ܺ����е����Ӻϳ�,����,����isToMergeִ�кϳ�
bool Player::canMerge(Chess* c, bool isToMerge)
{
    if (!c)
        return false;

    int count = 0;
    int index[2];
    //�ж��Ƿ�����ͬ�Ǽ�ͬ�������������,������������index
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

    //���ܺϳ�
    if (count == 2) {
        //��Ҫִ�кϳɲ���
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
        return true;
    }
    else {
        return false;
    }


}

//����һ�ξ���
void Player::buyExp()
{
    myStore->money -= EXP_FOR_UPGRADE;
    myStore->exp += EXP_FOR_UPGRADE;
    if (myStore->exp >= levelExp[myStore->level - 1]) {
        myStore->exp -= levelExp[myStore->level - 1];
        myStore->level++;
    }
}