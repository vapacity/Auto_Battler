#include "FightScene.h"

cocos2d::Scene* FightScene::createScene()
{
    // ����һ���������󣬸ö������Զ��ͷų��Զ��ͷ�
    auto scene = FightScene::create();
    return scene;
}
FiniteTimeAction* createSequenceFromVector(const Vector<FiniteTimeAction*>& actions, int index) {
    if (index >= actions.size() - 1) {
        // ���ֻʣһ��������û�ж�����ֱ�ӷ��ظö����� nullptr
        return index < actions.size() ? actions.at(index) : nullptr;
    }
    else {
        // �ݹ�ش�������
        // ȷ����ǰ������ݹ鷵�صĶ���˳����ȷ
        auto nextAction = createSequenceFromVector(actions, index + 1);
        return Sequence::createWithTwoActions(actions.at(index), nextAction);
    }
}

bool FightScene::init()
{
    // ���ȵ��û����init����
    if (!Scene::init())
    {
        return false;
    }
    initPlayer();
    initBackground();
    initGridMap();
    initPreparationSeats();
    initLittleHero();
    initStore();
    //moveChess(gridMap->myChessMap[Vec2(1, 0)], gridMap->myChessMap[Vec2(1, 0)]->stopMoveFlag);
    //initChessExp();
    findEnemyAndMove();
    gridMap->disableMouseListener();
}

void FightScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
    enemyPlayer->convertToEnemy();
}



void FightScene::initBackground()
{
    backgroundImg = Sprite::create("battle-background2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backgroundImg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundImg->setScaleX(visibleSize.width / backgroundImg->getContentSize().width);
    backgroundImg->setScaleY(visibleSize.height / backgroundImg->getContentSize().height);
    this->addChild(backgroundImg, -1);
}
void FightScene::initChessExp()
{
    //���ڲ���ͬʱ��������
  /*  auto Yevee = ChessFactory::createChessById(0);
    if (Yevee) {
        Yevee->setScale(0.15);

        gridMap->addChessToGrid(Yevee, gridMap->getCellAtPosition(Vec2(5, 5)));
        myPlayer->addChess(Yevee);
        Yevee->playerNumber = 1;
        this->addChild(Yevee, 1);
    }*/

    auto charmander = ChessFactory::createChessById(1);
    if (charmander) {
        charmander->setScale(0.15);
        gridMap->addChessToGrid(charmander, gridMap->getCellAtPosition(Vec2(4, 4)));
        myPlayer->addChess(charmander);
        charmander->playerNumber = 1;
        charmander->attackRange = 1;
        this->addChild(charmander, 1);
    }

}
void FightScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    //�˴���Ҫһ������ط����̵Ĳ�������
   /* for (auto& pair : enemyPlayer->transformedMap)
    {
        gridMap->addChessToGrid(pair.second, gridMap->getCellAtPosition(pair.first));
    }*/
    this->addChild(gridMap, 0);
    initChessExp();
    for (auto iter : gridMap->myChessMap)
    {
        iter.second->removeFromParent();
        this->addChild(iter.second, 1);
    }
    gridMap->selectSchedule(0);
}

void FightScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    this->addChild(preSeats);
}

void FightScene::initLittleHero()
{
    myLittleHero = myPlayer->myHero;

    //this->addChild(myLittleHero);
    //enemyLittleHero = enemyPlayer->myHero;
    //this->addChild(enemyLittleHero);
}

void FightScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void FightScene::moveChess(Chess* chessToMove,bool& stopMoveFlag)
{
    //�����ʼ������ֹ���
    HexCell* fromCell = gridMap->getCellAtPosition(chessToMove->atGridPosition);
    HexCell* toCell = gridMap->FindBattle(chessToMove, fromCell);

    //���·��
    Vector<HexCell*> movePath;
    gridMap->FindPath(movePath, chessToMove, fromCell, toCell,chessToMove->attackRange);

    //�ж��Ƿ���빥����Χ
    stopMoveFlag=judgeAttack(movePath);
    if (stopMoveFlag)
    {
        return;
    }
        

    //ֻȡ��һ��
    Vec2 firstMove = movePath.at(0)->getPosition();
    chessToMove->actions.pushBack(chessToMove->moveTo(firstMove));

    gridMap->addChessToGrid(chessToMove, movePath.at(0));
    gridMap->removeChessOfGrid(fromCell);
}

bool FightScene::judgeAttack(Vector<HexCell*> movePath)
{
    return !movePath.size();
}

bool FightScene::judgeAllDead()
{
    int cntMy = 0;
    int cntEnemy = 0;
    for (auto& iter : gridMap->myChessMap)
    {
        if (iter.second->playerNumber == myPlayer->playerNumber)
            cntMy++;
        else
            cntEnemy++;
    }
    return !(cntMy && cntEnemy);
}

void FightScene::findEnemyAndMove()
{
    Vector<Chess*> chessesOnMap;
    //����myChessMapȡ�����������ϵ�����
    for (auto iter : gridMap->myChessMap)
    {
        chessesOnMap.pushBack(iter.second);
    }
    //��ÿһ�����ӽ����ƶ�������ֱ�����е�����ֹͣ�ƶ�
    while (true) {
        //�����ƶ�����
        for (auto& chess :chessesOnMap)
        {
             //�ƶ�
             moveChess(chess, chess->stopMoveFlag);
             //���ƶ����ˣ�����Թ���
             if (chess->stopMoveFlag == 1)
             {
                 //�ж�Ŀ��λ���ܲ��ܴ�
                 HexCell* toCell = gridMap->FindBattle(chess, gridMap->getCellAtPosition(chess->atGridPosition));
                 if (toCell && toCell->chessInGrid && toCell->chessInGrid->health > 0)
                 {
                     Chess* attackedChess = toCell->chessInGrid;
                     chess->attack(attackedChess);

                     // ��鱻�����������Ƿ�����
                     if (attackedChess->health <= 0)
                     {
                         auto fadeOut = FadeOut::create(1.0f);
                         attackedChess->actions.pushBack(fadeOut);
                         gridMap->removeChessOfGrid(toCell);
                     }
                 }
             }

        }
        
        if (judgeAllDead())
            break;
    }
    for (auto chess: chessesOnMap)
    {
        auto sequence = createSequenceFromVector(chess->actions, 0);
        chess->runAction(sequence);
    }

}

void FightScene::locatdEnemyAndAttack(Chess* chess)
{
    HexCell* toCell = gridMap->FindBattle(chess, gridMap->getCellAtPosition(chess->atGridPosition));
    chess->attack(toCell->chessInGrid);

}
