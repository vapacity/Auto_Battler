// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
USING_NS_CC;

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

    //初始化棋子
    initChessExp();
   

    //启用PrepareScene鼠标监听
    prepareSceneMouseListener = EventListenerMouse::create();
    prepareSceneMouseListener->onMouseDown = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseDown, this);
    prepareSceneMouseListener->onMouseMove = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseMove, this);
    prepareSceneMouseListener->onMouseUp = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(prepareSceneMouseListener, this);
    return true;

    //启用棋盘内置的，监听鼠标选择棋格的监听器
    this->enableMouseListener();
    gridMap->enableMouseListener();
    store->enableMouseListener();



    return true;
}


//添加背景图片
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
    gridMap = GridMap::create(); // 假设您的棋盘有8行8列
    this->addChild(gridMap, 0);
}

void PrepareScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create();
    this->addChild(preSeats);
}

void PrepareScene::initChessExp()
{
    //正在测试同时出现三个
    auto charmander = ChessFactory::createChessById(0);
    if (charmander) {
        charmander->setScale(0.15);

        preSeats->addChessToSeat(charmander, preSeats->latestSeat);

        this->addChild(charmander, 1);
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
    store = storeLayer::create();
    this->addChild(store,2);
}

void PrepareScene::enableMouseListener()
{
    prepareSceneMouseListener->setEnabled(true);
}

void PrepareScene::disableMouseListener()
{
    prepareSceneMouseListener->setEnabled(false);
}


void PrepareScene::prepareSceneOnMouseDown(Event* event)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        // 处理鼠标左键按下事件
        CCLOG("Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();
        
        /*----------------------*/
        /*此部分为对拖拽棋子的判断*/
        /*----------------------*/
        //实现判断单击时是否有棋格，且棋格上是否存在棋子
        HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
        Seat* seat = preSeats->mouseInWhichSeat(mousePosition);

        if (cell && cell->chessInGrid)
        {
            selectedChess = cell->chessInGrid;
            selectedChess->initialCell = cell;
            selectedChess->isDragging = true;
            cell->chessInGrid = nullptr;
        }
        if (seat && seat->chessInSeat)
        {
            selectedChess = seat->chessInSeat;
            selectedChess->initialSeat = seat;
            selectedChess->isDragging = true;
            seat->chessInSeat = nullptr;
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

    /*----------------------*/
    /*此部分为对拖拽棋子的判断*/
    /*----------------------*/
    if (selectedChess)
        if (selectedChess->isDragging)
        {
            selectedChess->setPosition(mousePosition);
        }
}

void PrepareScene::prepareSceneOnMouseUp(Event* event)
{
    CCLOG("MouseUp");
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    /*----------------------*/
    /*此部分为对拖拽棋子的判断*/
    /*----------------------*/

    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);
    //是否有已经在被拖动的棋子
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;

        //此处判断鼠标位置所处棋格是否存在
        //1 存在且位置为空
        if (cell && !cell->chessInGrid)
        {
            CCLOG("swap Cell and Nothing");
            gridMap->addChessToGrid(selectedChess, cell);
        }
        else if (seat && !seat->chessInSeat)
        {
            CCLOG("swap Seat and Nothing");
            preSeats->addChessToSeat(selectedChess, seat);
        }
        //2 存在且位置不为空
        else if (cell && cell->chessInGrid)
        {
            CCLOG("swap Cell and Something");
            auto res = selectedChess;
            gridMap->addChessToGrid(cell->chessInGrid, selectedChess->initialCell);
            preSeats->addChessToSeat(cell->chessInGrid, selectedChess->initialSeat);

            gridMap->addChessToGrid(selectedChess, cell);
        }
        else if (seat && seat->chessInSeat)
        {            
            CCLOG("swap Seat and Something");
            auto res = selectedChess;
            gridMap->addChessToGrid(seat->chessInSeat, selectedChess->initialCell);
            preSeats->addChessToSeat(seat->chessInSeat, selectedChess->initialSeat);

            preSeats->addChessToSeat(selectedChess, seat);
        }
        //3 不存在
        else 
        {
            CCLOG("swap failed");
            gridMap->addChessToGrid(selectedChess, selectedChess->initialCell);
            preSeats->addChessToSeat(selectedChess, selectedChess->initialSeat);
        }
        if(selectedChess->initialCell)
            selectedChess->initialCell = nullptr;
        if(selectedChess->initialSeat)
            selectedChess->initialSeat = nullptr;
        selectedChess = nullptr;

    }
    return;

}



