#include "FightScene.h"

cocos2d::Scene* FightScene::createScene()
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = FightScene::create();
    return scene;
}
FiniteTimeAction* createSequenceFromVector(const Vector<FiniteTimeAction*>& actions, int index) {
    if (index >= actions.size() - 1) {
        // 如果只剩一个动作或没有动作，直接返回该动作或 nullptr
        return index < actions.size() ? actions.at(index) : nullptr;
    }
    else {
        // 递归地创建序列
        // 确保当前动作与递归返回的动作顺序正确
        auto nextAction = createSequenceFromVector(actions, index + 1);
        return Sequence::createWithTwoActions(actions.at(index), nextAction);
    }
}

bool FightScene::init()
{
    // 首先调用基类的init方法
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
    //正在测试同时出现三个
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
    //此处需要一个导入地方棋盘的操作！！
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
    //获得起始棋格和终止棋格
    HexCell* fromCell = gridMap->getCellAtPosition(chessToMove->atGridPosition);
    HexCell* toCell = gridMap->FindBattle(chessToMove, fromCell);

    //获得路径
    Vector<HexCell*> movePath;
    gridMap->FindPath(movePath, chessToMove, fromCell, toCell,chessToMove->attackRange);

    //判断是否进入攻击范围
    stopMoveFlag=judgeAttack(movePath);
    if (stopMoveFlag)
    {
        return;
    }
        

    //只取第一步
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
    //遍历myChessMap取出所有棋盘上的棋子
    for (auto iter : gridMap->myChessMap)
    {
        chessesOnMap.pushBack(iter.second);
    }
    //对每一个棋子进行移动操作，直到所有的棋子停止移动
    while (true) {
        //遍历移动棋子
        for (auto& chess :chessesOnMap)
        {
             //移动
             moveChess(chess, chess->stopMoveFlag);
             //若移动不了，则可以攻击
             if (chess->stopMoveFlag == 1)
             {
                 //判断目标位置能不能打
                 HexCell* toCell = gridMap->FindBattle(chess, gridMap->getCellAtPosition(chess->atGridPosition));
                 if (toCell && toCell->chessInGrid && toCell->chessInGrid->health > 0)
                 {
                     Chess* attackedChess = toCell->chessInGrid;
                     chess->attack(attackedChess);

                     // 检查被攻击的棋子是否死亡
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
