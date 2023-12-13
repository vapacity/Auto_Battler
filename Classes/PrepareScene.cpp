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
    initChessExp();
   

    //����PrepareScene������
    prepareSceneMouseListener = EventListenerMouse::create();
    prepareSceneMouseListener->onMouseDown = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseDown, this);
    prepareSceneMouseListener->onMouseMove = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseMove, this);
    prepareSceneMouseListener->onMouseUp = CC_CALLBACK_1(PrepareScene::prepareSceneOnMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(prepareSceneMouseListener, this);
    return true;

    //�����������õģ��������ѡ�����ļ�����
    this->enableMouseListener();
    gridMap->enableMouseListener();
    store->enableMouseListener();



    return true;
}


//��ӱ���ͼƬ
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

void PrepareScene::initChessExp()
{
    //���ڲ���ͬʱ��������
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
        // ���������������¼�
        CCLOG("Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();
        
        /*----------------------*/
        /*�˲���Ϊ����ק���ӵ��ж�*/
        /*----------------------*/
        //ʵ���жϵ���ʱ�Ƿ��������������Ƿ��������
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
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();

    Vec2 location = Director::getInstance()->convertToGL(mousePosition);

    /*----------------------*/
    /*�˲���Ϊ����ק���ӵ��ж�*/
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
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();
    /*----------------------*/
    /*�˲���Ϊ����ק���ӵ��ж�*/
    /*----------------------*/

    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);
    //�Ƿ����Ѿ��ڱ��϶�������
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;

        //�˴��ж����λ����������Ƿ����
        //1 ������λ��Ϊ��
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
        //2 ������λ�ò�Ϊ��
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
        //3 ������
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



