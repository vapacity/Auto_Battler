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
    //findEnemyAndMove();
    gridMap->disableMouseListener();
    this->schedule([this](float dt) {this->update(dt); }, "update_key");
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

    auto charmander = ChessFactory::createChessById(31);
    if (charmander) {
        charmander->setScale(0.15);
        gridMap->addChessToGrid(charmander, gridMap->getCellAtPosition(Vec2(4, 4)));
        //myPlayer->addChess(charmander);
        charmander->reverseImg();
        charmander->playerNumber = 1;

        this->addChild(charmander, 1);
    }
    auto charmander2 = ChessFactory::createChessById(32);
    if (charmander2) {
        charmander2->setScale(0.15);
        gridMap->addChessToGrid(charmander2, gridMap->getCellAtPosition(Vec2(10, 7)));
        //myPlayer->addChess(charmander2);
        charmander2->reverseImg();
        charmander2->playerNumber = 1;
        this->addChild(charmander2, 1);
    }
    auto charmander3 = ChessFactory::createChessById(33);
    if (charmander3) {
        charmander3->setScale(0.15);
        gridMap->addChessToGrid(charmander3, gridMap->getCellAtPosition(Vec2(10, 5)));
        //myPlayer->addChess(charmander3);
        charmander3->playerNumber = 1;
        charmander3->reverseImg();
        this->addChild(charmander3, 1);
    }

}
void FightScene::createChessOnGrids()
{
    for (auto a : myPlayer->myChessMap) {
        int newChessId = a.second->id;
        int newChessStar = a.second->star;
        Chess* newChess = Chess::createByIdAndStar(newChessId, newChessStar);
        gridMap->nodeMap.at(a.first)->chessInGrid = newChess;
        gridMap->addChessToGrid(newChess, gridMap->getCellAtPosition(a.first));
        this->addChild(newChess, 2);
    }
    for (auto a : enemyPlayer->transformedMap) {
        int newChessId = a.second->id;
        int newChessStar = a.second->star;
        Chess* newChess = Chess::createByIdAndStar(newChessId, newChessStar);
        newChess->reverseImg();
        newChess->playerNumber = 1-myPlayer->playerNumber;
        gridMap->nodeMap.at(a.first)->chessInGrid = newChess;
        gridMap->addChessToGrid(newChess, gridMap->getCellAtPosition(a.first));
        this->addChild(newChess, 2);
    }
}
void FightScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    //�˴���Ҫһ������ط����̵Ĳ�������
    //for (auto& pair : enemyPlayer->transformedMap)
    //{
    //    gridMap->addChessToGrid(pair.second, gridMap->getCellAtPosition(pair.first));
    //    //myPlayer->addChess(pair.second);
    //    pair.second->reverseImg();
    //    pair.second->playerNumber = 1;
    //    gridMap->nodeMap.at(pair.first)->chessInGrid = pair.second;
    //    //gridMap->myChessMap.insert(pair);
    //}
    createChessOnGrids();

    this->addChild(gridMap, 0);
    //initChessExp();
    /*for (auto iter : gridMap->myChessMap)
    {
        if(iter.second->getParent())
            iter.second->removeFromParent();
        this->addChild(iter.second, 1);
    }*/
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
    if (myLittleHero->getParent())
        myLittleHero->removeFromParent();
    this->addChild(myLittleHero);

    enemyLittleHero = enemyPlayer->myHero;
    if (enemyLittleHero->getParent())
        enemyLittleHero->removeFromParent();
    enemyLittleHero->setScaleX(enemyLittleHero->getScaleX() * -1);
    this->addChild(enemyLittleHero);
    //this->addChild(myLittleHero);
    //enemyLittleHero = enemyPlayer->myHero;
    //this->addChild(enemyLittleHero);
}

void FightScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void FightScene::update(float dt)
{
    Vector<Chess*> chesses;
    for (auto& chess : gridMap->myChessMap)
    {
        chesses.pushBack(chess.second);
    }

    for (auto& chess : chesses)
    {
        chess->updateInBattle(dt, gridMap);
    }
    updateWin(dt);
}

void FightScene::updateWin(float dt)
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
    if (cntEnemy == 0) {
        //myLittleHero->attack(enemyLittleHero);
        // ����һ��Label
        auto label = Label::createWithTTF("You Win", "fonts/Marker Felt.ttf", 80); // �����ļ���Ҫ����

        // ����Label����ɫ����ѡ��
        label->setColor(Color3B::WHITE);

        // ��ȡ�����ĳߴ����������
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // ����Label��λ��
        label->setPosition(centerPosition);

        // ��Label��ӵ���ǰ����
        this->addChild(label, 2); // �ڶ���������z-order�����Ը�����Ҫ����
        auto delay = cocos2d::DelayTime::create(2);

        // ����һ���ص�����������ִ����Ҫ�ȴ��Ĳ���
        auto callback = cocos2d::CallFunc::create([this]() {
            FightScene::goToPrepareScene();

            });

        // ����һ��˳�������ȵȴ���Ȼ��ִ�лص�����
        auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);

        // ���ж���
        this->runAction(sequence);
    }
    else if (cntMy == 0) {
        // ����һ��Label
        //enemyLittleHero->attack(myLittleHero);
        auto label = Label::createWithTTF("Enemy Win", "fonts/Marker Felt.ttf", 80); // �����ļ���Ҫ����

        // ����Label����ɫ����ѡ��
        label->setColor(Color3B::WHITE);

        // ��ȡ�����ĳߴ����������
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // ����Label��λ��
        label->setPosition(centerPosition);

        // ��Label��ӵ���ǰ����
        this->addChild(label, 2); // �ڶ���������z-order�����Ը�����Ҫ����
        auto delay = cocos2d::DelayTime::create(2);

        // ����һ���ص�����������ִ����Ҫ�ȴ��Ĳ���
        auto callback = cocos2d::CallFunc::create([this]() {
            FightScene::goToPrepareScene();
            });

        // ����һ��˳�������ȵȴ���Ȼ��ִ�лص�����
        auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);

        // ���ж���
        this->runAction(sequence);
    }
}

void FightScene::goToPrepareScene()
{
    // �����µĳ���
    auto prepareScene = PrepareScene::create();

    // �л����³���
    cocos2d::Director::getInstance()->replaceScene(prepareScene);
}

