// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
USING_NS_CC;
#define PREPARE_TIME 5.0f
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


    Vector<MenuItem*> MenuItems_fight;
    //����
    auto backItem = MenuItemImage::create(
        "smallbacknormal.png",
        "smallbackselected.png",
        CC_CALLBACK_1(PrepareScene::menuPlayCallback, this));

    if (!(backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0))
    {//�˳��˵�����Ч��������������˳��˵����λ��
        // ��ȡ�����ĳߴ����������
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        float x = origin.x + visibleSize.width * 17 / 18;
        float y = origin.y + visibleSize.height * 14 / 15;
        backItem->setPosition(Vec2(x, y));
    }
    MenuItems_fight.pushBack(backItem);
    auto menu = Menu::createWithArray(MenuItems_fight);//�����˵�
    menu->setPosition(Vec2::ZERO);//���˵���λ������Ϊ(0, 0)�������½�
    this->addChild(menu, 2);//���˵���ӵ���ǰ��ͼ���У��㼶����Ϊ1����ʾ���˵�������ͼ������Ϸ�
    // ���������ӳ�ʼ�������Ĵ���
    ///////////////////////////////////////////////////////////

    initPlayer();

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

    //��ʼ������ʱ
    initPrepareLabel();

    //���������ú�����һ��ע�͵�
    //initChessExp();

    //������������
    this->enableMouseListener();
    gridMap->enableMouseListener();
    //�˴�ΪѰ·����
    /*Vector<HexCell*> path;
    HexCell* toNode=nullptr;
    gridMap->getCellAtPosition(Vec2(1, 1))->chessInGrid->moveTo(gridMap->FindBattle(gridMap->getCellAtPosition(Vec2(1, 1))->chessInGrid, gridMap->getCellAtPosition(Vec2(1, 1)))->getPosition());*/
    
    this->schedule(schedule_selector(PrepareScene::updateCountdownLabel), 0.01f);  // ÿ��1�����һ��Label

    return true;
}

void PrepareScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
    enemyPlayer->ai();
    myPlayer->myStore->money += myPlayer->myStore->interest + INIT_ADD_FOR_TURN;
}
void PrepareScene::initBackground()
{
    backgroundImg = Sprite::create("battle-background3.png");
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

//����
void PrepareScene::initLittleHero()
{
    //littleHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    littleHero = myPlayer->myHero;
    if (littleHero->getParent())
        littleHero->removeFromParent();
    this->addChild(myPlayer->myHero, 1);
}

void PrepareScene::initChessExp()
{
    ////���ڲ���ͬʱ��������
    //auto Yevee = ChessFactory::createChessById(0);
    //if (Yevee) {
    //    Yevee->setScale(0.15);

    //    gridMap->addChessToGrid(Yevee, gridMap->getCellAtPosition(Vec2(1, 1)));
    //    myPlayer->addChess(Yevee);
    //    Yevee->playerNumber = 1;
    //    this->addChild(Yevee, 1);
    //}

    //auto charmander = ChessFactory::createChessById(1);
    //if (charmander) {
    //    charmander->setScale(0.15);
    //    gridMap->addChessToGrid(charmander, gridMap->getCellAtPosition(Vec2(4, 4)));
    //    myPlayer->addChess(charmander);
    //    charmander->playerNumber = 2;
    //    this->addChild(charmander, 1);
    //}

}

void PrepareScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void PrepareScene::initPrepareLabel()
{
    // ��ʼ���߶�
    countdownLine = DrawNode::create();
    countdownLine->setAnchorPoint(Vec2(0, 0.5));
    countdownLine->setPosition(Vec2(0, 100));
    this->addChild(countdownLine);
    // ��ʼ��Label
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
        a.second->setOpacity(255);
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

    // ���������������¼�
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {

        CCLOG("PrepareScene:Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();

        /*�˲���Ϊ����ק���ӵ��ж�*/
        chessOnMouseDown(mousePosition);

        /*�˲���Ϊ�Ե��ͼƬ���ж�*/
        store->selectStore(event, mousePosition, preSeats->isFull());//store��������
        if (store->chessIdHaveBought != -1)
        {
            Chess* chess = ChessFactory::createChessById(store->chessIdHaveBought);
            chess->maxHP = chess->health;
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
        //2 ��������λ����������
        else if (cell && cell->chessInGrid && cell->isMine)
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

void PrepareScene::checkAndMerge(Chess* chess)
{
    int chessId = chess->getId();
    if (myPlayer->chessCount[std::make_pair(chess->getId(), chess->getStar())] >= 3)
    {
        //�˴���Ҫע�������������Ŀ��ܣ��õݹ���ʽ�������
        checkAndMerge(upgradeChess(chess->getId(), chess->getStar()));
    }
    else
    {
        return;
    }
}

Chess* PrepareScene::upgradeChess(int id, int star)
{
    //upgradeChess���ڱ����һ����⵽�����ӣ�������������
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

void PrepareScene::goToFightScene(float dt)
{
    // �����µĳ���
    auto fightScene = FightScene::create();

    // �л����³���
    cocos2d::Director::getInstance()->replaceScene(fightScene);
}

void PrepareScene::menuPlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }
    //��ԭ����ɾ�����뿪����
    PlayerManager::getInstance()->getPlayer(0)->deletePast();
    PlayerManager::getInstance()->getPlayer(1)->deletePast();

    Director::getInstance()->popScene(); // �л���playscene����
}

void PrepareScene::updateCountdownLabel(float dt) {
    remainingTime -= dt;
    int seconds = static_cast<int>(remainingTime) + 1;

    // �����߶γ��ȱ���
    float lengthRatio = remainingTime / PREPARE_TIME;

    // �����߶εĿ�ȣ����Ը�����Ҫ����
    float lineWidth = 30.0f;

    // �����߶εĳ���
    countdownLine->clear();

    countdownLine->drawLine(Vec2(300, 600), Vec2(300 + 700 * lengthRatio, 600), Color4F::WHITE);
    countdownLine->setLineWidth(lineWidth);

    // ����Label���ı�
    countdownLabel->setString(StringUtils::format("%d", seconds));

    // ���ʱ�䵽����ת����һ������
    if (remainingTime <= 0) {
        goToFightScene(0); // ����Ĳ������Ը��������Ҫ����
    }
}
