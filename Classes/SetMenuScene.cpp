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
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "AudioManager.h"
using namespace cocos2d::ui;
USING_NS_CC;

Scene* SetMenu::createScene()
{
    return SetMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
//第一行错误消息打印出文件名
//第二行错误消息提示用户根据情况添加"Resources/"前缀来修复问题
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SetMenuScene.cpp\n");
}

// on "init" you need to initialize your instance    SetMenu场景的初始化
bool SetMenu::init()
{
    //////////////////////////////
    // 1. super init first初始化Scene父类，如果初始化失败则返回false
    if (!Scene::init())
    {
        return false;
    }
    //通过调用Director::getInstance()获取Director类的实例
    //然后使用getVisibleSize()方法获取可见窗口的尺寸
    //visibleSize变量被赋值为一个Size对象，该对象包含了宽度和高度信息
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //调用getVisibleOrigin()方法获取可见窗口的原点位置（左下角）
    //origin变量被赋值为一个Vec2对象，该对象包含了原点的x和y坐标
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
    slider->setPercent(g_slider_position);//每次进入场景时滑动条保存上一次设置的位置，g_slider_position的定义在AudioManager.cpp里
    slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                // 获取滑动条的数值（假设范围是0.0到1.0）
                // 设置背景音乐的音量,先暂停再设置
                AudioManager::pauseBackgroundMusic();
                AudioManager::setBackgroundMusicVolume(0.5);
                //BUG:会异常退出而且调不了音量，本来应该是AudioManager::setBackgroundMusicVolume(slider->getPercent() / 100.0f);
                AudioManager::resumeBackgroundMusic();
                // 将滑动条的位置保存到全局变量中
                //g_slider_position = slider->getPercent();//BUG
                break;
            default:
                break;
        }
    });

    this->addChild(slider);

    auto label_volume = Label::createWithTTF("volume", "fonts/Marker Felt.ttf", 24);
    if (label_volume == nullptr)
    {//检查标签，打印错误消息
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label_volume->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height - 4 * slider->getContentSize().height));

        // add the label as a child to this layer
        //将标签添加到当前图层中，层级参数为1，表示将标签放置在其他元素的上方
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
                // 保存上一次复选框的选择状态
                //lastCheckBoxState = checkbox->isSelected();//BUG:取消注释会异常退出
                // 切换音效开关变量的值
                isAudioEnabled = !isAudioEnabled;

                // 根据音效开关变量的值启用或禁用音效
                if (isAudioEnabled)
                {
                    // 启用音效
                    AudioManager::stopAllEffects();//不知道为什么这样才会正常
                }
                else
                {
                    // 禁用音效
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
    {//检查标签，打印错误消息
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label_audio->setPosition(Vec2(origin.x + visibleSize.width / 4,
            origin.y + visibleSize.height - 4 * checkbox->getContentSize().height));

        // add the label as a child to this layer
        //将标签添加到当前图层中，层级参数为1，表示将标签放置在其他元素的上方
        this->addChild(label_audio, 1);
    }

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

    // create menu, it's an autorelease object自动释放对象
    auto menu = Menu::createWithArray(MenuItems_Set);//创建菜单
    menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
    this->addChild(menu, 1);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //创建了一个使用TrueType字体文件的标签，其中传入的参数分别是要显示的文本内容、字体文件路径和字体大小
    auto label = Label::createWithTTF("SET", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {//检查标签，打印错误消息
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {//标签有效，接下来会设置标签的位置为屏幕中心上方
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        //将标签添加到当前图层中，层级参数为1，表示将标签放置在其他元素的上方
        this->addChild(label, 1);
    }

    // add "SetMenu" splash screen"
    auto background = Sprite::create("background_play.png");//创建精灵
    if (background == nullptr)
    {//检查是否成功创建了精灵对象
        problemLoading("'background_play.png'");
    }
    else
    {
        background->setContentSize(visibleSize);
        //设置精灵的位置为屏幕中心
        // position the sprite on the center of the screen
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        //将精灵添加到当前图层中，层级参数为0，表示将精灵放置在其他元素的下方
        this->addChild(background, -1);
    }
    return true;
}

void SetMenu::menuFirstCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        AudioManager::playEffect();
    }
    Director::getInstance()->popScene(); // 切换到startscene场景
}

void SetMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application关闭cocos2d-x游戏场景并退出应用程序
    Director::getInstance()->end();

    //To navigate back to native iOS screen(if present) without quitting the application 
    //do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}