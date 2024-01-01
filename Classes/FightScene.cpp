#include "FightScene.h"
#define enemyPosition Vec2(1060,600)
#define myPosition Vec2(60,265)

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
    initLittleHero();
    gridMap->disableMouseListener();//鼠标不能和棋盘交互
    this->schedule([this](float dt) {this->update(dt); }, "update_key");

}

void FightScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);//获取我方玩家信息
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);//敌方
    enemyPlayer->convertToEnemy();//敌方位置要反转
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

void FightScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    createChessOnGrids();//创建棋盘上的棋子
    this->addChild(gridMap, 0);
    gridMap->selectSchedule(0);
}

void FightScene::createChessOnGrids()
{
    //把棋盘上的棋子依次显示出来
    for (auto a : myPlayer->myChessMap) {
        //创建棋子实例
        int newChessId = a.second->id;
        int newChessStar = a.second->star;
        Chess* newChess = Chess::createByIdAndStar(newChessId, newChessStar);

        //图像反转
        newChess->reverseImg();

        //录入棋格上的棋子信息
        gridMap->nodeMap.at(a.first)->chessInGrid = newChess;
        //把棋子放在棋盘上
        gridMap->addChessToGrid(newChess, gridMap->getCellAtPosition(a.first));
        //加入场景
        this->addChild(newChess, 2);
    } 

    for (auto a : enemyPlayer->transformedMap) {//敌方反转

        int newChessId = a.second->id;
        int newChessStar = a.second->star;
        Chess* newChess = Chess::createByIdAndStar(newChessId, newChessStar);

        //棋子所属玩家编号
        newChess->playerNumber = 1 - myPlayer->playerNumber;

        gridMap->nodeMap.at(a.first)->chessInGrid = newChess;
        gridMap->addChessToGrid(newChess, gridMap->getCellAtPosition(a.first));
        this->addChild(newChess, 2);
    }
}

void FightScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    this->addChild(preSeats);
}

void FightScene::initLittleHero()
{
    //我方小小英雄
    myLittleHero = myPlayer->myHero;
    if (myLittleHero->getParent())
        myLittleHero->removeFromParent();

    myLittleHero->setPosition(myPosition);
    this->addChild(myLittleHero);
    myLittleHero->isAnimationPlaying = false;
    myLittleHero->enableMoving();

    //敌方
    enemyLittleHero = enemyPlayer->myHero;
    enemyLittleHero->setEnemey();//设成敌人
    if (enemyLittleHero->getParent())
        enemyLittleHero->removeFromParent();

    enemyLittleHero->setColor(Color3B(180,180,180));//用颜色区分敌我
    enemyLittleHero->setPosition(enemyPosition);
    this->addChild(enemyLittleHero);
    enemyLittleHero->isAnimationPlaying = false;
    enemyLittleHero->disableMoving();//防止我方能控制对方英雄
}

void FightScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

//提取出我方棋盘上的棋子，依次更新战斗状态，判断是否决出胜负
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
    //统计双方棋子数量
    int cntMy = 0;
    int cntEnemy = 0;
    for (auto& iter : gridMap->myChessMap)
    {
        //根据棋子所属玩家编号区分
        if (iter.second->playerNumber == myPlayer->playerNumber)
            cntMy++;
        else
            cntEnemy++;
    }

    if (cntEnemy == 0|| cntMy == 0) {
        // 创建一个Label
        std::string str= cntEnemy == 0 ? "You Win" : "Enemy Win";
        if (cntEnemy == 0)
        {
            myLittleHero->attack(enemyLittleHero);
        }
        else
        {
            enemyLittleHero->attack(myLittleHero);
        }
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
            //有一方死了，结束游戏
            if (myLittleHero->percentage <= 0||enemyLittleHero->percentage<=0)
            {
                FightScene::goToGameOverScene();
            }
            else {//没死继续
                FightScene::goToPrepareScene();
            }
            });

        auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);
        this->runAction(sequence);
    }

}

void FightScene::goToPrepareScene()
{
    auto prepareScene = PrepareScene::create();
    experimental::AudioEngine::stop(globalAudioId);
    //切换音乐
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("prepareMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);
    //切换场景
    cocos2d::Director::getInstance()->replaceScene(prepareScene);
}

void FightScene::goToGameOverScene()
{
    // 创建新的场景
    auto gameOverScene = GameOverScene::createScene();
    //停止音乐
    experimental::AudioEngine::stop(globalAudioId);
    // 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(gameOverScene);
}