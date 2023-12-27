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

#include "PlayMenuScene.h"

USING_NS_CC;
class PrepareScene;
Scene* PlayMenu::createScene()
{
    return PlayMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
//��һ�д�����Ϣ��ӡ���ļ���
//�ڶ��д�����Ϣ��ʾ�û�����������"Resources/"ǰ׺���޸�����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PlayMenuScene.cpp\n");
}

// on "init" you need to initialize your instance    PlayMenu�����ĳ�ʼ��
bool PlayMenu::init()
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    Vector<MenuItem*> MenuItems_play;

    //�˻���ս
    auto machinePlayItem = MenuItemImage::create(
        "renjinormal.png",
        "renjiselected.png",
        CC_CALLBACK_1(PlayMenu::menuMachinePlayCallback, this));

    if (machinePlayItem == nullptr ||
        machinePlayItem->getContentSize().width <= 0 ||
        machinePlayItem->getContentSize().height <= 0)
    {
        problemLoading("'renjinormal.png' and 'renjiselected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2 + machinePlayItem->getContentSize().height;
        machinePlayItem->setPosition(Vec2(x, y));
    }
    MenuItems_play.pushBack(machinePlayItem);

    //������ս
    auto humanPlayItem = MenuItemImage::create(
        "lianjinormal.png",
        "lianjiselected.png",
        CC_CALLBACK_1(PlayMenu::menuMultiPlayCallback, this));

    if (humanPlayItem == nullptr ||
        humanPlayItem->getContentSize().width <= 0 ||
        humanPlayItem->getContentSize().height <= 0)
    {
        problemLoading("'lianjinormal.png' and 'lianjiselected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3;
        humanPlayItem->setPosition(Vec2(x, y));
    }
    MenuItems_play.pushBack(humanPlayItem);

    //����
    auto backItem = MenuItemImage::create(
        "backnormal.png",
        "backselected.png",
        CC_CALLBACK_1(PlayMenu::menuFirstCallback, this));

    if (backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0)
    {//���˳��˵�����Ч������problemLoading()������ӡ������Ϣ
        problemLoading("'backnormal.png' and 'backselected.png'");
    }
    else
    {//�˳��˵�����Ч��������������˳��˵����λ��
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3 - backItem->getContentSize().height * 20 / 13;
        backItem->setPosition(Vec2(x, y));
    }
    MenuItems_play.pushBack(backItem);

    // create menu, it's an autorelease object�Զ��ͷŶ���
    auto menu = Menu::createWithArray(MenuItems_play);//�����˵�
    menu->setPosition(Vec2::ZERO);//���˵���λ������Ϊ(0, 0)�������½�
    this->addChild(menu, 1);//���˵���ӵ���ǰ��ͼ���У��㼶����Ϊ1����ʾ���˵�������ͼ������Ϸ�

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //������һ��ʹ��TrueType�����ļ��ı�ǩ�����д���Ĳ����ֱ���Ҫ��ʾ���ı����ݡ������ļ�·���������С
    auto label = Label::createWithTTF("START", "fonts/Marker Felt.ttf", 24);
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

    // add "PlayMenu" splash screen"
    auto background = Sprite::create("background_play.png");//��������
    if (background == nullptr)
    {//����Ƿ�ɹ������˾������
        problemLoading("'background_play.png'");
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

void PlayMenu::menuMachinePlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }

    auto machinePrepareScene = PrepareScene::createScene();
    float dur = 1.0f;
    auto transition = TransitionFade::create(dur, machinePrepareScene);
    Director::getInstance()->pushScene(transition);
}

void PlayMenu::menuMultiPlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }
    auto WaitingScene = WaitingRoomScene::create();
    Director::getInstance()->pushScene(WaitingScene);
}

void PlayMenu::menuFirstCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }
    Director::getInstance()->popScene(); // �л���startscene����
}

void PlayMenu::menuCloseCallback(Ref* pSender)
{
    //�ر�cocos2d-x��Ϸ�������˳�Ӧ�ó���
    Director::getInstance()->end();

    //To navigate back to native iOS screen(if present) without quitting the application 
    //do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
