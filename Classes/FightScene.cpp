#include "FightScene.h"

cocos2d::Scene* FightScene::createScene()
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = FightScene::create();
    return scene;
}

bool FightScene::init()
{
    // 首先调用基类的init方法
    if (!Scene::init())
    {
        return false;
    }
    initBackground();
    initGridMap();
    initPreparationSeats();
    initLittleHero();
    initStore();
}

void FightScene::initBackground()
{
    backgroundImg = Sprite::create("battle-background2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backgroundImg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundImg->setScaleX(visibleSize.width / backgroundImg->getContentSize().width);
    backgroundImg->setScaleY(visibleSize.height / backgroundImg->getContentSize().height);
    this->addChild(backgroundImg, -1);
}

void FightScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    //此处需要一个导入地方棋盘的操作！！
    this->addChild(gridMap, 0);

    for (auto iter : gridMap->myChessMap)
    {
        iter.second->removeFromParent();
        this->addChild(iter.second, 1);
    }
}

void FightScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    this->addChild(preSeats);
}

void FightScene::initLittleHero()
{
    myLittleHero = myPlayer->myHero;

    //this->addChild(myLittleHero);
    //enemyLittleHero = enemyPlayer->myHero;
    //this->addChild(enemyLittleHero);
}

void FightScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void FightScene::moveChess(Chess* chessToMove)
{

}
