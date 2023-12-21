// PrepareScene.cpp
#include "cocos2d.h"
#include "PrepareScene.h"
#include "HexGrid.h"
#include "sword.h"
#include "BlueBar.h"
#include "HelloWorldScene.h"
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
    littleHero = LittleHero::create();
    //littleHero->setContentSize(Size(200,200));
    littleHero->setPosition(Vec2(1000, 300));
    this->addChild(littleHero);
    enemy = LittleHero::create();
    enemy->setEnemy();
    enemy->setScale(0.5);
    //enemy->setContentSize(Size(150, 150));
    enemy->setPosition(Vec2(1000, 600));
    this->addChild(enemy); 
    littleHero->attack(enemy);
    /*auto blueBar = BlueBar::create();
    this->addChild(blueBar);*/
    this->initClock();
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

void PrepareScene::initClock()
{
    auto sprite = Sprite::create("Timer.png");
    Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto label = cocos2d::Label::createWithTTF(std::to_string(countdownSeconds), "fonts/Arial.ttf", 24);
    label->setColor(Color3B::RED);
    Size labelSize = label->getContentSize();
    Size spriteSize = sprite->getContentSize();
    sprite->setPosition(0 + spriteSize.width / 2, visibleSize.height - spriteSize.height / 2);
    this->addChild(sprite);
    label->setPosition(0+ spriteSize.width +labelSize.width/2,visibleSize.height-spriteSize.height/2);
    this->addChild(label);
    this->schedule([=](float dt) {
        countdownSeconds--;
        // ���µ���ʱ��ʾ
        if (label) {
            label->setString(std::to_string(countdownSeconds));
        }

        // �������ʱ�������л�����һ������
        if (countdownSeconds <= 0) {
           this->unschedule("updateCountdown");
           this->scheduleOnce([=](float dt) {
                this->switchToNextScene(dt);
                }, 0.5f, "switchScene");
        }
    }, 1.0f, "updateCountdown");
}

void PrepareScene::switchToNextScene(float dt)
{
}

void PrepareScene::onMouseDown(Event* event)
{
    EventMouse* e = (EventMouse*)event;

    // �ж��Ƿ����Ҽ����
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
    {
        //// �ƶ����鵽���λ��
        //auto currentTime = std::chrono::high_resolution_clock::now();
        //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastRightClickTime);
        //lastRightClickTime = currentTime;
        //// ���������ʱ��С��һ����ֵ������Դ˴ε��
        //if (elapsed.count() < doubleClickThreshold)
        //{
        //    return;
        //}
        littleHero->attack(enemy);
    }
}

