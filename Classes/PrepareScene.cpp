// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
USING_NS_CC;

Scene* PrepareScene::createScene()
{
    // ����һ���������󣬸ö������Զ��ͷų��Զ��ͷ�
    auto scene = PrepareScene::create();
    return scene;
}
bool PrepareScene::init()
{
    // ���ȵ��û����init����
    if (!Scene::init())
    {
        return false;
    }

    // ���������ӳ�ʼ�������Ĵ���
    

    //��ӱ���ͼƬ
    initBackground();

    //������ʼ����
    initGridMap();


    //������սϯ
    initPreparationSeats();

    //�����̵�
    initStore();

    //��ʼ������
   // initChessExp();
   
    //��ʼ��ССӢ��
    initLittleHero();

    //������������
    this->enableMouseListener();
    gridMap->enableMouseListener();
    //store->enableMouseListener();
    
    /*if (store->buyCardId != -1)
    {
        Chess* chess = ChessFactory::createChessById(store->buyCardId);
        if (chess)
        {
            preSeats->addChessToSeat(chess, preSeats->latestSeat);
            this->addChild(chess, 1);
        }
    }*/

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
    gridMap = GridMap::create(); // ��������������8��8��
    this->addChild(gridMap, 0);
}

void PrepareScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create();
    this->addChild(preSeats);
}

void PrepareScene::initLittleHero()
{
    littleHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    this->addChild(littleHero);    
}

void PrepareScene::initChessExp()
{
    //���ڲ���ͬʱ��������
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
    store = StoreLayer::create();
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
    
    // ���������������¼�
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        
        CCLOG("PrepareScene:Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();
        
        /*�˲���Ϊ����ק���ӵ��ж�*/
        chessOnMouseDown(mousePosition);
        store->selectStore(event);
        if (store->buyCardId != -1)
        {
            Chess* chess = ChessFactory::createChessById(store->buyCardId);
            if (chess)
            {
                preSeats->addChessToSeat(chess, preSeats->latestSeat);
                this->addChild(chess, 1);
                store->buyCardId = -1;
            }
        }
    }
}

void PrepareScene::prepareSceneOnMouseMove(Event* event)
{
    //CCLOG("MousMove");
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();

    Vec2 location = Director::getInstance()->convertToGL(mousePosition);

    /*�˲���Ϊ����ק���ӵ��ж�*/
    chessOnMouseMove(mousePosition);
    return;
}

void PrepareScene::prepareSceneOnMouseUp(Event* event)
{
    CCLOG("MouseUp");
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();
    
    /*�˲���Ϊ����ק���ӵ��ж�*/
    chessOnMouseUp(mousePosition);
    return;

}

void PrepareScene::chessOnMouseDown(Vec2 mousePosition)
{

    //ʵ���жϵ���ʱ�Ƿ��������������Ƿ��������
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
    //�Ƿ����Ѿ��ڱ��϶�������
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;

        //�˴��ж����λ����������Ƿ����
        //1 ������λ��Ϊ��,�����ӷ������µ�λ����
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
        //2 ������λ�ò�Ϊ��
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
        //4 ��������񣬵�λ���̵�
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


