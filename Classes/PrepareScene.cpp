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
    // 初始化背景
    initBackground();

    // 初始化棋格
    inithexGrid();
    // 初始化小小英雄
    initLittleHero();
    //棋子测试用例
    initChessExp();

    // 创建鼠标监听
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(PrepareScene::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(PrepareScene::onMouseMove, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(PrepareScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    return true;
}

void PrepareScene::inithexGrid()
{
    hexGrid = HexGrid::create(14, 8); // 假设您的棋盘有8行8列
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
    //正在测试同时出现两个
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

//用于服务onMouseMove的拆分函数，用于实现鼠标滑过棋格时的局部高亮
void PrepareScene::moveOnGrids(Vec2 mousePosition)
{
    //对棋格的高亮处理
    static HexCell* lastCell = nullptr;
    auto currentCell = hexGrid->getCellAt(mousePosition);

    if (currentCell != lastCell) {
        if (currentCell) {
            currentCell->changeOpacity(150); // 新的棋格增加透明度
        }
        if (lastCell) {
            lastCell->changeOpacity(80); // 前一个棋格恢复透明度
        }
        lastCell = currentCell;
    }
}

//用于服务onMouseMove的拆分函数,负责实现拖动棋子的中途位移
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
        // 处理鼠标左键按下事件
        CCLOG("Left mouse button clicked.");
        Vec2 mousePosition = mouseEvent->getLocationInView();

        //实现判断单击时是否有棋格，且棋格是否落在
        HexCell* cell = hexGrid->getCellAt(mousePosition);
        if (cell && cell->chess) {
            selectedChess = cell->chess;
            selectedChess->isDragging = true;
            cell->chess=nullptr;
        }

    }
    else if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        // 处理鼠标右键按下事件
        CCLOG("Right mouse button clicked.");
        // 移动精灵到点击位置
        //littleHero->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
        auto moveTo = MoveTo::create(1, Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
        littleHero->runAction(moveTo);
        littleHero->healthBar->setPercentage(25.0f);// test
    }
}

//监听鼠标移动事件
void PrepareScene::onMouseMove(Event* event)
{

    CCLOG("MousMove");
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    
    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();

    Vec2 location = Director::getInstance()->convertToGL(mousePosition);
    moveOnGrids(mousePosition);
    moveOnChess(mousePosition);

}

//监听键抬起
void PrepareScene::onMouseUp(Event* event)
{
    CCLOG("MouseUp");
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
    HexCell* cell = hexGrid->getCellAt(mousePosition);

    //是否有已经在被拖动的棋子
    if (selectedChess && selectedChess->isDragging)
    {
        selectedChess->isDragging = false;

        //此处判断鼠标位置所处棋格是否存在
        //1 存在且位置为空
        if (cell && !cell->chess) {
            cell->setChess(selectedChess);//设置新棋格上的棋子为被拖拽的棋子
            selectedChess = nullptr;//置空，安全
        }
        //2 存在且位置不为空
        else if (cell && cell->chess)
        {
            HexGrid::swapChessOnGrids(cell, hexGrid->getCellAt(selectedChess->initialPosition));//交换两个棋格上的棋子
            cell->setChess(selectedChess);//有不可抗力因素，交换后一个被拖拽棋子无法被控制（在MouseDown时那个棋格就失去了指向），凑活写了
        }
        //3 不存在
        else {
            HexCell* initialCell =hexGrid->getCellAt(selectedChess->initialPosition);//获取初始棋格
            initialCell->setChess(selectedChess);//回到初始棋格
        }

    }
        return;
    
}

void PrepareScene::createChessAtCell(HexCell* cell)
{

}
