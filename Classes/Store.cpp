// Store.cpp

#include "Store.h"

StoreAttribute* StoreAttribute::create()
{
    try {
        StoreAttribute* s = new StoreAttribute();
        if (s && s->init()) {
            s->retain(); // 需要增加 retain，这是 player 的成员变量，不能被随意释放
            s->autorelease();
            return s;
        }
        CC_SAFE_DELETE(s);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
}

bool StoreAttribute::init()
{
    if (!Node::init()) {
        throw std::runtime_error("StoreAttribute initialization failed: Node initialization failed");
    }
    money = INIT_MONEY;
    exp = INIT_EXP;
    level = INIT_LEVEL;
    interest = INIT_INTEREST;
    for (int i = 0; i < 5; i++) {
        idInStore[i] = -1;
    }
    return true;
}

//创建商店
Store* Store::create(StoreAttribute* st)
{
    try {
        Store* s = new Store();
        if (s && s->init(st)) {
            s->autorelease();
            return s;
        }
        CC_SAFE_DELETE(s);
    }
    catch (const std::exception& e) {
        // 捕获到异常时的处理逻辑
        CCLOG("Exception caught: %s", e.what());
    }
    return nullptr;
}

//初始化商店
bool Store::init(StoreAttribute* st)
{
    if (!Node::init())
        throw std::runtime_error("Store initialization failed: Node initialization failed");

    this->playerStore = st;

    //初始化场景
    backGround = Sprite::create("StoreBackground.png");
    backGround->setContentSize(Size(1000, 180));
    backGround->setPosition(Vec2(600, 90));
    this->addChild(backGround, -1);

    //生成随机数种子
    srand((unsigned)time(NULL));

    // 初始化时，先随机生成一次商店
    refreshStore();

    // 初始化storeLayers放在指定位置
    for (int i = 0; i < 5; i++) {
        storeLayers[i] = StoreLayer::create(playerStore->idInStore[i]);
        storeLayers[i]->setPosition(Vec2(i * 200 + 130, 10));
        this->addChild(storeLayers[i]);
    }

    chessIdHaveBought = -1;//初始化购买的棋子id为-1

    // 显示金钱数
    gold = Sprite::create("Gold.png");
    gold->setContentSize(Size(80,80));
    gold->setPosition(Vec2(50, 110));
    this->addChild(gold);

    std::string newLabel1 = std::to_string(playerStore->money);
    moneyLabel = Label::createWithTTF(newLabel1, "fonts/arial.ttf", 50);
    moneyLabel->setPosition(Vec2(50, 40));
    moneyLabel->setColor(Color3B::RED);
    this->addChild(moneyLabel);

    // 显示经验和等级
    leVel = Sprite::create("Level.png");
    leVel->setContentSize(Size(180, 70));
    leVel->setPosition(Vec2(1190, 40));
    this->addChild(leVel);

    std::string newLabel2 = "LEVEL " + std::to_string(playerStore->level) + "  EXP " + std::to_string(playerStore->exp);
    levelAndExpLabel = Label::createWithTTF(newLabel2, "fonts/arial.ttf", 20);
    levelAndExpLabel->setPosition(Vec2(1190, 40));
    levelAndExpLabel->setColor(Color3B::BLUE);
    this->addChild(levelAndExpLabel);

    // 显示刷新的标签
    reFresh = Sprite::create("Refresh1.png");
    reFresh->setContentSize(Size(70, 70));
    reFresh->setPosition(Vec2(1140, 120));
    this->addChild(reFresh);

    // 显示升级的标签
    upGrade = Sprite::create("Upgrade1.png");
    upGrade->setContentSize(Size(70, 70));
    upGrade->setPosition(Vec2(1230, 120));
    this->addChild(upGrade);

    updateForPlayer();

    schedule(CC_CALLBACK_0(Store::updateForPlayer, this), 0.0f, "updateStore");
    return true;
}

// 更新金钱标签
void Store::updateMoneyLabel()
{
    std::string newLabel = std::to_string(playerStore->money);
    moneyLabel->setString(newLabel);
}

// 更新经验标签
void Store::updateLevelLabel()
{
    std::string newLabel = "LEVEL " + std::to_string(playerStore->level) + "  EXP " + std::to_string(playerStore->exp);
    if (playerStore->level == MAX_LEVEL) {
        newLabel = "LEVEL 5 MAX";
    }
    levelAndExpLabel->setString(newLabel);
}

// 根据玩家信息更新商店显示
void Store::updateForPlayer()
{
    updateMoneyLabel();//更新金钱显示
    updateLevelLabel();//更新等级和经验显示

    // 更新卡槽显示
    for (int i = 0; i < 5; i++) {
        storeLayers[i]->refreshWithId(playerStore->idInStore[i]);
    }
}

// 刷新商店
void Store::refreshStore()
{
    for (int i = 0; i < 5; i++) {
        int costPointer = rand() % 100;
        switch (whichCost(costPointer)) {
            case -2:
                playerStore->idInStore[i] = -2;//捕获失败
                break;
            case 1:
                playerStore->idInStore[i] = 11 + rand() % COST1_AMOUNT;
                break;
            case 2:
                playerStore->idInStore[i] = 21 + rand() % COST2_AMOUNT;
                break;
            case 3:
                playerStore->idInStore[i] = 31 + rand() % COST3_AMOUNT;
                break;
            default:
                playerStore->idInStore[i] = -2;
                break;
        }
    }
    return;
} 

// 传入随机出的数据概率，返回在当前人物等级下，对应的棋子初始费用
int Store::whichCost(int pointer)
{
    if (pointer <= cardPercent[playerStore->level - 1][0])
        return -2;
    else if (pointer <= cardPercent[playerStore->level - 1][1])
        return 1;
    else if (pointer <= cardPercent[playerStore->level - 1][2])
        return 2;
    else if (pointer <= cardPercent[playerStore->level - 1][3])
        return 3;
    return -1;
}


// 用于在money变更后，更新playerStore中的利润
void Store::renewInterest()
{
    int add = playerStore->money / 10;
    if (add >= MAX_INTEREST)
        add = MAX_INTEREST;
    add += INIT_ADD_FOR_TURN;
    playerStore->interest = add;
}

// 刷新，修改了金钱、利润和卡槽内的id，但没有动显示
void Store::refresh()
{
    if (playerStore->money < MONEY_FOR_REFRESH) {
        createText("You Have No Money");
        //log("no money");
        return;
    }
    this->unschedule("refreshTimer");
    reFresh->setTexture("Refresh0.png");
    reFresh->setContentSize(Size(70, 70));
    this->scheduleOnce([=](float dt) {
        refreshStore();
        playerStore->money -= MONEY_FOR_REFRESH;
        renewInterest();
        reFresh->setTexture("Refresh1.png");
        reFresh->setContentSize(Size(70, 70));
        }, 0.1f, "refreshTimer");

}

// 购买传入编号卡槽的棋子，更新卡槽信息，利润，钱，返回买到的棋子id到chessIdHaveBought
void Store::buyCard(int choice)
{
    int id = playerStore->idInStore[choice];
    //卡牌已购买或捕获失败，无法买
    if (id == -1 || id == -2)
        return;

    playerStore->money -= StoreLayer::calCostFromId(id);
    //钱不够不能买
    if (playerStore->money < 0) {
        createText("You Have No Money");
        playerStore->money += StoreLayer::calCostFromId(id);
        chessIdHaveBought = -1;
        return;
    }

    //买后卡槽的卡牌id置-1，表示已购买
    playerStore->idInStore[choice] = -1;
    chessIdHaveBought = id;//获取买的id

    renewInterest();
}

// 根据传入的棋子id和星级，更新出售后的money数值，利润
void Store::sellCard(int sellCardId, int star)
{
    playerStore->money += StoreLayer::calCostFromId(sellCardId);
    if (star != 1)
        playerStore->money--;
    renewInterest();
}

// 买经验升级，修改了金钱，经验，等级
void Store::upgrade()
{

    if (playerStore->level == MAX_LEVEL) {
        createText("You Are At The Max Level");
        return;
    }
    if (playerStore->money < EXP_FOR_UPGRADE) {
        createText("You Have No Money");
        return;
    }
    this->unschedule("upgradeTimer");
    upGrade->setTexture("Upgrade0.png");
    upGrade->setContentSize(Size(70, 70));
    this->scheduleOnce([=](float dt) {
        playerStore->money -= 4;
        playerStore->exp += EXP_FOR_UPGRADE;
        if (playerStore->exp >= levelExp[playerStore->level - 1]) {
            playerStore->exp -= levelExp[playerStore->level - 1];
            playerStore->level++;
        }
        renewInterest();
        upGrade->setTexture("Upgrade1.png");
        upGrade->setContentSize(Size(70, 70));
        }, 0.1f, "upgradeTimer");

}

// 判断点击事件并执行
void Store::selectStore(Event* event, Vec2 mousePosition, bool isFull)
{
    //刷新按钮
    Rect spriteRectA = reFresh->getBoundingBox();

    //升级按钮
    Rect spriteRectB = upGrade->getBoundingBox();

    //五个卡槽按钮
    Rect spriteRect0 = storeLayers[0]->getBoundingBox();
    Rect spriteRect1 = storeLayers[1]->getBoundingBox();
    Rect spriteRect2 = storeLayers[2]->getBoundingBox();
    Rect spriteRect3 = storeLayers[3]->getBoundingBox();
    Rect spriteRect4 = storeLayers[4]->getBoundingBox();

    if (spriteRectA.containsPoint(mousePosition))
        refresh();
    if (spriteRectB.containsPoint(mousePosition))
        upgrade();
    if (!isFull) {//备战席满了不能买
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
    else {
        createText("Your Seats Are Full");
    }
}

//输出随输入改变的提示，并在一段时间后自动移除
void Store::createText(const std::string& textContent)
{
    unschedule(CC_SCHEDULE_SELECTOR(Store::updateText));
    if (fadingText) {
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
    fadingText = Label::createWithTTF(textContent, "fonts/arial.ttf", 36);
    fadingText->setPosition(Vec2(600, 300));
    this->addChild(fadingText);

    elapsedTime = 0.0f;

    schedule(CC_SCHEDULE_SELECTOR(Store::updateText));


}

//createText的调度器用，使提示逐渐淡出
void Store::updateText(float dt)
{
    elapsedTime += dt;

    int opacity = 255 - static_cast<int>(elapsedTime * 200);

    fadingText->setOpacity(opacity);

    //完全透明后停止调度器
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(Store::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
}

