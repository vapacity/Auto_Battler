// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
#include "Chess.h"
#include "HexCell.h"
#include "HexGrid.h"
#include "Charmander.h"
#include "Squirtle.h"

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
    // ��ʼ������
    initBackground();

    // ��ʼ�����
    inithexGrid();
    // ��ʼ��ССӢ��
    initLittleHero();
    //���Ӳ�������
    initChessExp();

    // ����������
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(PrepareScene::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(PrepareScene::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(PrepareScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    return true;
}

void PrepareScene::inithexGrid()
{
    hexGrid = HexGrid::create(14, 8); // ��������������8��8��
    this->addChild(hexGrid, 0);
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

void PrepareScene::initLittleHero()
{
    littleHero = LittleHero::create("gala.png");
    littleHero->setContentSize(Size(150, 150));
    littleHero->setPosition(Vec2(50, 300));
    this->addChild(littleHero);
}

void PrepareScene::initChessExp()
{
    //���ڲ���ͬʱ��������
    auto charmander=Charmander::create("charmander1-back-left.png");
    if (charmander) {
        charmander->setScale(0.15);
        chessSet.push_back(charmander);

        auto cell = hexGrid->getCellAt(Vec2(300, 210));

        cell->setChess(charmander);

        this->addChild(charmander,1);
    }

    auto squirtle = Squirtle::create("squirtle1-back-left.png");
    if (squirtle) {
        squirtle->setScale(0.15);
        chessSet.push_back(squirtle);
        auto cell = hexGrid->getCellAt(Vec2(600, 210));
       
        cell->setChess(squirtle);

        this->addChild(squirtle, 1);
    }
    
}

//���ڷ���onMouseMove�Ĳ�ֺ���������ʵ����껬�����ʱ�ľֲ�����
void PrepareScene::moveOnGrids(Vec2 mousePosition)
{
    //�����ĸ�������
    static HexCell* lastCell = nullptr;
    auto currentCell = hexGrid->getCellAt(mousePosition);

    if (currentCell != lastCell) {
        if (currentCell) {
            currentCell->changeOpacity(150); // �µ��������͸����
        }
        if (lastCell) {
            lastCell->changeOpacity(80); // ǰһ�����ָ�͸����
        }
        lastCell = currentCell;
    }
}

//���ڷ���onMouseMove�Ĳ�ֺ���,����ʵ���϶����ӵ���;λ��
void PrepareScene::moveOnChess(Vec2 mousePosition)
{
    if (selectedChess)
        if (selectedChess->isDragging)
        {
            selectedChess->setPosition(mousePosition);
        }

}

void PrepareScene::onMouseDown(Event* event)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        // ���������������¼�
        CCLOG("Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();

        //ʵ���жϵ���ʱ�Ƿ������������Ƿ�����
        HexCell* cell = hexGrid->getCellAt(mousePosition);
        if (cell && cell->chess) {
            selectedChess = cell->chess;
            selectedChess->isDragging = true;
            cell->chess=nullptr;
        }

    }
    else if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        // ��������Ҽ������¼�
        CCLOG("Right mouse button clicked.");
        // �ƶ����鵽���λ��
        //littleHero->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
        auto moveTo = MoveTo::create(1, Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
        littleHero->runAction(moveTo);
        littleHero->healthBar->setPercentage(25.0f);// test
    }
}

//��������ƶ��¼�
void PrepareScene::onMouseMove(Event* event)
{

    CCLOG("MousMove");
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    
    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();

    Vec2 location = Director::getInstance()->convertToGL(mousePosition);
    moveOnGrids(mousePosition);
    moveOnChess(mousePosition);

}

//������̧��
void PrepareScene::onMouseUp(Event* event)
{
    CCLOG("MouseUp");
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();
    HexCell* cell = hexGrid->getCellAt(mousePosition);

    //�Ƿ����Ѿ��ڱ��϶�������
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;

        //�˴��ж����λ����������Ƿ����
        //1 ������λ��Ϊ��
        if (cell && !cell->chess) {
            cell->setChess(selectedChess);//����������ϵ�����Ϊ����ק������
            selectedChess = nullptr;//�ÿգ���ȫ
        }
        //2 ������λ�ò�Ϊ��
        else if (cell && cell->chess)
        {
            HexGrid::swapChessOnGrids(cell, hexGrid->getCellAt(selectedChess->initialPosition));//������������ϵ�����
            cell->setChess(selectedChess);//�в��ɿ������أ�������һ������ק�����޷������ƣ���MouseDownʱ�Ǹ�����ʧȥ��ָ�򣩣��ջ�д��
        }
        //3 ������
        else {
            HexCell* initialCell =hexGrid->getCellAt(selectedChess->initialPosition);//��ȡ��ʼ���
            initialCell->setChess(selectedChess);//�ص���ʼ���
        }

    }
        return;
    
}

void PrepareScene::createChessAtCell(HexCell* cell)
{

}
