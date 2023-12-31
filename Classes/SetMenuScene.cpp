#include<iostream>
#include "SetMenuScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "AudioManager.h"
using namespace cocos2d::ui;
USING_NS_CC;

Scene* SetMenu::createScene()
{
    return SetMenu::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SetMenuScene.cpp\n");
}

//SetMenu�����ĳ�ʼ��
bool SetMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    initMusic();
    initAudio();
    initBack();
    initTopic();
    initBackground();
    return true;
}
void SetMenu::initMusic()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //����������
    auto slider = Slider::create();
    slider->loadBarTexture("Slider_Back.png");
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    //λ��
    slider->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - 4 * slider->getContentSize().height));
    //���ðٷֱȣ���¼��һ�ε��϶�λ�ã�
    slider->setPercent(cocos2d::UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50));
    slider->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                // ��ȡ����������ֵ����Χ��0.0��1.0��
                // ���ñ������ֵ�����,����ͣ������
                cocos2d::experimental::AudioEngine::pause(globalAudioId);
                experimental::AudioEngine::setVolume(globalAudioId, slider->getPercent() / 100.0f);
                cocos2d::experimental::AudioEngine::resume(globalAudioId);
                // ����������λ�ñ��浽ȫ�ֱ�����
                cocos2d::UserDefault::getInstance()->setFloatForKey("backGroundMusicVolumn", slider->getPercent());
                break;
            default:
                break;
        }
        });
    this->addChild(slider);
    //���ֱ�ǩ
    auto label_volume = Label::createWithTTF("volume", "fonts/Marker Felt.ttf", 24);
    if (label_volume == nullptr)
    {//����ǩ����ӡ������Ϣ
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label_volume->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height - 4 * slider->getContentSize().height));
        this->addChild(label_volume, 1);
    }
}
void SetMenu::initAudio()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //��Ч��ѡ��
    auto checkbox = CheckBox::create("check_box_normal.png",
        "check_box_normal_press.png",
        "check_box_active.png",
        "check_box_normal_disable.png",
        "check_box_active_disable.png");
    checkbox->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - 4 * checkbox->getContentSize().height));
    checkbox->setSelected(cocos2d::UserDefault::getInstance()->getBoolForKey("lastCheckBoxState", 1));
    checkbox->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                // �л���Ч���ر�����ֵ
                isAudioEnabled = !isAudioEnabled;
                // ������Ч���ر�����ֵ���û������Ч
                if (isAudioEnabled)
                {// ������Ч
                    AudioManager::stopAllEffects();
                }
                else
                {// ������Ч
                    AudioManager::playEffect();
                }
                // ������һ�θ�ѡ���ѡ��״̬
                cocos2d::UserDefault::getInstance()->setBoolForKey("lastCheckBoxState", checkbox->isSelected());
                break;
            default:
                break;
        }
        });
    this->addChild(checkbox);
    //��Ч��ǩ
    auto label_audio = Label::createWithTTF("audio", "fonts/Marker Felt.ttf", 24);
    if (label_audio == nullptr)
    {//����ǩ����ӡ������Ϣ
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label_audio->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height - 4 * checkbox->getContentSize().height));
        this->addChild(label_audio, 1);
    }
}
void SetMenu::initBack()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //�����˵�
    Vector<MenuItem*> MenuItems_Set;

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

    //�����˵�
    auto menu = Menu::createWithArray(MenuItems_Set);
    menu->setPosition(Vec2::ZERO);//���˵���λ������Ϊ(0, 0)�������½�
    this->addChild(menu, 1);//���˵���ӵ���ǰ��ͼ���У��㼶����Ϊ1����ʾ���˵�������ͼ������Ϸ�
}
void SetMenu::initTopic()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //����ҳ��ı���
    auto label = Label::createWithTTF("SET", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {//����ǩ����ӡ������Ϣ
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);
    }
}
void SetMenu::initBackground()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //����
    auto background = Sprite::create("background_play.png");
    if (background == nullptr)
    {//����Ƿ�ɹ������˾������
        problemLoading("'background_play.png'");
    }
    else
    {
        background->setContentSize(visibleSize);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(background, -1);
    }
}
void SetMenu::menuFirstCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// ������Ч
        AudioManager::playEffect();
    }
    Director::getInstance()->popScene(); // �л���startscene����
}
