// PrepareScene.cpp
#include "cocos2d.h"
#include "OnlinePrepareScene.h"
#define enemyPosition Vec2(1060,600)
#define myPosition Vec2(60,265)
USING_NS_CC;
#define PREPARE_TIME 10.0f

Scene* OnlinePrepareScene::createScene()
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = OnlinePrepareScene::create();
    return scene;
}

bool OnlinePrepareScene::init()
{
    // 首先调用基类的init方法
    if (!Scene::init())
    {
        return false;
    }


    //回退按钮
    initBack();

    initPlayer();

    //添加背景图片
    initBackground();

    //创建初始棋盘
    initGridMap();


    //创建备战席
    initPreparationSeats();

    //创建商店
    initStore();


    //初始化小小英雄
    initLittleHero();

    //测试棋子用函数，一般注释掉
    //initChessExp();

    //启用鼠标监听器
    initPrepareLabel();
    this->enableMouseListener();
    gridMap->enableMouseListener();
    //此处为寻路测试
    /*Vector<HexCell*> path;
    HexCell* toNode=nullptr;
    gridMap->getCellAtPosition(Vec2(1, 1))->chessInGrid->moveTo(gridMap->FindBattle(gridMap->getCellAtPosition(Vec2(1, 1))->chessInGrid, gridMap->getCellAtPosition(Vec2(1, 1)))->getPosition());*/

    this->schedule(schedule_selector(OnlinePrepareScene::updateCountdownLabel), 0.01f);  // 每隔1秒更新一次Label

    return true;
}
void OnlinePrepareScene::initBack()
{
    Vector<MenuItem*> MenuItems_fight;
    //回退
    auto backItem = MenuItemImage::create(
        "smallbacknormal.png",
        "smallbackselected.png",
        CC_CALLBACK_1(OnlinePrepareScene::menuPlayCallback, this));

    if (!(backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0))
    {//退出菜单项有效，接下来会计算退出菜单项的位置
        // 获取场景的尺寸和中心坐标
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        float x = origin.x + visibleSize.width * 17 / 18;
        float y = origin.y + visibleSize.height * 14 / 15;
        backItem->setPosition(Vec2(x, y));
    }
    MenuItems_fight.pushBack(backItem);
    auto menu = Menu::createWithArray(MenuItems_fight);//创建菜单
    menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
    this->addChild(menu, 2);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方
}
void OnlinePrepareScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
    myPlayer->myStore->money += myPlayer->myStore->interest + INIT_ADD_FOR_TURN;
    if (myPlayer->myStore->level < 5)
    {
        myPlayer->myStore->exp += 2;
        if (myPlayer->myStore->exp >= levelExp[myPlayer->myStore->level - 1]) {
            myPlayer->myStore->exp -= levelExp[myPlayer->myStore->level - 1];
            myPlayer->myStore->level++;
        }
    }

}
void OnlinePrepareScene::initBackground()
{
    backgroundImg = Sprite::create("battle-background2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backgroundImg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundImg->setScaleX(visibleSize.width / backgroundImg->getContentSize().width);
    backgroundImg->setScaleY(visibleSize.height / backgroundImg->getContentSize().height);
    this->addChild(backgroundImg, -1);
}

void OnlinePrepareScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    this->addChild(gridMap, 0);
    putChessOnGrids();
    gridMap->selectSchedule(1);
}

void OnlinePrepareScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    putChessOnSeats();
    this->addChild(preSeats);
}


void OnlinePrepareScene::initLittleHero()
{
    //littleHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    littleHero = myPlayer->myHero;
    littleHeroEnemy = enemyPlayer->myHero;
    if (littleHero->getParent())
        littleHero->removeFromParent();
    if (myPlayer->playerNumber == 0) {
        littleHero->setPosition(myPosition);
    }
    else {
        littleHero->setPosition(enemyPosition);
    }
    littleHero->enableMoving();
    this->addChild(littleHero);
}


void OnlinePrepareScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void OnlinePrepareScene::initPrepareLabel()
{
    // 初始化线段
    countdownLine = DrawNode::create();
    countdownLine->setAnchorPoint(Vec2(0, 0.5));
    countdownLine->setPosition(Vec2(0, 100));
    this->addChild(countdownLine);
    // 初始化Label
    countdownLabel = Label::createWithTTF("10", "fonts/arial.ttf", 50);
    countdownLabel->setPosition(Vec2(270, 700));
    this->addChild(countdownLabel);

    remainingTime = PREPARE_TIME;
}

void OnlinePrepareScene::putChessOnGrids()
{
    for (auto a : myPlayer->myChessMap) {
        if (a.second->getParent())
            a.second->removeFromParent();
        gridMap->nodeMap.at(a.first)->chessInGrid = a.second;
        gridMap->addChessToGrid(a.second, gridMap->getCellAtPosition(a.first));
        this->addChild(a.second, 2);
        a.second->setOpacity(255);
    }
}
void OnlinePrepareScene::putChessOnSeats()
{
    for (int i = 0; i < SEATS_NUM; i++)
    {
        if (auto iter = myPlayer->mySeats[i])
        {
            if (iter->getParent())
                iter->removeFromParent();
            preSeats->addChessToSeat(iter, preSeats->seatsArray.at(i));
            this->addChild(iter, 2);
        }
    }
}
void OnlinePrepareScene::enableMouseListener()
{
    prepareSceneMouseListener = EventListenerMouse::create();
    prepareSceneMouseListener->onMouseDown = CC_CALLBACK_1(OnlinePrepareScene::prepareSceneOnMouseDown, this);
    prepareSceneMouseListener->onMouseMove = CC_CALLBACK_1(OnlinePrepareScene::prepareSceneOnMouseMove, this);
    prepareSceneMouseListener->onMouseUp = CC_CALLBACK_1(OnlinePrepareScene::prepareSceneOnMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(prepareSceneMouseListener, this);

}


void OnlinePrepareScene::prepareSceneOnMouseDown(Event* event)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 处理鼠标左键按下事件
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

        CCLOG("PrepareScene:Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();

        /*此部分为对拖拽棋子的判断*/
        chessOnMouseDown(mousePosition);

        /*此部分为对点击图片的判断*/
        store->selectStore(event, mousePosition, preSeats->isFull());//store监听函数
        if (store->chessIdHaveBought != -1)
        {
            Chess* chess = ChessFactory::createChessById(store->chessIdHaveBought);
            chess->maxHP = chess->health;
            if (chess)
            {
                //检查新增的这个是否能合成
                preSeats->addChessToSeat(chess, preSeats->latestSeat);
                myPlayer->addChess(chess);
                this->addChild(chess, 1);
                checkAndMerge(chess);
            }
            store->chessIdHaveBought = -1;
        }
    }
}

void OnlinePrepareScene::prepareSceneOnMouseMove(Event* event)
{
    //CCLOG("MousMove");
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();

    Vec2 location = Director::getInstance()->convertToGL(mousePosition);

    /*此部分为对拖拽棋子的判断*/
    chessOnMouseMove(mousePosition);
    return;
}

void OnlinePrepareScene::prepareSceneOnMouseUp(Event* event)
{
    CCLOG("MouseUp");
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();

    /*此部分为对拖拽棋子的判断*/
    chessOnMouseUp(mousePosition);
    return;

}

//鼠标按下
void OnlinePrepareScene::chessOnMouseDown(Vec2 mousePosition)
{

    //实现判断单击时是否有棋格，且棋格上是否存在棋子
    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);

    if (cell && cell->chessInGrid)
    {
        selectedChess = cell->chessInGrid;
        //selectedChess->atGridPosition = cell;
        selectedChess->isDragging = true;

        gridMap->removeChessOfGrid(cell);
        myPlayer->removeChess(selectedChess);


    }
    if (seat && seat->chessInSeat)
    {
        selectedChess = seat->chessInSeat;
        //selectedChess->atSeat = seat;
        selectedChess->isDragging = true;

        preSeats->removeChessOfSeat(seat);
        myPlayer->removeChess(selectedChess);

    }
}

//鼠标移动
void OnlinePrepareScene::chessOnMouseMove(Vec2 mousePosition)
{
    if (selectedChess)
        if (selectedChess->isDragging)
        {
            for (auto iter : gridMap->nodeMap)
            {
                if ((!iter.second->isMine == myPlayer->playerNumber))
                    iter.second->turnToSeen();
            }
            selectedChess->setPosition(mousePosition);
        }
}

//鼠标抬起
void OnlinePrepareScene::chessOnMouseUp(Vec2 mousePosition)
{
    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);
    //若有已经在被拖动的棋子
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;



        if (gridMap->chessAmount >= myPlayer->myStore->level && cell && !cell->chessInGrid) {
            createText("Level Is Not Enough");
            CCLOG("PrepareScene:swap failed");
            gridMap->addChessToGrid(selectedChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(selectedChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));

            myPlayer->addChess(selectedChess);
        }
        //此处判断鼠标位置所处棋格是否存在
        //1 棋格存在且位置上无棋子,将棋子放置在新的位置上
        else if (cell && !cell->chessInGrid && (!cell->isMine == myPlayer->playerNumber))
        {
            CCLOG("PrepareScene:put Chess on Grid");
            gridMap->addChessToGrid(selectedChess, cell);
            myPlayer->addChess(selectedChess);
        }
        else if (seat && !seat->chessInSeat)
        {
            CCLOG("PrepareScene:put Chess on Seat");
            preSeats->addChessToSeat(selectedChess, seat);
            myPlayer->addChess(selectedChess);
        }
        //2 棋格存在且位置上有棋子
        else if (cell && cell->chessInGrid && (!cell->isMine==myPlayer->playerNumber))
        {
            CCLOG("PrepareScene:swap Cell and Something");

            Chess* moveChess = cell->chessInGrid;
            //将该位置上的棋子清除
            myPlayer->removeChess(moveChess);
            gridMap->removeChessOfGrid(cell);

            //将该位置处的棋子添加到selectedChess的位置
            gridMap->addChessToGrid(moveChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(moveChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(moveChess);

            //将selectedChess添加到这个位置上
            gridMap->addChessToGrid(selectedChess, cell);
            myPlayer->addChess(selectedChess);
        }
        else if (seat && seat->chessInSeat)
        {
            CCLOG("PrepareScene:swap Seat and Something");
            Chess* moveChess = seat->chessInSeat;
            //将该位置上的棋子清除
            myPlayer->removeChess(seat->chessInSeat);
            preSeats->removeChessOfSeat(seat);

            //将该位置处的棋子添加到selectedChess的位置
            gridMap->addChessToGrid(moveChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(moveChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(moveChess);

            //将selectedChess添加到这个位置上
            preSeats->addChessToSeat(selectedChess, seat);
            myPlayer->addChess(selectedChess);
        }
        //4 不存在棋格，但位于商店
        else if (mousePosition.y <= store->storeAreaHeight)
        {
            CCLOG("PrepareScene: chess to be sold");
            myPlayer->myStore->money += selectedChess->price;
            selectedChess->deleteChess();

        }
        //让棋格退回原来位置
        else
        {
            CCLOG("PrepareScene:swap failed");
            gridMap->addChessToGrid(selectedChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(selectedChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(selectedChess);
        }
        for (auto iter : gridMap->nodeMap)
        {
            if ((!iter.second->isMine == myPlayer->playerNumber))
                iter.second->turnToNormal();
        }
        selectedChess = nullptr;
    }

}

void OnlinePrepareScene::checkAndMerge(Chess* chess)
{
    int chessId = chess->getId();
    if (myPlayer->chessCount[std::make_pair(chess->getId(), chess->getStar())] >= 3)
    {
        //此处需要注意有连续进化的可能，用递归形式容易理解
        checkAndMerge(upgradeChess(chess->getId(), chess->getStar()));
    }
    else
    {
        return;
    }
}

Chess* OnlinePrepareScene::upgradeChess(int id, int star)
{
    //upgradeChess用于保存第一个检测到的棋子，将基于他进化
    Chess* upgradeChess = nullptr;
    for (int i = 0; i < SEATS_NUM; i++)
    {
        if (preSeats->mySeats[i]->getId() == id && preSeats->mySeats[i]->getStar() == star)
        {
            auto chessRemove = preSeats->mySeats[i];
            if (upgradeChess == nullptr) {
                upgradeChess = chessRemove;
                myPlayer->removeChess(chessRemove);
            }
            else {
                myPlayer->removeChess(chessRemove);
                preSeats->removeChessOfSeat(preSeats->getSeatAtPosition(chessRemove->atSeatPosition));
                chessRemove->deleteChess();
            }
        }
    }
    //先保存与传入值相同的棋盘上的棋子key值
    std::vector<Vec2> keysToRemove;
    for (auto pair : myPlayer->myChessMap)
    {
        if (pair.second->getId() == id && pair.second->getStar() == star)
        {
            keysToRemove.push_back(pair.first);
        }
    }
    //再依次处理
    for (const auto& key : keysToRemove)
    {
        auto chessRemove = myPlayer->myChessMap[key];
        if (upgradeChess == nullptr) {
            upgradeChess = chessRemove;
            myPlayer->removeChess(chessRemove);
        }
        else {
            myPlayer->removeChess(chessRemove);
            gridMap->removeChessOfGrid(gridMap->getCellAtPosition(chessRemove->atGridPosition));
            chessRemove->deleteChess();
        }
    }
    //根据star，决定是进化成star2还是star3
    cocos2d::experimental::AudioEngine::play2d("upgradeEffect.mp3", false);
    upgradeChess->upgrade();
    myPlayer->addChess(upgradeChess);
    return upgradeChess;
}

void OnlinePrepareScene::goToFightScene(float dt)
{
    // 创建新的场景
    auto fightScene = OnlineFightScene::create();
    //切换音乐
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("battleMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);
    // 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(fightScene);
}

void OnlinePrepareScene::menuPlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    //把原数据删除再离开场景
    PlayerManager::getInstance()->getPlayer(0)->deletePast();
    PlayerManager::getInstance()->getPlayer(1)->deletePast();

    Director::getInstance()->popScene(); // 切换到playscene场景
}

void OnlinePrepareScene::updateCountdownLabel(float dt) {
    remainingTime -= dt;
    int seconds = static_cast<int>(remainingTime) + 1;

    // 计算线段长度比例
    float lengthRatio = remainingTime / PREPARE_TIME;

    // 计算线段的宽度，可以根据需要调整
    float lineWidth = 30.0f;

    // 更新线段的长度
    countdownLine->clear();

    countdownLine->drawLine(Vec2(300, 600), Vec2(300 + 700 * lengthRatio, 600), Color4F::WHITE);
    countdownLine->setLineWidth(lineWidth);

    // 更新Label的文本
    countdownLabel->setString(StringUtils::format("%d", seconds));

    // 如果时间到，跳转到下一个场景
    if (remainingTime <= 0) {
        gridMap->disableMouseListener();
        //this->disableMouseListener();
        if (selectedChess)
        {
            CCLOG("PrepareScene:swap failed");
            gridMap->addChessToGrid(selectedChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(selectedChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(selectedChess);
        }
        for (auto iter : preSeats->seatsArray)
            iter->turnToNormal();
        selectedChess = nullptr;
        goToFightScene(0); // 这里的参数可以根据你的需要传递
    }
}
//输出随输入改变的提示，并在一段时间后自动移除
void OnlinePrepareScene::createText(const std::string& textContent)
{
    unschedule(CC_SCHEDULE_SELECTOR(OnlinePrepareScene::updateText));
    if (fadingText) {
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
    fadingText = Label::createWithTTF(textContent, "fonts/arial.ttf", 36);
    fadingText->setPosition(Vec2(600, 600));
    this->addChild(fadingText);

    elapsedTime = 0.0f;

    schedule(CC_SCHEDULE_SELECTOR(OnlinePrepareScene::updateText));


}

//createText的调度器用，使提示逐渐淡出
void OnlinePrepareScene::updateText(float dt)
{
    elapsedTime += dt;

    int opacity = 255 - static_cast<int>(elapsedTime * 200);

    fadingText->setOpacity(opacity);

    //完全透明后停止调度器
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(OnlinePrepareScene::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
}
