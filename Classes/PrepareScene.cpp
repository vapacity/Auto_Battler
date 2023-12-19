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

    //��ȫ͸����ֹͣ������
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(PrepareScene::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
}

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

   
    //��ʼ��ССӢ��
    initLittleHero();

    //������������
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

//����
void PrepareScene::initLittleHero()
{
    littleHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    myPlayer->myHero = littleHero;
    this->addChild(myPlayer->myHero);    
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
    
    // ���������������¼�
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        
        CCLOG("PrepareScene:Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();
       
        /*�˲���Ϊ����ק���ӵ��ж�*/
        chessOnMouseDown(mousePosition);

        /*�˲���Ϊ�Ե��ͼƬ���ж�*/
        store->selectStore(event,mousePosition,preSeats->isFull());//store��������
        if (store->chessIdHaveBought != -1)
        {
            Chess* chess = ChessFactory::createChessById(store->chessIdHaveBought);
            if (chess)
            {
                //�������������Ƿ��ܺϳ�
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

//��갴��
void PrepareScene::chessOnMouseDown(Vec2 mousePosition)
{

    //ʵ���жϵ���ʱ�Ƿ��������������Ƿ��������
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

//����ƶ�
void PrepareScene::chessOnMouseMove(Vec2 mousePosition)
{
    if (selectedChess)
        if (selectedChess->isDragging)
        {
            selectedChess->setPosition(mousePosition);
        }
}

//���̧��
void PrepareScene::chessOnMouseUp(Vec2 mousePosition)
{
    HexCell* cell = gridMap->mouseInWhichCell(mousePosition);
    Seat* seat = preSeats->mouseInWhichSeat(mousePosition);
    //�����Ѿ��ڱ��϶�������
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
        //�˴��ж����λ����������Ƿ����
        //1 ��������λ����������,�����ӷ������µ�λ����
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
        //2 ��������λ����������
        else if (cell && cell->chessInGrid)
        {
            CCLOG("PrepareScene:swap Cell and Something");

            Chess* moveChess = cell->chessInGrid;
            //����λ���ϵ��������
            myPlayer->removeChess(moveChess);
            gridMap->removeChessOfGrid(cell);

            //����λ�ô���������ӵ�selectedChess��λ��
            gridMap->addChessToGrid(moveChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(moveChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(moveChess);        

            //��selectedChess��ӵ����λ����
            gridMap->addChessToGrid(selectedChess, cell);
            myPlayer->addChess(selectedChess);
        }
        else if (seat && seat->chessInSeat)
        {
            CCLOG("PrepareScene:swap Seat and Something");
            Chess* moveChess = seat->chessInSeat;
            //����λ���ϵ��������
            myPlayer->removeChess(seat->chessInSeat);
            preSeats->removeChessOfSeat(seat);

            //����λ�ô���������ӵ�selectedChess��λ��
            gridMap->addChessToGrid(moveChess, gridMap->getCellAtPosition(selectedChess->atGridPosition));
            preSeats->addChessToSeat(moveChess, preSeats->getSeatAtPosition(selectedChess->atSeatPosition));
            myPlayer->addChess(moveChess);
           
            //��selectedChess��ӵ����λ����
            preSeats->addChessToSeat(selectedChess, seat);
            myPlayer->addChess(selectedChess);
        }
        //4 ��������񣬵�λ���̵�
        else if (mousePosition.y <= store->storeAreaHeight)
        {
            CCLOG("PrepareScene: chess to be sold");                  
            myPlayer->myStore->money += selectedChess->price;
            selectedChess->deleteChess();

        }
        //������˻�ԭ��λ��
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
        //�˴���Ҫע�������������Ŀ��ܣ��õݹ���ʽ�������
        checkAndMerge(upgradeChess(chess->getId(), chess->getStar()));
    }
    else
    {
        return;
    }
}

Chess* PrepareScene::upgradeChess(int id,int star)
{
    //upgradeChess���ڱ����һ����⵽�����ӣ�������������
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
    //�ȱ����봫��ֵ��ͬ�������ϵ�����keyֵ
    std::vector<Vec2> keysToRemove;
    for (auto pair : myPlayer->myChessMap)
    {
        if (pair.second->getId() == id && pair.second->getStar() == star)
        {
            keysToRemove.push_back(pair.first);
        }
    }
    //�����δ���
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
    //����star�������ǽ�����star2����star3
    upgradeChess->upgrade();
    myPlayer->addChess(upgradeChess);
    return upgradeChess;
}


