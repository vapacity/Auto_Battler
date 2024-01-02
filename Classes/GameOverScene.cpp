#include"cocos2d.h"
#include "StartScene.h"
#include "GameOverScene.h"

cocos2d::Scene* GameOverScene::createScene()
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = GameOverScene::create();
    return scene;
}
bool GameOverScene::init() 
{ 
    // 首先调用基类的init方法
    if (!Scene::init())
    {
        return false;
    }
    //音效
    cocos2d::experimental::AudioEngine::play2d("youwinEffect.mp3", false);

    auto label = Label::createWithTTF("GameOver", "fonts/Marker Felt.ttf", 80); // 字体文件需要存在

    // 设置Label的颜色（可选）
    label->setColor(Color3B::WHITE);

    // 获取场景的尺寸和中心坐标
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    // 设置Label的位置
    label->setPosition(centerPosition);

    // 将Label添加到当前场景
    this->addChild(label, 2); // 第二个参数是z-order，可以根据需要调整
    auto delay = cocos2d::DelayTime::create(2);

    // 创建一个回调动作，用于执行需要等待的操作
    auto callback = cocos2d::CallFunc::create([this]() {
        myPlayer->deletePast();
        enemyPlayer->deletePast();
        GameOverScene::goToStartScene();
        });

    // 创建一个顺序动作，先等待，然后执行回调操作
    auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);

    // 运行动作
    this->runAction(sequence);
    return true;
}

void GameOverScene::goToStartScene()
{
    // 创建新的场景
    auto startScene = StartScene::createScene();

    // 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(startScene);
}
