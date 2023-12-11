// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
#include "HexGrid.h"
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
    littleHero = LittleHero::create("gala.png");
    littleHero->setContentSize(Size(150, 150));
    littleHero->setPosition(Vec2(50, 300));
    this->addChild(littleHero);
    // 创建鼠标监听
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(PrepareScene::onMouseDown, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(PrepareScene::onMouseMove, this);
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

void PrepareScene::onMouseMove(Event* event)
{
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // 获取鼠标位置
    Vec2 mousePosition = mouseEvent->getLocationInView();
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

void PrepareScene::onMouseDown(Event* event)
{
    EventMouse* e = (EventMouse*)event;

    // 判断是否是右键点击
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        // 移动精灵到点击位置
        //littleHero->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
        auto moveTo = MoveTo::create(1, Vec2(e->getCursorX(), e->getCursorY()));
        littleHero->runAction(moveTo);
        littleHero->healthBar->setPercentage(25.0f);// test
    }
}

