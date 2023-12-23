/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "StartScene.h"


USING_NS_CC;
class PlayMenu;
Scene* StartScene::createScene()
{
    return StartScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
//��һ�д�����Ϣ��ӡ���ļ���
//�ڶ��д�����Ϣ��ʾ�û�����������"Resources/"ǰ׺���޸�����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance    StartScene�����ĳ�ʼ��
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first��ʼ��Scene���࣬�����ʼ��ʧ���򷵻�false
    if (!Scene::init())
    {
        return false;
    }
    //ͨ������Director::getInstance()��ȡDirector���ʵ��
    //Ȼ��ʹ��getVisibleSize()������ȡ�ɼ����ڵĳߴ�
    //visibleSize��������ֵΪһ��Size���󣬸ö�������˿�Ⱥ͸߶���Ϣ
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //����getVisibleOrigin()������ȡ�ɼ����ڵ�ԭ��λ�ã����½ǣ�
    //origin��������ֵΪһ��Vec2���󣬸ö��������ԭ���x��y����
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //���ֿ�ʼ����
    AudioManager::preloadBackgroundMusic();
    AudioManager::playBackgroundMusic();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to do something about the program
    //    you may modify it.

    Vector<MenuItem*> MenuItems;

    //��ʼ��Ϸ
    auto playItem = MenuItemImage::create(
        "playnormal.png",
        "playselected.png",
        CC_CALLBACK_1(StartScene::menuStartCallback, this));

    if (playItem == nullptr ||
        playItem->getContentSize().width <= 0 ||
        playItem->getContentSize().height <= 0)
    {//����ʼ�˵�����Ч������problemLoading()������ӡ������Ϣ
        problemLoading("'playnormal.png' and 'playselected.png'");
    }
    else
    {//��ʼ�˵�����Ч������������㿪ʼ�˵����λ��
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2 + playItem->getContentSize().height;
        playItem->setPosition(Vec2(x, y));
    }
    MenuItems.pushBack(playItem);

    //����
    auto setItem = MenuItemImage::create(
        "setnormal.png",
        "setselected.png",
        CC_CALLBACK_1(StartScene::menuSetCallback, this));

    if (setItem == nullptr ||
        setItem->getContentSize().width <= 0 ||
        setItem->getContentSize().height <= 0)
    {//�����ò˵�����Ч������problemLoading()������ӡ������Ϣ
        problemLoading("'setnormal.png' and 'setselected.png'");
    }
    else
    {//���ò˵�����Ч����������������ò˵����λ��
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3;
        setItem->setPosition(Vec2(x, y));
    }
    MenuItems.pushBack(setItem);

    // add a "close" icon to exit the progress. it's an autorelease object
    //�˳��˵������ͨ��ѡ��״̬�µ�ͼƬ��Դ
    //ͨ������������CC_CALLBACK_1()ָ���˵��û�������˳��˵���ʱ������HelloWorld::menuCloseCallback��������
    auto closeItem = MenuItemImage::create(
        "quitnormal.png",
        "quitselected.png",
        CC_CALLBACK_1(StartScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {//���˳��˵�����Ч������problemLoading()������ӡ������Ϣ
        problemLoading("'quitnormal.png' and 'quitselected.png'");
    }
    else
    {//�˳��˵�����Ч��������������˳��˵����λ��
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3 - closeItem->getContentSize().height * 20 / 13;
        closeItem->setPosition(Vec2(x, y));
    }
    MenuItems.pushBack(closeItem);

    // create menu, it's an autorelease object�Զ��ͷŶ���
    auto menu = Menu::createWithArray(MenuItems);//�����˵��������ոյ��˳��˵���closeItem��Ϊ��������
    menu->setPosition(Vec2::ZERO);//���˵���λ������Ϊ(0, 0)�������½�
    this->addChild(menu, 1);//���˵���ӵ���ǰ��ͼ���У��㼶����Ϊ1����ʾ���˵�������ͼ������Ϸ�

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //������һ��ʹ��TrueType�����ļ��ı�ǩ�����д���Ĳ����ֱ���Ҫ��ʾ���ı����ݡ������ļ�·���������С
    auto label = Label::createWithTTF("Pokemon Chess", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {//����ǩ����ӡ������Ϣ
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {//��ǩ��Ч�������������ñ�ǩ��λ��Ϊ��Ļ�����Ϸ�
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        //����ǩ��ӵ���ǰͼ���У��㼶����Ϊ1����ʾ����ǩ����������Ԫ�ص��Ϸ�
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto background = Sprite::create("background.png");//��������
    if (background == nullptr)
    {//����Ƿ�ɹ������˾������
        problemLoading("'background.png'");
    }
    else
    {
        background->setContentSize(visibleSize);
        //���þ����λ��Ϊ��Ļ����
        // position the sprite on the center of the screen
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        //��������ӵ���ǰͼ���У��㼶����Ϊ0����ʾ���������������Ԫ�ص��·�
        this->addChild(background, -1);
    }
    return true;
}
void StartScene::menuStartCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }
    auto startScene = PlayMenu::createScene();
    Director::getInstance()->pushScene(startScene);
}
void StartScene::menuSetCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }
    auto setScene = SetMenu::createScene();
    Director::getInstance()->pushScene(setScene);
}
void StartScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application�ر�cocos2d-x��Ϸ�������˳�Ӧ�ó���
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
