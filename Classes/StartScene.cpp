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
//第一行错误消息打印出文件名
//第二行错误消息提示用户根据情况添加"Resources/"前缀来修复问题
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance    StartScene场景的初始化
bool StartScene::init()
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

    //音乐开始播放
    AudioManager::preloadBackgroundMusic();
    AudioManager::playBackgroundMusic();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to do something about the program
    //    you may modify it.

    Vector<MenuItem*> MenuItems;

    //开始游戏
    auto playItem = MenuItemImage::create(
        "playnormal.png",
        "playselected.png",
        CC_CALLBACK_1(StartScene::menuStartCallback, this));

    if (playItem == nullptr ||
        playItem->getContentSize().width <= 0 ||
        playItem->getContentSize().height <= 0)
    {//若开始菜单项无效，调用problemLoading()函数打印错误消息
        problemLoading("'playnormal.png' and 'playselected.png'");
    }
    else
    {//开始菜单项有效，接下来会计算开始菜单项的位置
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2 + playItem->getContentSize().height;
        playItem->setPosition(Vec2(x, y));
    }
    MenuItems.pushBack(playItem);

    //设置
    auto setItem = MenuItemImage::create(
        "setnormal.png",
        "setselected.png",
        CC_CALLBACK_1(StartScene::menuSetCallback, this));

    if (setItem == nullptr ||
        setItem->getContentSize().width <= 0 ||
        setItem->getContentSize().height <= 0)
    {//若设置菜单项无效，调用problemLoading()函数打印错误消息
        problemLoading("'setnormal.png' and 'setselected.png'");
    }
    else
    {//设置菜单项有效，接下来会计算设置菜单项的位置
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3;
        setItem->setPosition(Vec2(x, y));
    }
    MenuItems.pushBack(setItem);

    // add a "close" icon to exit the progress. it's an autorelease object
    //退出菜单项的普通和选中状态下的图片资源
    //通过第三个参数CC_CALLBACK_1()指定了当用户点击该退出菜单项时，调用HelloWorld::menuCloseCallback方法处理
    auto closeItem = MenuItemImage::create(
        "quitnormal.png",
        "quitselected.png",
        CC_CALLBACK_1(StartScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {//若退出菜单项无效，调用problemLoading()函数打印错误消息
        problemLoading("'quitnormal.png' and 'quitselected.png'");
    }
    else
    {//退出菜单项有效，接下来会计算退出菜单项的位置
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3 - closeItem->getContentSize().height * 20 / 13;
        closeItem->setPosition(Vec2(x, y));
    }
    MenuItems.pushBack(closeItem);

    // create menu, it's an autorelease object自动释放对象
    auto menu = Menu::createWithArray(MenuItems);//创建菜单，并将刚刚的退出菜单项closeItem作为参数传入
    menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
    this->addChild(menu, 1);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //创建了一个使用TrueType字体文件的标签，其中传入的参数分别是要显示的文本内容、字体文件路径和字体大小
    auto label = Label::createWithTTF("Pokemon Chess", "fonts/Marker Felt.ttf", 24);
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

    // add "HelloWorld" splash screen"
    auto background = Sprite::create("background.png");//创建精灵
    if (background == nullptr)
    {//检查是否成功创建了精灵对象
        problemLoading("'background.png'");
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
void StartScene::menuStartCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        AudioManager::playEffect();
    }
    auto startScene = PlayMenu::createScene();
    Director::getInstance()->pushScene(startScene);
}
void StartScene::menuSetCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        AudioManager::playEffect();
    }
    auto setScene = SetMenu::createScene();
    Director::getInstance()->pushScene(setScene);
}
void StartScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application关闭cocos2d-x游戏场景并退出应用程序
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
