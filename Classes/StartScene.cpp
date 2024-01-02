
#include "StartScene.h"


USING_NS_CC;
class PlayMenu;
Scene* StartScene::createScene()
{
    return StartScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//StartScene场景的初始化
bool StartScene::init()
{
    // uper init first初始化Scene父类，如果初始化失败则返回false
    if (!Scene::init())
    {
        return false;
    }

    //音乐开始播放
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("prepareMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);

    //初始化菜单
    initMenu();
    //初始化标题
    initTopic();
    //初始化背景
    initBackground();

    return true;
}

void StartScene::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建菜单
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

    //退出
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

    //创建菜单
    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
    this->addChild(menu, 1);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方
}
void StartScene::initTopic()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建游戏标题
    auto label = Label::createWithTTF("Pokemon Chess", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        this->addChild(label, 1);
    }
}
void StartScene::initBackground()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建背景图片
    auto background = Sprite::create("background.png");
    if (background == nullptr)
    {//检查是否成功创建了精灵对象
        problemLoading("'background.png'");
    }
    else
    {
        background->setContentSize(visibleSize);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //将精灵添加到当前图层中，层级参数为0，表示将精灵放置在其他元素的下方
        this->addChild(background, -1);
    }
}
void StartScene::menuStartCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    auto startScene = PlayMenu::createScene();
    Director::getInstance()->pushScene(startScene);
}

void StartScene::menuSetCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    auto setScene = SetMenu::createScene();
    Director::getInstance()->pushScene(setScene);
}

void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}