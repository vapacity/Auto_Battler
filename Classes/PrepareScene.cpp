// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
USING_NS_CC;
#define PREPARE_TIME 10.0f
#define myPosition Vec2(40,265)

Scene* PrepareScene::createScene()
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = PrepareScene::create();
    return scene;
}

bool PrepareScene::init()
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

    //初始化倒计时
    initPrepareLabel();


    //启用鼠标监听器
    this->enableMouseListener();
    gridMap->enableMouseListener();
    //此处为寻路测试
    /*Vector<HexCell*> path;
    HexCell* toNode=nullptr;
    gridMap->getCellAtPosition(Vec2(1, 1))->chessInGrid->moveTo(gridMap->FindBattle(gridMap->getCellAtPosition(Vec2(1, 1))->chessInGrid, gridMap->getCellAtPosition(Vec2(1, 1)))->getPosition());*/

    this->schedule(schedule_selector(PrepareScene::updateCountdownLabel), 0.01f);  // 每隔1秒更新一次Label

    return true;
}

void PrepareScene::initBack()
{
    Vector<MenuItem*> MenuItems_fight;
    //回退
    auto backItem = MenuItemImage::create(
        "smallbacknormal.png",
        "smallbackselected.png",
        CC_CALLBACK_1(PrepareScene::menuPlayCallback, this));

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

void PrepareScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
    enemyPlayer->ai();//人机对战，对手是ai功能
    myPlayer->myStore->money += myPlayer->myStore->interest + INIT_ADD_FOR_TURN;//玩家金钱
    if (myPlayer->myStore->level < 5)
    {
        myPlayer->myStore->exp += 2;
        if (myPlayer->myStore->exp >= levelExp[myPlayer->myStore->level - 1]) {
            myPlayer->myStore->exp -= levelExp[myPlayer->myStore->level - 1];
            myPlayer->myStore->level++;
        }

    }
}
void PrepareScene::initBackground()
{
    backgroundImg = Sprite::create("battle-background2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backgroundImg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundImg->setScaleX(visibleSize.width / backgroundImg->getContentSize().width);
    backgroundImg->setScaleY(visibleSize.height / backgroundImg->getContentSize().height);
    this->addChild(backgroundImg, -1);
}

void PrepareScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    this->addChild(gridMap, 0);
    putChessOnGrids();
    gridMap->selectSchedule(1);
}

void PrepareScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    putChessOnSeats();
    this->addChild(preSeats);
}


void PrepareScene::initLittleHero()
{
    littleHero = myPlayer->myHero;
    if (littleHero->getParent())
        littleHero->removeFromParent();
    this->addChild(myPlayer->myHero, 1);
    littleHero->enableMoving();
    littleHero->setPosition(myPosition);
}


void PrepareScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void PrepareScene::initPrepareLabel()
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

void PrepareScene::putChessOnGrids()
{
    for (auto a : myPlayer->myChessMap) {
        if (a.second->getParent())
            a.second->removeFromParent();
        gridMap->nodeMap.at(a.first)->chessInGrid = a.second;
        gridMap->addChessToGrid(a.second, gridMap->getCellAtPosition(a.first));
        this->addChild(a.second, 2);
        a.second->setOpacity(255);//不透明
    }
}
void PrepareScene::putChessOnSeats()
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
void PrepareScene::enableMouseListener()
{
    prepareSceneMouseListener = EventListenerMouse::create();
    prepareSceneMouseListener->onMouseDown = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseDown, this);
    prepareSceneMouseListener->onMouseMove = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseMove, this);
    prepareSceneMouseListener->onMouseUp = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(prepareSceneMouseListener, this);

}


void PrepareScene::prepareSceneOnMouseDown(Event* event)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 处理鼠标左键按下事件
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

        CCLOG("PrepareScene:Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();

        /*此部分为对拖拽棋子的判断*/
        chessOnMouseDown(mousePosition);

        /*此部分为对点击卡牌的判断*/
        store->selectStore(event, mousePosition, preSeats->isFull());//store监听函数
        if (store->chessIdHaveBought != -1)//成功购买
        {
            Chess* chess = ChessFactory::createChessById(store->chessIdHaveBought);//生成棋子实例
            chess->maxHP = chess->health;
            if (chess)//棋子存在
            {
                preSeats->addChessToSeat(chess, preSeats->latestSeat);//放置备战席
                myPlayer->addChess(chess);//加入玩家队伍
                this->addChild(chess, 1);
                checkAndMerge(chess);//检查新增的这个是否能合成
            }
            store->chessIdHaveBought = -1;//重置
        }
    }
}

void PrepareScene::prepareSceneOnMouseMove(Event* event)
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

void PrepareScene::prepareSceneOnMouseUp(Event* event)
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
void PrepareScene::chessOnMouseDown(Vec2 mousePosition)
{

    //实现判断单击时是否有棋格或备战席
    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);
    //如果棋格存在且有棋子
    if (cell && cell->chessInGrid)
    {
        selectedChess = cell->chessInGrid;
        selectedChess->isDragging = true;

        gridMap->removeChessOfGrid(cell);//从棋格上移除
        myPlayer->removeChess(selectedChess);
    }
    //有备战席，且席位上存在棋子
    if (seat && seat->chessInSeat)
    {
        selectedChess = seat->chessInSeat;
        selectedChess->isDragging = true;

        preSeats->removeChessOfSeat(seat);//移除
        myPlayer->removeChess(selectedChess);

    }
}

//鼠标移动
void PrepareScene::chessOnMouseMove(Vec2 mousePosition)
{
    if (selectedChess)//有选中棋子
        if (selectedChess->isDragging)//棋子正在被拖动
        {
            //我方棋盘高亮
            for (auto iter : gridMap->nodeMap)
            {
                if (iter.second->isMine)
                    iter.second->turnToSeen();
            }
            //棋子跟随鼠标位置
            selectedChess->setPosition(mousePosition);
        }
}

//鼠标抬起
void PrepareScene::chessOnMouseUp(Vec2 mousePosition)
{
    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);
    //若有已经在被拖动的棋子
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;


        //此处判断鼠标位置所处棋格是否存在
        //1 有效但超出人口范围
        if (gridMap->chessAmount >= myPlayer->myStore->level && cell && !cell->chessInGrid) {
            createText("Level Is Not Enough");
            CCLOG("PrepareScene:swap failed");
            gridMap->addChessToGrid(selectedChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(selectedChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(selectedChess);
        }
        //2 棋格存在且位置上无棋子,将棋子放置在新的位置上
        else if (cell && !cell->chessInGrid && cell->isMine)
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
        //3 棋格存在且位置上有棋子
        else if (cell && cell->chessInGrid && cell->isMine)
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
            if (cell && !cell->chessInGrid && !cell->isMine)//在敌方棋盘放置
                createText("Cannot Put on the Opponent's Board");
            CCLOG("PrepareScene:swap failed");
            gridMap->addChessToGrid(selectedChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(selectedChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(selectedChess);

        }
        for (auto iter : gridMap->nodeMap)
        {
            if (iter.second->isMine)
                iter.second->turnToNormal();
        }
        selectedChess = nullptr;
    }

}

void PrepareScene::checkAndMerge(Chess* chess)
{
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

//进化原来是id和star的棋子
//棋子三合一进化，在第一个棋子的基础上进化，删除剩下两个棋子
//棋子可能出现在备战席和棋盘上
Chess* PrepareScene::upgradeChess(int id, int star)
{
    //upgradeChess用于保存第一个检测到的棋子，将基于他进化
    Chess* upgradeChess = nullptr;

    //逐个检查备战席上的棋子
    for (int i = 0; i < SEATS_NUM; i++)
    {
        if (preSeats->mySeats[i]->getId() == id && preSeats->mySeats[i]->getStar() == star)
        {
            auto chessRemove = preSeats->mySeats[i];//指向要删除的棋子
            //保留第一个棋子
            if (upgradeChess == nullptr) {
                upgradeChess = chessRemove;
                myPlayer->removeChess(chessRemove);//从玩家棋子中删除原星级的棋子
            }
            else {
                myPlayer->removeChess(chessRemove);//从玩家棋子中删除原星级的棋子
                preSeats->removeChessOfSeat(preSeats->getSeatAtPosition(chessRemove->atSeatPosition));//删除原星级的棋子的席位
                chessRemove->deleteChess();//把棋子删除
            }
        }
    }

    //逐个检查棋盘上的棋子
    //保存棋盘上所有这个id和star的棋子
    std::vector<Vec2> keysToRemove;
    for (auto pair : myPlayer->myChessMap)
    {
        if (pair.second->getId() == id && pair.second->getStar() == star)
        {
            keysToRemove.push_back(pair.first);
        }
    }
    //再依次处理同上
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

void PrepareScene::goToFightScene(float dt)
{
    // 创建新的场景
    auto fightScene = FightScene::create();
    //切换音乐
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("battleMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);

    // 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(fightScene);
}

void PrepareScene::menuPlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    //把原数据删除再离开场景
    PlayerManager::getInstance()->getPlayer(0)->deletePast();
    PlayerManager::getInstance()->getPlayer(1)->deletePast();

    Director::getInstance()->popScene(); // 切换到playscene场景
}

void PrepareScene::updateCountdownLabel(float dt) {
    //剩余时间的整数秒数
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
        //如果鼠标还在拖动棋子，棋子恢复原位
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
        goToFightScene(0);
    }
}
//输出随输入改变的提示，并在一段时间后自动移除
void PrepareScene::createText(const std::string& textContent)
{
    unschedule(CC_SCHEDULE_SELECTOR(PrepareScene::updateText));
    if (fadingText) {
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
    fadingText = Label::createWithTTF(textContent, "fonts/arial.ttf", 36);
    fadingText->setPosition(Vec2(600, 600));
    this->addChild(fadingText);

    elapsedTime = 0.0f;

    schedule(CC_SCHEDULE_SELECTOR(PrepareScene::updateText));


}

//createText的调度器用，使提示逐渐淡出
void PrepareScene::updateText(float dt)
{
    elapsedTime += dt;

    int opacity = 255 - static_cast<int>(elapsedTime * 200);

    fadingText->setOpacity(opacity);

    //完全透明后停止调度器
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(PrepareScene::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
}