// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
USING_NS_CC;

Scene* PrepareScene::createScene(Player* player)
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = PrepareScene::create(player);

    return scene;
}

PrepareScene* PrepareScene::create(Player* player)
{
    PrepareScene* scene = new PrepareScene();
    if (scene && scene->init(player)) {
        // 如果初始化成功，autorelease 以确保在不再需要时释放内存
        scene->autorelease();
        return scene;
    }
    else {
        // 如果初始化失败，释放内存并返回 nullptr
        delete scene;
        return nullptr;
    }
}

bool PrepareScene::init(Player* player)
{
    // 首先调用基类的init方法
    if (!Scene::init())
    {
        return false;
    }

    // 这里可以添加初始化场景的代码
    
    //初始化玩家属性
    initPlayer(player);
    //player->retain();

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
}//init一结束，player就变0了？

void PrepareScene::initPlayer(Player* player)
{
    myPlayer = player;
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

void PrepareScene::initLittleHero()
{
    littleHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    this->addChild(littleHero);    
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
    store = Store::create(myPlayer->playerStore);
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
        store->selectStore(event, preSeats->isFull());//store监听函数,备战席未满则可以添加
           

        //根据buyCardId判断买到的棋子id
        if (store->chessIdHaveBought != -1)
        {
            Chess* chess = ChessFactory::createChessById(store->chessIdHaveBought);
            if (chess)
            {
                preSeats->addChessToSeat(chess, preSeats->latestSeat);
                this->addChild(chess, 1);
            }
            store->chessIdHaveBought = -1;
        }
    }
}

void PrepareScene::prepareSceneOnMouseMove(Event* event)
{
    //if (myPlayer)
    //    log("%d\n", myPlayer->playerStore->money);
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

void PrepareScene::chessOnMouseDown(Vec2 mousePosition)
{

    //实现判断单击时是否有棋格，且棋格上是否存在棋子
    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);

    if (cell && cell->chessInGrid)
    {
        selectedChess = cell->chessInGrid;
        selectedChess->atCell = cell;
        selectedChess->isDragging = true;
        cell->chessInGrid = nullptr;

    }
    if (seat && seat->chessInSeat)
    {
        selectedChess = seat->chessInSeat;
        selectedChess->atSeat = seat;
        selectedChess->isDragging = true;
        preSeats->removeChessOfSeat(seat);

    }
}

void PrepareScene::chessOnMouseMove(Vec2 mousePosition)
{
    if (selectedChess)
        if (selectedChess->isDragging)
        {
            selectedChess->setPosition(mousePosition);
        }
}

void PrepareScene::chessOnMouseUp(Vec2 mousePosition)
{
    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);
    //若有已经在被拖动的棋子
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;

        //此处判断鼠标位置所处棋格是否存在
        //1 存在且位置为空,将棋子放置在新的位置上
        if (cell && !cell->chessInGrid)
        {
            CCLOG("PrepareScene:put Chess on Grid");
            gridMap->addChessToGrid(selectedChess, cell);
        }
        else if (seat && !seat->chessInSeat)
        {
            CCLOG("PrepareScene:put Chess on Seat");
            preSeats->addChessToSeat(selectedChess, seat);
        }
        //2 存在且位置不为空
        else if (cell && cell->chessInGrid)
        {
            CCLOG("PrepareScene:swap Cell and Something");

            gridMap->addChessToGrid(cell->chessInGrid, selectedChess->atCell);
            preSeats->addChessToSeat(cell->chessInGrid, selectedChess->atSeat);

            gridMap->addChessToGrid(selectedChess, cell);
        }
        else if (seat && seat->chessInSeat)
        {
            CCLOG("PrepareScene:swap Seat and Something");

            gridMap->addChessToGrid(seat->chessInSeat, selectedChess->atCell);
            preSeats->addChessToSeat(seat->chessInSeat, selectedChess->atSeat);

            preSeats->addChessToSeat(selectedChess, seat);
        }
        //4 不存在棋格，但位于商店
        else if (mousePosition.y <= store->storeAreaHeight)
        {
            CCLOG("PrepareScene: chess to be sold");
            gridMap->removeChessOfGrid(selectedChess->atCell);
            preSeats->removeChessOfSeat(selectedChess->atSeat);
            //Player->money+=selectedChess->price;
            selectedChess->removeFromParentAndCleanup(1);

        }
        else
        {
            CCLOG("PrepareScene:swap failed");
            gridMap->addChessToGrid(selectedChess, selectedChess->atCell);
            preSeats->addChessToSeat(selectedChess, selectedChess->atSeat);
        }
        selectedChess = nullptr;
    }

}


