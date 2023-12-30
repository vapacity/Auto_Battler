#include "FightScene.h"
#define enemyPosition Vec2(900,550)
#define myPosition Vec2(40,265)
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
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("battleMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);
    initPlayer();
    initBackground();
    initGridMap();
    //initPreparationSeats();
    initLittleHero();
    //initStore();
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
    //正在测试同时出现三个
  /*  auto Yevee = ChessFactory::createChessById(0);
    if (Yevee) {
        Yevee->setScale(0.15);

        gridMap->addChessToGrid(Yevee, gridMap->getCellAtPosition(Vec2(5, 5)));
        myPlayer->addChess(Yevee);
        Yevee->playerNumber = 1;
        this->addChild(Yevee, 1);
    }*/

    /*auto charmander = ChessFactory::createChessById(31);
    if (charmander) {
        charmander->setScale(0.15);
        gridMap->addChessToGrid(charmander, gridMap->getCellAtPosition(Vec2(4, 4)));
        myPlayer->addChess(charmander);
        charmander->reverseImg();
        charmander->playerNumber = 1;

        this->addChild(charmander, 1);
    }
    auto charmander2 = ChessFactory::createChessById(32);
    if (charmander2) {
        charmander2->setScale(0.15);
        gridMap->addChessToGrid(charmander2, gridMap->getCellAtPosition(Vec2(10, 7)));
        myPlayer->addChess(charmander2);
        charmander2->reverseImg();
        charmander2->playerNumber = 1;
        this->addChild(charmander2, 1);
    }*/
    //auto charmander3 = ChessFactory::createChessById(31);
    //if (charmander3) {
    //    charmander3->initHealthBar();
    //    charmander3->initBlueBar();
    //    charmander3->maxHP = charmander3->health;
    //    gridMap->addChessToGrid(charmander3, gridMap->getCellAtPosition(Vec2(10, 5)));
    //    //myPlayer->addChess(charmander3);
    //    charmander3->playerNumber = 1;
    //    charmander3->reverseImg();
    //    this->addChild(charmander3, 1);
    //}

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
        newChess->playerNumber = 1 - myPlayer->playerNumber;
        gridMap->nodeMap.at(a.first)->chessInGrid = newChess;
        gridMap->addChessToGrid(newChess, gridMap->getCellAtPosition(a.first));
        this->addChild(newChess, 2);
    }
}
void FightScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    createChessOnGrids();
    this->addChild(gridMap, 0);
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
    myLittleHero->setPosition(myPosition);
    this->addChild(myLittleHero);
    myLittleHero->isAnimationPlaying = false;
    myLittleHero->enableMoving();
    enemyLittleHero = enemyPlayer->myHero;
    enemyLittleHero->setEnemey();
    if (enemyLittleHero->getParent())
        enemyLittleHero->removeFromParent();
    enemyLittleHero->setColor(Color3B(180,180,180));
    enemyLittleHero->setPosition(enemyPosition);
    this->addChild(enemyLittleHero);
    enemyLittleHero->isAnimationPlaying = false;
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
    if (cntEnemy == 0 && cntMy == 0)
    {
        std::string str = "Draw";
        auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 80); // 字体文件需要存在

        // 设置Label的颜色（可选）
        label->setColor(Color3B::WHITE);

        // 获取场景的尺寸和中心坐标
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // 设置Label的位置
        label->setPosition(centerPosition);

        // 将Label添加到当前场景
        this->addChild(label, 2); // 第二个参数是z-order，可以根据需要调整
        auto delay = cocos2d::DelayTime::create(2);

        auto callback = cocos2d::CallFunc::create([this]() {

            if (myLittleHero->percentage <= 0 || enemyLittleHero->percentage <= 0)
            {
                FightScene::goToGameOverScene();
            }
            else {
                FightScene::goToPrepareScene();
            }
            });

        auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);


        this->runAction(sequence);
        return;
    }
    else if (cntEnemy == 0|| cntMy == 0) {
        // 创建一个Label
        std::string str= cntEnemy == 0 ? "You Win" : "Enemy Win";
        if (cntEnemy == 0)
            myLittleHero->attack(enemyLittleHero);
        else
            enemyLittleHero->attack(myLittleHero);
        auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 80); // 字体文件需要存在

        // 设置Label的颜色（可选）
        label->setColor(Color3B::WHITE);

        // 获取场景的尺寸和中心坐标
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // 设置Label的位置
        label->setPosition(centerPosition);

        // 将Label添加到当前场景
        this->addChild(label, 2); // 第二个参数是z-order，可以根据需要调整
        auto delay = cocos2d::DelayTime::create(2);

        auto callback = cocos2d::CallFunc::create([this]() {
            
            if (myLittleHero->percentage <= 0||enemyLittleHero->percentage<=0)
            {
                FightScene::goToGameOverScene();
            }
            else {
                FightScene::goToPrepareScene();
            }
            });

        auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);


        this->runAction(sequence);
    }


}

void FightScene::menuPlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        AudioManager::playEffect();
    }
    //把原数据删除再离开场景
    PlayerManager::getInstance()->getPlayer(0)->deletePast();
    PlayerManager::getInstance()->getPlayer(1)->deletePast();
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("prepareMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);
    Director::getInstance()->popScene(); // 切换到playscene场景
}

void FightScene::goToPrepareScene()
{
    auto prepareScene = PrepareScene::create();
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("prepareMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);
    cocos2d::Director::getInstance()->replaceScene(prepareScene);
}

void FightScene::goToGameOverScene()
{
    // 创建新的场景
    auto gameOverScene = GameOverScene::createScene();
    experimental::AudioEngine::stop(globalAudioId);
    //experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);
    // 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(gameOverScene);
}