#include"cocos2d.h"
#include "StartScene.h"
#include "GameOverScene.h"

cocos2d::Scene* GameOverScene::createScene()
{
    // ����һ���������󣬸ö������Զ��ͷų��Զ��ͷ�
    auto scene = GameOverScene::create();
    return scene;
}
bool GameOverScene::init()
{ 
    // ���ȵ��û����init����
    if (!Scene::init())
    {
        return false;
    }

    auto label = Label::createWithTTF("GameOver", "fonts/Marker Felt.ttf", 80); // �����ļ���Ҫ����

    // ����Label����ɫ����ѡ��
    label->setColor(Color3B::WHITE);

    // ��ȡ�����ĳߴ����������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    // ����Label��λ��
    label->setPosition(centerPosition);

    // ��Label��ӵ���ǰ����
    this->addChild(label, 2); // �ڶ���������z-order�����Ը�����Ҫ����
    auto delay = cocos2d::DelayTime::create(2);

    // ����һ���ص�����������ִ����Ҫ�ȴ��Ĳ���
    auto callback = cocos2d::CallFunc::create([this]() {
        myPlayer->deletePlayer();
        enemyPlayer->deletePlayer();
        GameOverScene::goToStartScene();
        });

    // ����һ��˳�������ȵȴ���Ȼ��ִ�лص�����
    auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);

    // ���ж���
    this->runAction(sequence);
    return true;
}

void GameOverScene::goToStartScene()
{
    // �����µĳ���
    auto startScene = StartScene::createScene();

    // �л����³���
    cocos2d::Director::getInstance()->replaceScene(startScene);
}
