#include"store.h"
#include"storeLayer.h"
//include"card.h"
USING_NS_CC;

storeLayer* storeLayer::create() {
	storeLayer* layer = new (std::nothrow) storeLayer();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

void storeLayer::disableMouseListener() {
	// ������������
	storeLayerMouseListener->setEnabled(false);
}

void storeLayer::enableMouseListener() {
	// ������������
	storeLayerMouseListener->setEnabled(true);
}

void storeLayer::showStore() {//��ʾ�̵����ݼ���������
    for (int i = 0; i < 5; i++) {
        if (layerId[i] == -1) {
            auto sprite = Sprite::create("03.jpg");
            sprite->setContentSize(Size(150, 150));
            sprite->setPosition(Vec2(i * 200 + 200, 100));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
        else if (layerId[i] % 3 == 0) {
            auto sprite = Sprite::create("Yevee-card.png");
            sprite->setContentSize(Size(150, 150));
            sprite->setPosition(Vec2(i * 200 + 200, 100));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
        else if (layerId[i] % 3 == 1) {
            auto sprite = Sprite::create("Chamander-card.png");
            sprite->setContentSize(Size(150, 150));
            sprite->setPosition(Vec2(i * 200 + 200, 100));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
        else if (layerId[i] % 3 == 2) {
            auto sprite = Sprite::create("Squirtle-card.png");
            sprite->setContentSize(Size(150, 150));
            sprite->setPosition(Vec2(i * 200 + 200, 100));
            this->addChild(sprite);
            spriteArray.push_back(sprite);
        }
    }
}

void storeLayer::updateMoneyLabel() {
    // �����µ��ı�����
    std::string newLabel = "Money:" + std::to_string(money);

    // �Ƴ�֮ǰ���ı���ǩ
    moneyLabel->removeFromParent();

    // �����µ��ı���ǩ
    moneyLabel = Label::createWithTTF(newLabel, "fonts/arial.ttf", 24);
    moneyLabel->setPosition(Vec2(600, 200));
    moneyLabel->setColor(Color3B::RED);

    // ���µ��ı���ǩ��ӵ�����
    this->addChild(moneyLabel);
}


void storeLayer::updateLevelLabel() {//���µȼ��뾭���ı�
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
void storeLayer:: selectStore(Event* event) {
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

bool storeLayer::init() {
	store::getStoreId(layerId);
	showStore();

    // �����ı���ǩ
    moneyLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 24);
    levelAndExpLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 20);
    label1 = Label::createWithTTF("REFRESH", "fonts/arial.ttf", 24);
    label2 = Label::createWithTTF("BUYEXP", "fonts/arial.ttf", 24);
    // �����ı���ǩ��λ��
    moneyLabel->setPosition(Vec2(600, 200));
    levelAndExpLabel->setPosition(Vec2(1170, 40));
    label1->setPosition(Vec2(1170, 180));
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

    storeLayerMouseListener = EventListenerMouse::create();
    storeLayerMouseListener->onMouseDown = CC_CALLBACK_1(storeLayer::selectStore, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(storeLayerMouseListener, this);

	return true;
}

void storeLayer::refresh() {
	store::getStoreId(layerId);
    money -= 2;
    updateMoneyLabel();
    showStore();
}

void storeLayer::buyCard(int choice) {
    money = money - (layerId[choice] / 3 + 1);
	layerId[choice] = -1;
    updateMoneyLabel();
    showStore();
}

void storeLayer::upgrade() {
    store::buyExp(money);
    exp = store::getExp();
    level = store::getLevel();
    updateLevelLabel();
    updateMoneyLabel();
    showStore();
}