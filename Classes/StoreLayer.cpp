#include"Store.h"
#include"StoreLayer.h"
//include"card.h"
USING_NS_CC;


StoreLayer* StoreLayer::create() {
	StoreLayer* layer = new (std::nothrow) StoreLayer();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

void StoreLayer::disableMouseListener() {
	// ������������
	StoreLayerMouseListener->setEnabled(false);
}

void StoreLayer::enableMouseListener() {
	// ������������
	StoreLayerMouseListener->setEnabled(true);
}

void StoreLayer::showStore() {//��ʾ�̵����ݼ���������
    for (int i = 0; i < 5; i++) {
        if (layerId[i] == -1) {
            auto sprite = Sprite::create("03.jpg");
            sprite->setContentSize(Size(pictureSize, pictureSize));
            sprite->setPosition(Vec2(i * 200 + 200, pictureSize / 2));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
        else if (layerId[i] % 3 == 0) {
            auto sprite = Sprite::create("Yevee-card.png");
            sprite->setContentSize(Size(pictureSize, pictureSize));
            sprite->setPosition(Vec2(i * 200 + 200, pictureSize / 2));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
        else if (layerId[i] % 3 == 1) {
            auto sprite = Sprite::create("Charmander-card.png");
            sprite->setContentSize(Size(pictureSize, pictureSize));
            sprite->setPosition(Vec2(i * 200 + 200, pictureSize / 2));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
        else if (layerId[i] % 3 == 2) {
            auto sprite = Sprite::create("Squirtle-card.png");
            sprite->setContentSize(Size(pictureSize, pictureSize));
            sprite->setPosition(Vec2(i * 200 + 200, pictureSize / 2));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
    }
}

void StoreLayer::updateMoneyLabel() {
    // �����µ��ı�����
    std::string newLabel = "Money:\n  " + std::to_string(money);

    // �Ƴ�֮ǰ���ı���ǩ
    moneyLabel->removeFromParent();

    // �����µ��ı���ǩ
    moneyLabel = Label::createWithTTF(newLabel, "fonts/arial.ttf", 30);
    moneyLabel->setPosition(Vec2(50, 100));
    moneyLabel->setColor(Color3B::RED);

    // ���µ��ı���ǩ��ӵ�����
    this->addChild(moneyLabel);
}


void StoreLayer::updateLevelLabel() {//���µȼ��뾭���ı�
    std::string newLabel = "LEVEL " + std::to_string(level) + "  EXP " + std::to_string(exp);
    // �Ƴ�֮ǰ���ı���ǩ
    levelAndExpLabel->removeFromParent();

    // �����µ��ı���ǩ
    levelAndExpLabel = Label::createWithTTF(newLabel, "fonts/arial.ttf", 20);
    levelAndExpLabel->setPosition(Vec2(1170, 40));
    levelAndExpLabel->setColor(Color3B::RED);

    // ���µ��ı���ǩ��ӵ�����
    this->addChild(levelAndExpLabel);
}

//����ƶ��¼��Ļص�����
void StoreLayer:: selectStore(Event* event) {
    // ��ȡ����¼�
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    // ��ȡ���λ��
    Vec2 mousePosition = mouseEvent->getLocationInView();

    Rect label1Rect = label1->getBoundingBox();
    Rect label2Rect = label2->getBoundingBox();
    Rect spriteRect0 = spriteArray[0]->getBoundingBox();
    Rect spriteRect1 = spriteArray[1]->getBoundingBox();
    Rect spriteRect2 = spriteArray[2]->getBoundingBox();
    Rect spriteRect3 = spriteArray[3]->getBoundingBox();
    Rect spriteRect4 = spriteArray[4]->getBoundingBox();
    if (label1Rect.containsPoint(mousePosition))
        refresh();
    if (label2Rect.containsPoint(mousePosition))
        upgrade();
    if (spriteRect0.containsPoint(mousePosition))
        buyCard(0);
    if (spriteRect1.containsPoint(mousePosition))
        buyCard(1);
    if (spriteRect2.containsPoint(mousePosition))
        buyCard(2);
    if (spriteRect3.containsPoint(mousePosition))
        buyCard(3);
    if (spriteRect4.containsPoint(mousePosition))
        buyCard(4);
}

bool StoreLayer::init() {
	Store::getStoreId(layerId);
	showStore();

    // �����ı���ǩ
    moneyLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 24);
    levelAndExpLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 20);
    label1 = Label::createWithTTF("REFRESH", "fonts/arial.ttf", 24);
    label2 = Label::createWithTTF("BUYEXP", "fonts/arial.ttf", 24);
    // �����ı���ǩ��λ��
    moneyLabel->setPosition(Vec2(0, 175));
    levelAndExpLabel->setPosition(Vec2(1170, 40));
    label1->setPosition(Vec2(1170, 160));
    label2->setPosition(Vec2(1170, 100));
    // �����ı���ɫ
    moneyLabel->setColor(Color3B::RED);
    levelAndExpLabel->setColor(Color3B::RED);
    label1->setColor(Color3B::BLUE);
    label2->setColor(Color3B::BLUE);
    // ���ı���ǩ��ӵ�����
    this->addChild(moneyLabel);
    this->addChild(levelAndExpLabel);
    this->addChild(label1);
    this->addChild(label2);
    updateMoneyLabel();
    updateLevelLabel();

    //StoreLayerMouseListener = EventListenerMouse::create();
    //StoreLayerMouseListener->onMouseDown = [this](EventMouse* event) {
    //    // �ж�ֻ�����������¼�
    //    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
    //        // �������������߼������Ե��� selectStore ������������
    //        selectStore(event);
    //    }
    //};
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(StoreLayerMouseListener, this);

	return true;
}

void StoreLayer::refresh() {
    if (money < Store::moneyPerRefresh) {
        noMoneyText();
        log("no money");
        return;
    }
	Store::getStoreId(layerId);
    money -= 2;
    updateMoneyLabel();
    showStore();
}

void StoreLayer::buyCard(int choice) {
   
    money -= (buyCardId / 3 + 1);
    if (money < 0) {
        noMoneyText();
        log("no money");
        money += (buyCardId / 3 + 1);
        return;
    }
    this->buyCardId = layerId[choice];
	layerId[choice] = -1;
    updateMoneyLabel();
    showStore();
}

void StoreLayer::sellCard(int sellCardId, int star) {
    money += (sellCardId / 3 + 1);
    if (star != 1)
        money--;
}

void StoreLayer::upgrade() {
    if (money < 4) {
        noMoneyText();
        log("no money");
        return;
    }
    Store::buyExp(money);
    exp = Store::getExp();
    level = Store::getLevel();
    updateLevelLabel();
    updateMoneyLabel();
    showStore();
}

void StoreLayer::alterMaxInteresr(int newInterest)
{
    Store::maxInterest = newInterest;
}

void StoreLayer::alterExpPerUpgrade(int newExpPerUpgrade)
{
    Store::expPerUpgrade = newExpPerUpgrade;
}

void StoreLayer::alterMoneyPerRefresh(int newMoneyPerRefresh)
{
    moneyPerRefresh = newMoneyPerRefresh;
}

void StoreLayer::noMoneyText() {
    // ֹ֮ͣǰ�����������еĵ�����
    unschedule(CC_SCHEDULE_SELECTOR(StoreLayer::updateText));
    // ɾ����һ�ε��ı�
    if (fadingText) {
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr; // ��ָ����Ϊ nullptr ��������ָ��
    }
    // �����ı���ǩ
    fadingText = Label::createWithTTF("You Have No Money", "fonts/arial.ttf", 36);
    fadingText->setPosition(Vec2(600, 300));
    this->addChild(fadingText);

    // ��ʼ��ʱ��
    elapsedTime = 0.0f;

    // ÿ֡����
    schedule(CC_SCHEDULE_SELECTOR(StoreLayer::updateText));
}

void StoreLayer::updateText(float dt)
{
    // ����ʱ��
    elapsedTime += dt;

    // ����͸���ȣ����Ը�����Ҫ�����仯���ٶ�
    int opacity = 255 - static_cast<int>(elapsedTime * 200);

    // �����ı�͸����
    fadingText->setOpacity(opacity);

    // ���͸����С�ڵ���0��ֹͣ����
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(StoreLayer::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr; // ��ָ����Ϊ nullptr ��������ָ��
    }
}
