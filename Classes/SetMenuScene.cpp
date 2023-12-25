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

#include "SetMenuScene.h"

using namespace cocos2d::ui;
USING_NS_CC;

Scene* SetMenu::createScene()
{
    return SetMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
//��һ�д�����Ϣ��ӡ���ļ���
//�ڶ��д�����Ϣ��ʾ�û������������"Resources/"ǰ׺���޸�����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SetMenuScene.cpp\n");
}

// on "init" you need to initialize your instance    SetMenu�����ĳ�ʼ��
bool SetMenu::init()
{
    //////////////////////////////
    // 1. super init first��ʼ��Scene���࣬�����ʼ��ʧ���򷵻�false
    if (!Scene::init())
    {
        return false;
    }
    //ͨ������Director::getInstance()��ȡDirector���ʵ��
    //Ȼ��ʹ��getVisibleSize()������ȡ�ɼ����ڵĳߴ�
    //visibleSize��������ֵΪһ��Size���󣬸ö�������˿��Ⱥ͸߶���Ϣ
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //����getVisibleOrigin()������ȡ�ɼ����ڵ�ԭ��λ�ã����½ǣ�
    //origin��������ֵΪһ��Vec2���󣬸ö��������ԭ���x��y����
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    Vector<MenuItem*> MenuItems_Set;
    
    auto slider = Slider::create();
    slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    slider->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - 4*slider->getContentSize().height));
    slider->setPercent(g_slider_position);//ÿ�ν��볡��ʱ������������һ�����õ�λ�ã�g_slider_position�Ķ�����AudioManager.cpp��
    slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                // ��ȡ����������ֵ�����跶Χ��0.0��1.0��
                // ���ñ������ֵ�����,����ͣ������
                AudioManager::pauseBackgroundMusic();
                AudioManager::setBackgroundMusicVolume(0.5);
                //BUG:���쳣�˳����ҵ���������������Ӧ����AudioManager::setBackgroundMusicVolume(slider->getPercent() / 100.0f);
                AudioManager::resumeBackgroundMusic();
                // ����������λ�ñ��浽ȫ�ֱ�����
                //g_slider_position = slider->getPercent();//BUG
                break;
            default:
                break;
        }
    });

    this->addChild(slider);

    auto label_volume = Label::createWithTTF("volume", "fonts/Marker Felt.ttf", 24);
    if (label_volume == nullptr)
    {//����ǩ����ӡ������Ϣ
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label_volume->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height - 4 * slider->getContentSize().height));

        // add the label as a child to this layer
        //����ǩ���ӵ���ǰͼ���У��㼶����Ϊ1����ʾ����ǩ����������Ԫ�ص��Ϸ�
        this->addChild(label_volume, 1);
    }
    
    auto checkbox = CheckBox::create("check_box_normal.png",
        "check_box_normal_press.png",
        "check_box_active.png",
        "check_box_normal_disable.png",
        "check_box_active_disable.png");
    checkbox->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - 4 * checkbox->getContentSize().height));
    checkbox->setSelected(lastCheckBoxState);
    checkbox->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                // ������һ�θ�ѡ���ѡ��״̬
                //lastCheckBoxState = checkbox->isSelected();//BUG:ȡ��ע�ͻ��쳣�˳�
                // �л���Ч���ر�����ֵ
                isAudioEnabled = !isAudioEnabled;

                // ������Ч���ر�����ֵ���û������Ч
                if (isAudioEnabled)
                {
                    // ������Ч
                    AudioManager::stopAllEffects();//��֪��Ϊʲô�����Ż�����
                }
                else
                {
                    // ������Ч
                    AudioManager::playEffect();
                }
                break;
            default:
                break;
        }
        });

    this->addChild(checkbox);

    auto label_audio = Label::createWithTTF("audio", "fonts/Marker Felt.ttf", 24);
    if (label_audio == nullptr)
    {//����ǩ����ӡ������Ϣ
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label_audio->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height - 4 * checkbox->getContentSize().height));

        // add the label as a child to this layer
        //����ǩ���ӵ���ǰͼ���У��㼶����Ϊ1����ʾ����ǩ����������Ԫ�ص��Ϸ�
        this->addChild(label_audio, 1);
    }

    //����
    auto backItem = MenuItemImage::create(
        "backnormal.png",
        "backselected.png",
        CC_CALLBACK_1(SetMenu::menuFirstCallback, this));

    if (backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0)
    {//���˳��˵�����Ч������problemLoading()������ӡ������Ϣ
        problemLoading("'backnormal.png' and 'backselected.png'");
    }
    else
    {//�˳��˵�����Ч��������������˳��˵����λ�ã�����������Ϊ��Ļ����ƫ�µ�λ��
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3 - backItem->getContentSize().height * 20 / 13;
        backItem->setPosition(Vec2(x, y));
    }
    MenuItems_Set.pushBack(backItem);

    // create menu, it's an autorelease object�Զ��ͷŶ���
    auto menu = Menu::createWithArray(MenuItems_Set);//�����˵�
    menu->setPosition(Vec2::ZERO);//���˵���λ������Ϊ(0, 0)�������½�
    this->addChild(menu, 1);//���˵����ӵ���ǰ��ͼ���У��㼶����Ϊ1����ʾ���˵�������ͼ������Ϸ�
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //������һ��ʹ��TrueType�����ļ��ı�ǩ�����д���Ĳ����ֱ���Ҫ��ʾ���ı����ݡ������ļ�·���������С
    auto label = Label::createWithTTF("SET", "fonts/Marker Felt.ttf", 24);
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
        //����ǩ���ӵ���ǰͼ���У��㼶����Ϊ1����ʾ����ǩ����������Ԫ�ص��Ϸ�
        this->addChild(label, 1);
    }

    // add "SetMenu" splash screen"
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
        //���������ӵ���ǰͼ���У��㼶����Ϊ0����ʾ���������������Ԫ�ص��·�
        this->addChild(background, -1);
    }
    return true;
}

void SetMenu::menuFirstCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }
    Director::getInstance()->popScene(); // �л���startscene����
}

void SetMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application�ر�cocos2d-x��Ϸ�������˳�Ӧ�ó���
    Director::getInstance()->end();

    //To navigate back to native iOS screen(if present) without quitting the application 
    //do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}