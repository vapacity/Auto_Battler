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
	// 禁用鼠标监听器
	storeLayerMouseListener->setEnabled(false);
}

void storeLayer::enableMouseListener() {
	// 启用鼠标监听器
	storeLayerMouseListener->setEnabled(true);
}

void storeLayer::showStore() {//显示商店数据及卡牌数据
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
    // 构造新的文本内容
    std::string newLabel = "Money:" + std::to_string(money);

    // 移除之前的文本标签
    moneyLabel->removeFromParent();

    // 创建新的文本标签
    moneyLabel = Label::createWithTTF(newLabel, "fonts/arial.ttf", 24);
    moneyLabel->setPosition(Vec2(600, 200));
    moneyLabel->setColor(Color3B::RED);

    // 将新的文本标签添加到场景
    this->addChild(moneyLabel);
}


void storeLayer::updateLevelLabel() {//更新等级与经验文本
    std::string newLabel = "LEVEL " + std::to_string(level) + "  EXP " + std::to_string(exp);
    // 移除之前的文本标签
    levelAndExpLabel->removeFromParent();

    // 创建新的文本标签
    levelAndExpLabel = Label::createWithTTF(newLabel, "fonts/arial.ttf", 20);
    levelAndExpLabel->setPosition(Vec2(1170, 40));
    levelAndExpLabel->setColor(Color3B::RED);

    // 将新的文本标签添加到场景
    this->addChild(levelAndExpLabel);
}

//鼠标移动事件的回调函数
void storeLayer:: selectStore(Event* event) {
    // 获取鼠标事件
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    // 获取鼠标位置
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

    // 创建文本标签
    moneyLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 24);
    levelAndExpLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 20);
    label1 = Label::createWithTTF("REFRESH", "fonts/arial.ttf", 24);
    label2 = Label::createWithTTF("BUYEXP", "fonts/arial.ttf", 24);
    // 设置文本标签的位置
    moneyLabel->setPosition(Vec2(600, 200));
    levelAndExpLabel->setPosition(Vec2(1170, 40));
    label1->setPosition(Vec2(1170, 180));
    label2->setPosition(Vec2(1170, 100));
    // 设置文本颜色
    moneyLabel->setColor(Color3B::RED);
    levelAndExpLabel->setColor(Color3B::RED);
    label1->setColor(Color3B::BLUE);
    label2->setColor(Color3B::BLUE);
    // 将文本标签添加到场景
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