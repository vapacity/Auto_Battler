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
	// 禁用鼠标监听器
	StoreLayerMouseListener->setEnabled(false);
}

void StoreLayer::enableMouseListener() {
	// 启用鼠标监听器
	StoreLayerMouseListener->setEnabled(true);
}

void StoreLayer::showStore() {//显示商店数据及卡牌数据
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
    // 构造新的文本内容
    std::string newLabel = "Money:\n  " + std::to_string(money);

    // 移除之前的文本标签
    moneyLabel->removeFromParent();

    // 创建新的文本标签
    moneyLabel = Label::createWithTTF(newLabel, "fonts/arial.ttf", 30);
    moneyLabel->setPosition(Vec2(50, 100));
    moneyLabel->setColor(Color3B::RED);

    // 将新的文本标签添加到场景
    this->addChild(moneyLabel);
}


void StoreLayer::updateLevelLabel() {//更新等级与经验文本
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
void StoreLayer:: selectStore(Event* event) {
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

bool StoreLayer::init() {
	Store::getStoreId(layerId);
	showStore();

    // 创建文本标签
    moneyLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 24);
    levelAndExpLabel = Label::createWithTTF("NULL", "fonts/arial.ttf", 20);
    label1 = Label::createWithTTF("REFRESH", "fonts/arial.ttf", 24);
    label2 = Label::createWithTTF("BUYEXP", "fonts/arial.ttf", 24);
    // 设置文本标签的位置
    moneyLabel->setPosition(Vec2(0, 175));
    levelAndExpLabel->setPosition(Vec2(1170, 40));
    label1->setPosition(Vec2(1170, 160));
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

    //StoreLayerMouseListener = EventListenerMouse::create();
    //StoreLayerMouseListener->onMouseDown = [this](EventMouse* event) {
    //    // 判断只处理左键点击事件
    //    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
    //        // 处理左键点击的逻辑，可以调用 selectStore 或其他处理函数
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
    // 停止之前可能正在运行的调度器
    unschedule(CC_SCHEDULE_SELECTOR(StoreLayer::updateText));
    // 删除上一次的文本
    if (fadingText) {
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr; // 将指针置为 nullptr 避免悬挂指针
    }
    // 创建文本标签
    fadingText = Label::createWithTTF("You Have No Money", "fonts/arial.ttf", 36);
    fadingText->setPosition(Vec2(600, 300));
    this->addChild(fadingText);

    // 初始化时间
    elapsedTime = 0.0f;

    // 每帧更新
    schedule(CC_SCHEDULE_SELECTOR(StoreLayer::updateText));
}

void StoreLayer::updateText(float dt)
{
    // 更新时间
    elapsedTime += dt;

    // 计算透明度，可以根据需要调整变化的速度
    int opacity = 255 - static_cast<int>(elapsedTime * 200);

    // 设置文本透明度
    fadingText->setOpacity(opacity);

    // 如果透明度小于等于0，停止更新
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(StoreLayer::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr; // 将指针置为 nullptr 避免悬挂指针
    }
}
