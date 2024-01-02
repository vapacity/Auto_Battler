
#include "PlayMenuScene.h"
#include "SimpleAudioEngine.h"
#include "StartScene.h"
#include "AudioManager.h"
#include "HumanPlayScene.h"
USING_NS_CC;

Scene* HumanPlayScene::createScene()
{
    return HumanPlayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
//第一行错误消息打印出文件名
//第二行错误消息提示用户根据情况添加"Resources/"前缀来修复问题
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HumanPlayScene.cpp\n");
}

// on "init" you need to initialize your instance    HumanPlay场景的初始化
bool HumanPlayScene::init()
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

    Vector<MenuItem*> MenuItems_multiplayer;

    //创建房间
    auto createRoomItem = MenuItemImage::create(
        "createnormal.png",
        "createselected.png",
        CC_CALLBACK_1(HumanPlayScene::menuCloseCallback, this));

    if (createRoomItem == nullptr ||
        createRoomItem->getContentSize().width <= 0 ||
        createRoomItem->getContentSize().height <= 0)
    {
        problemLoading("'createnormal.png' and 'createselected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 2 + createRoomItem->getContentSize().height;
        createRoomItem->setPosition(Vec2(x, y));
    }
    MenuItems_multiplayer.pushBack(createRoomItem);

    //加入房间
    auto joinRoomItem = MenuItemImage::create(
        "joinnormal.png",
        "joinselected.png",
        CC_CALLBACK_1(HumanPlayScene::menuCloseCallback, this));

    if (joinRoomItem == nullptr ||
        joinRoomItem->getContentSize().width <= 0 ||
        joinRoomItem->getContentSize().height <= 0)
    {
        problemLoading("'joinnormal.png' and 'joinselected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3;
        joinRoomItem->setPosition(Vec2(x, y));
    }
    MenuItems_multiplayer.pushBack(joinRoomItem);

    //回退
    auto backItem = MenuItemImage::create(
        "backnormal.png",
        "backselected.png",
        CC_CALLBACK_1(HumanPlayScene::menuPlayMenuCallback, this));

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
    MenuItems_multiplayer.pushBack(backItem);

    // create menu, it's an autorelease object自动释放对象
    auto menu = Menu::createWithArray(MenuItems_multiplayer);//创建菜单
    menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
    this->addChild(menu, 1);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //创建了一个使用TrueType字体文件的标签，其中传入的参数分别是要显示的文本内容、字体文件路径和字体大小
    auto label = Label::createWithTTF("HUMANPLAY", "fonts/Marker Felt.ttf", 24);
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

    // add "HumanPlay" splash screen"
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

void HumanPlayScene::menuPlayMenuCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        AudioManager::playEffect();
    }
    Director::getInstance()->popScene(); // 切换到startscene场景
}

void HumanPlayScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application关闭cocos2d-x游戏场景并退出应用程序
    Director::getInstance()->end();

    //To navigate back to native iOS screen(if present) without quitting the application 
    //do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}