// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
#include "HexGrid.h"
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

    // ����������
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(PrepareScene::onMouseMove, this);
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

void PrepareScene::onMouseMove(Event* event)
{
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();
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
