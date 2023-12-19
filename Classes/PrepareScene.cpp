// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
USING_NS_CC;

void PrepareScene::noPopulationText()
{
    unschedule(CC_SCHEDULE_SELECTOR(PrepareScene::updateText));
    if (fadingText) {
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
    fadingText = Label::createWithTTF("Level Is Not Enough", "fonts/arial.ttf", 36);
    fadingText->setPosition(Vec2(600, 600));
    this->addChild(fadingText);

    elapsedTime = 0.0f;

    schedule(CC_SCHEDULE_SELECTOR(PrepareScene::updateText));
}

void PrepareScene::updateText(float dt)
{
    elapsedTime += dt;

    int opacity = 255 - static_cast<int>(elapsedTime * 150);

    fadingText->setOpacity(opacity);

    //完全透明后停止调度器
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(PrepareScene::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
}

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

    // 这里可以添加初始化场景的代码
    

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

    //启用鼠标监听器
    this->enableMouseListener();
    gridMap->enableMouseListener();


    return true;
}


void PrepareScene::initBackground()
{
    backgroundImg=Sprite::create("battle-background3.png");
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
}

void PrepareScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    this->addChild(preSeats);
}

//待改
void PrepareScene::initLittleHero()
{
    littleHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    myPlayer->myHero = littleHero;
    this->addChild(myPlayer->myHero);    
}

void PrepareScene::initChessExp()
{
    //正在测试同时出现三个
    auto charmander1 = ChessFactory::createChessById(0);
    if (charmander1) {
        charmander1->setScale(0.15);

        preSeats->addChessToSeat(charmander1, preSeats->latestSeat);

        this->addChild(charmander1, 1);
    }

    auto charmander2 = ChessFactory::createChessById(1);
    if (charmander2) {
        charmander2->setScale(0.15);
        preSeats->addChessToSeat(charmander2, preSeats->latestSeat);

        this->addChild(charmander2, 1);
    }

    auto charmander3 = ChessFactory::createChessById(2);
    if (charmander3) {
        charmander3->setScale(0.15);
            preSeats->addChessToSeat(charmander3, preSeats->latestSeat);

        this->addChild(charmander3, 1);
    }

}

void PrepareScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store,2);
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

        /*此部分为对点击图片的判断*/
        store->selectStore(event,mousePosition,preSeats->isFull());//store监听函数
        if (store->chessIdHaveBought != -1)
        {
            Chess* chess = ChessFactory::createChessById(store->chessIdHaveBought);
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
void PrepareScene::chessOnMouseMove(Vec2 mousePosition)
{
    if (selectedChess)
        if (selectedChess->isDragging)
        {
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



        if (gridMap->chessAmount >= myPlayer->myStore->level && cell && !cell->chessInGrid) {
            noPopulationText();
            CCLOG("PrepareScene:swap failed");
            gridMap->addChessToGrid(selectedChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(selectedChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));

            myPlayer->addChess(selectedChess);
        }
        //此处判断鼠标位置所处棋格是否存在
        //1 棋格存在且位置上无棋子,将棋子放置在新的位置上
        else if (cell && !cell->chessInGrid)
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
        else if (cell && cell->chessInGrid)
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
        selectedChess = nullptr;
    }

}

void PrepareScene::checkAndMerge(Chess*chess)
{
    int chessId = chess->getId();
    if (myPlayer->chessCount[std::make_pair(chess->getId(), chess->getStar()) ]>= 3)
    {
        //此处需要注意有连续进化的可能，用递归形式容易理解
        checkAndMerge(upgradeChess(chess->getId(), chess->getStar()));
    }
    else
    {
        return;
    }
}

Chess* PrepareScene::upgradeChess(int id,int star)
{
    //upgradeChess用于保存第一个检测到的棋子，将基于他进化
    Chess* upgradeChess=nullptr;
    for (int i = 0; i < SEATS_NUM; i++)
    {
        if (preSeats->mySeats[i]->getId() == id && preSeats->mySeats[i]->getStar()==star)
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
    upgradeChess->upgrade();
    myPlayer->addChess(upgradeChess);
    return upgradeChess;
}


