
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

//StartScene�����ĳ�ʼ��
bool StartScene::init()
{
    // uper init first��ʼ��Scene���࣬�����ʼ��ʧ���򷵻�false
    if (!Scene::init())
    {
        return false;
    }
    //ʹ��getVisibleSize()������ȡ�ɼ����ڵĳߴ�
    //visibleSize��������ֵΪһ��Size���󣬸ö�������˿�Ⱥ͸߶���Ϣ
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //����getVisibleOrigin()������ȡ�ɼ����ڵ�ԭ��λ�ã����½ǣ�
    //origin��������ֵΪһ��Vec2���󣬸ö��������ԭ���x��y����
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //���ֿ�ʼ����
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("prepareMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);

    //�����˵�
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

    //�˳�
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
    
    //�����˵�
    auto menu = Menu::createWithArray(MenuItems);
    menu->setPosition(Vec2::ZERO);//���˵���λ������Ϊ(0, 0)�������½�
    this->addChild(menu, 1);//���˵���ӵ���ǰ��ͼ���У��㼶����Ϊ1����ʾ���˵�������ͼ������Ϸ�

    
    //������Ϸ����
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

    //��������ͼƬ
    auto background = Sprite::create("background.png");
    if (background == nullptr)
    {//����Ƿ�ɹ������˾������
        problemLoading("'background.png'");
    }
    else
    {
        background->setContentSize(visibleSize);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

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
    Director::getInstance()->end();
}
