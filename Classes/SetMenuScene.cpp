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

//SetMenu场景的初始化
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

    //音量滑动条
    auto slider = Slider::create();
    slider->loadBarTexture("Slider_Back.png");
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    //位置
    slider->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - 4 * slider->getContentSize().height));
    //设置百分比（记录上一次的拖动位置）
    slider->setPercent(cocos2d::UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50));
    slider->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                // 获取滑动条的数值（范围是0.0到1.0）
                // 设置背景音乐的音量,先暂停再设置
                cocos2d::experimental::AudioEngine::pause(globalAudioId);
                experimental::AudioEngine::setVolume(globalAudioId, slider->getPercent() / 100.0f);
                cocos2d::experimental::AudioEngine::resume(globalAudioId);
                // 将滑动条的位置保存到全局变量中
                cocos2d::UserDefault::getInstance()->setFloatForKey("backGroundMusicVolumn", slider->getPercent());
                break;
            default:
                break;
        }
        });
    this->addChild(slider);
    //音乐标签
    auto label_volume = Label::createWithTTF("volume", "fonts/Marker Felt.ttf", 24);
    if (label_volume == nullptr)
    {//检查标签，打印错误消息
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

    //音效复选框
    auto checkbox = CheckBox::create("check_box_normal.png",
        "check_box_normal_press.png",
        "check_box_active.png",
        "check_box_normal_disable.png",
        "check_box_active_disable.png");
    checkbox->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - 4 * checkbox->getContentSize().height));
    //保留音效状态
    if(isAudioEnabled)
        checkbox->setSelected(1);
    else
        checkbox->setSelected(0);
    checkbox->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                // 切换音效开关变量的值
                isAudioEnabled = !isAudioEnabled;
                // 根据音效开关变量的值启用或禁用音效
                if (isAudioEnabled)
                {// 启用音效
                    playSoundEffect("myEffect.mp3");
                }
                break;
            default:
                break;
        }
        });
    this->addChild(checkbox);
    //音效标签
    auto label_audio = Label::createWithTTF("audio", "fonts/Marker Felt.ttf", 24);
    if (label_audio == nullptr)
    {//检查标签，打印错误消息
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

    //创建菜单
    Vector<MenuItem*> MenuItems_Set;

    //回退
    auto backItem = MenuItemImage::create(
        "backnormal.png",
        "backselected.png",
        CC_CALLBACK_1(SetMenu::menuFirstCallback, this));

    if (backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0)
    {//若退出菜单项无效，调用problemLoading()函数打印错误消息
        problemLoading("'backnormal.png' and 'backselected.png'");
    }
    else
    {//退出菜单项有效，接下来会计算退出菜单项的位置，并将其设置为屏幕中心偏下的位置
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3 - backItem->getContentSize().height * 20 / 13;
        backItem->setPosition(Vec2(x, y));
    }
    MenuItems_Set.pushBack(backItem);

    //创建菜单
    auto menu = Menu::createWithArray(MenuItems_Set);
    menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
    this->addChild(menu, 1);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方
}
void SetMenu::initTopic()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //设置页面的标题
    auto label = Label::createWithTTF("SET", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {//检查标签，打印错误消息
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

    //背景
    auto background = Sprite::create("background_play.png");
    if (background == nullptr)
    {//检查是否成功创建了精灵对象
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
    {// 启用音效 
        playSoundEffect("myEffect.mp3");
    }
    Director::getInstance()->popScene(); // 切换到startscene场景
}
