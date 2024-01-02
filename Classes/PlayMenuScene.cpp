
#include "PlayMenuScene.h"

USING_NS_CC;
class PrepareScene;
Scene* PlayMenu::createScene()
{
    return PlayMenu::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PlayMenuScene.cpp\n");
}

bool PlayMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    initMenu();
    initTopic();
    initBackground();


    return true;
}

void PlayMenu::initMenu()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建菜单
    Vector<MenuItem*> MenuItems_play;

    //人机对战
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

    //联机对战
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

    //回退
    auto backItem = MenuItemImage::create(
        "backnormal.png",
        "backselected.png",
        CC_CALLBACK_1(PlayMenu::menuFirstCallback, this));

    if (backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0)
    {//若退出菜单项无效，调用problemLoading()函数打印错误消息
        problemLoading("'backnormal.png' and 'backselected.png'");
    }
    else
    {//退出菜单项有效，接下来会计算退出菜单项的位置
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + visibleSize.height / 7 * 3 - backItem->getContentSize().height * 20 / 13;
        backItem->setPosition(Vec2(x, y));
    }
    MenuItems_play.pushBack(backItem);

    //创建菜单
    auto menu = Menu::createWithArray(MenuItems_play);
    menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
    this->addChild(menu, 1);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方
}

void PlayMenu::initTopic()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //标题
    auto label = Label::createWithTTF("START", "fonts/Marker Felt.ttf", 24);
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
void PlayMenu::initBackground()
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

void PlayMenu::menuMachinePlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    auto machinePrepareScene = PrepareScene::createScene();
    //过场淡入淡出
    float dur = 1.0f;
    auto transition = TransitionFade::create(dur, machinePrepareScene);
    Director::getInstance()->pushScene(transition);
}

void PlayMenu::menuMultiPlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    auto WaitingScene = WaitingRoomScene::create();
    Director::getInstance()->pushScene(WaitingScene);
}

void PlayMenu::menuFirstCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        playSoundEffect("myEffect.mp3");
    }
    Director::getInstance()->popScene(); // 切换到startscene场景
}
