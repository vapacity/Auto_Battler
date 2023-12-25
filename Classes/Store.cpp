// Store.cpp

#include "Store.h"



StoreAttribute* StoreAttribute::create()
{
    StoreAttribute* s = new (std::nothrow) StoreAttribute();
    if (s && s->init()) {// ��Ҫ���� retain������ player �ĳ�Ա���������ܱ������ͷ�
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}


bool StoreAttribute::init()
{
    if (!Node::init()) {
        return false;
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

//�����̵�
Store* Store::create(StoreAttribute* st)
{
    Store* s = new (std::nothrow) Store();
    if (s && s->init(st)) {
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}

//��ʼ���̵�
bool Store::init(StoreAttribute* st)
{
    if (!Node::init())
        return false;

    this->playerStore = st;

    // ��ʼ��ʱ�����������һ���̵�
    refreshStore();

    // ��ʼ��storeLayers����ָ��λ��
    for (int i = 0; i < 5; i++) {
        storeLayers[i] = StoreLayer::create(playerStore->idInStore[i]);
        storeLayers[i]->setPosition(Vec2(i * 200 + 130, 30));
        this->addChild(storeLayers[i]);
    }

    chessIdHaveBought = -1;

    // ��ʾ��Ǯ��
    std::string newLabel1 = "Money:\n  " + std::to_string(playerStore->money);
    moneyLabel = Label::createWithTTF(newLabel1, "fonts/arial.ttf", 30);
    moneyLabel->setPosition(Vec2(60, 175));
    moneyLabel->setColor(Color3B::RED);
    this->addChild(moneyLabel);

    // ��ʾ����͵ȼ�
    std::string newLabel2 = "LEVEL " + std::to_string(playerStore->level) + "  EXP " + std::to_string(playerStore->exp);
    levelAndExpLabel = Label::createWithTTF(newLabel2, "fonts/arial.ttf", 20);
    levelAndExpLabel->setPosition(Vec2(1170, 40));
    levelAndExpLabel->setColor(Color3B::RED);
    this->addChild(levelAndExpLabel);

    // ��ʾˢ�µı�ǩ
    labelRefresh = Label::createWithTTF("Refresh", "fonts/arial.ttf", 24);
    labelRefresh->setColor(Color3B::BLUE);
    labelRefresh->setPosition(Vec2(1170, 160));
    this->addChild(labelRefresh);

    // ��ʾ���µı�ǩ
    labelUpgrade = Label::createWithTTF("BuyXP", "fonts/arial.ttf", 24);
    labelUpgrade->setPosition(Vec2(1170, 100));
    labelUpgrade->setColor(Color3B::BLUE);
    this->addChild(labelUpgrade);

    updateForPlayer();

    schedule(CC_CALLBACK_0(Store::updateForPlayer, this), 0.0f, "updateStore");
    return true;
}

// ���½�Ǯ��ǩ
void Store::updateMoneyLabel()
{
    std::string newLabel = "Money:\n  " + std::to_string(playerStore->money);
    moneyLabel->setString(newLabel);
}

// ���¾����ǩ
void Store::updateLevelLabel()
{
    std::string newLabel = "LEVEL " + std::to_string(playerStore->level) + "  EXP " + std::to_string(playerStore->exp);
    levelAndExpLabel->setString(newLabel);
}

// ���������Ϣ�����̵���ʾ
void Store::updateForPlayer()
{
    updateMoneyLabel();
    updateLevelLabel();

    // ���¿�����ʾ
    for (int i = 0; i < 5; i++) {
        storeLayers[i]->refreshWithId(playerStore->idInStore[i]);
    }
}

// ˢ���̵�
void Store::refreshStore()
{
    srand((unsigned)time(NULL));

    for (int i = 0; i < 5; i++) {
        int costPointer = rand() % 100;
        switch (whichCost(costPointer)) {
            case -2:
                playerStore->idInStore[i] = -2;
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

// ��������������ݣ������ڵ�ǰ����ȼ��£���Ӧ�����ӳ�ʼ����
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

// ������
void Store::buyExp()
{
    playerStore->money -= 4;
    playerStore->exp += EXP_FOR_UPGRADE;
    if (playerStore->exp >= levelExp[playerStore->level - 1]) {
        playerStore->exp -= levelExp[playerStore->level - 1];
        playerStore->level++;
    }
    renewInterest();
}

// ������money����󣬸���playerStore�е�����
void Store::renewInterest()
{
    int add = playerStore->money / 10;
    if (add >= MAX_INTEREST)
        add = MAX_INTEREST;
    add += INIT_ADD_FOR_TURN;
    playerStore->interest = add;
}

// ˢ�£��޸��˽�Ǯ������Ϳ����ڵ�id����û�ж���ʾ
void Store::refresh()
{
    if (playerStore->money < MONEY_FOR_REFRESH) {
        createText("You Have No Money");
        log("no money");
        return;
    }
    refreshStore();
    playerStore->money -= MONEY_FOR_REFRESH;
    renewInterest();
}

// �������ſ��۵����ӣ����¿�����Ϣ������Ǯ�������򵽵�����id��chessIdHaveBought
void Store::buyCard(int choice)
{
    int id = playerStore->idInStore[choice];
    if (id == -1 || id == -2)
        return;
    playerStore->money -= StoreLayer::calCostFromId(id);
    if (playerStore->money < 0) {
        createText("You Have No Money");
        playerStore->money += StoreLayer::calCostFromId(id);
        chessIdHaveBought = -1;
        return;
    }
    playerStore->idInStore[choice] = -1;
    chessIdHaveBought = id;
    renewInterest();
}

// ���ݴ��������id���Ǽ������³��ۺ��money��ֵ������
void Store::sellCard(int sellCardId, int star)
{
    playerStore->money += StoreLayer::calCostFromId(sellCardId);
    if (star != 1)
        playerStore->money--;
    renewInterest();
}

// �������޸��˽�Ǯ�����飬�ȼ�
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
    buyExp();
}

// �жϵ���¼���ִ��
void Store::selectStore(Event* event, Vec2 mousePosition, bool isFull)
{
    Rect label1Rect = labelRefresh->getBoundingBox();
    Rect label2Rect = labelUpgrade->getBoundingBox();

    Rect spriteRect0 = storeLayers[0]->getBoundingBox();
    Rect spriteRect1 = storeLayers[1]->getBoundingBox();
    Rect spriteRect2 = storeLayers[2]->getBoundingBox();
    Rect spriteRect3 = storeLayers[3]->getBoundingBox();
    Rect spriteRect4 = storeLayers[4]->getBoundingBox();

    if (label1Rect.containsPoint(mousePosition))
        refresh();
    if (label2Rect.containsPoint(mousePosition))
        upgrade();
    if (!isFull) {
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
}

//���������ı����ʾ������һ��ʱ����Զ��Ƴ�
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

//createText�ĵ������ã�ʹ��ʾ�𽥵���
void Store::updateText(float dt)
{
    elapsedTime += dt;

    int opacity = 255 - static_cast<int>(elapsedTime * 200);

    fadingText->setOpacity(opacity);

    //��ȫ͸����ֹͣ������
    if (opacity <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(Store::updateText));
        fadingText->removeFromParentAndCleanup(true);
        fadingText = nullptr;
    }
}