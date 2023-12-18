#include"Store.h"


const int cardPercent[MAX_LEVEL][4] = { {50,100,0,0},{25,85,100,0},{10,60,100,0},{0,40,80,100},{0,30,70,100} };//棋子概率
const int levelExp[4] = { 4,8,14,20 };//升级所需经验(共四次升级)

//根据传入的玩家信息创建商店
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

bool Store::init(StoreAttribute* st)//初始化
{
	if (!Node::init())
		return false;

	this->playerStore = st;


	//初始化时，先随机生成一次商店
	refreshStore();

	//初始化storeLayers放在指定位置
	for (int i = 0; i < 5; i++) {
		storeLayers[i] = StoreLayer::create(playerStore->idInStore[i]);
		storeLayers[i]->setPosition(Vec2(i * 200 + 130, 30));
		this->addChild(storeLayers[i]);
	}

	chessIdHaveBought = -1;

	//显示金钱数
	std::string newLabel1 = "Money:\n  " + std::to_string(playerStore->money);
	moneyLabel = Label::createWithTTF(newLabel1, "fonts/arial.ttf", 30);
	moneyLabel->setPosition(Vec2(60, 175));
	moneyLabel->setColor(Color3B::RED);
	this->addChild(moneyLabel);


	//显示经验和等级
	std::string newLabel2 = "LEVEL " + std::to_string(playerStore->level) + "  EXP " + std::to_string(playerStore->exp);
	levelAndExpLabel = Label::createWithTTF(newLabel2, "fonts/arial.ttf", 20);
	levelAndExpLabel->setPosition(Vec2(1170, 40));
	levelAndExpLabel->setColor(Color3B::RED);
	this->addChild(levelAndExpLabel);


	//显示刷新的标签
	labelRefresh = Label::createWithTTF("Refresh", "fonts/arial.ttf", 24);
	labelRefresh->setColor(Color3B::BLUE);
	labelRefresh->setPosition(Vec2(1170, 160));
	this->addChild(labelRefresh);

	//显示更新的标签
	labelUpgrade = Label::createWithTTF("BuyXP", "fonts/arial.ttf", 24);
	labelUpgrade->setPosition(Vec2(1170, 100));
	labelUpgrade->setColor(Color3B::BLUE);
	this->addChild(labelUpgrade);
		
	updateForPlayer();

	schedule(CC_CALLBACK_0(Store::updateForPlayer, this), 0.0f, "updateStore");
	return true;
}

//根据玩家信息更新商店显示
void Store::updateForPlayer()
{
	//更新金钱显示
	updateMoneyLabel();

	//更新经验显示
	updateLevelLabel();

	//更新卡槽显示
	for (int i = 0; i < 5; i++) {
		storeLayers[i]->refreshWithId(playerStore->idInStore[i]);
	}


}

//一种棋子有5个不同费用，须改
//刷新商店，更新5个playerStore的id
void Store::refreshStore()
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; i++) {//根据等级随机生成商店
		int costPointer = rand() % 100;
		switch (whichCost(costPointer)) {
			case -2:
				playerStore->idInStore[i] = -2;
				break;
			case 0:
				playerStore->idInStore[i] = rand() % COST1_Amount;
				break;
			case 1:
				playerStore->idInStore[i] = COST1_Amount + rand() % COST2_Amount;
				break;
			case 2:
				playerStore->idInStore[i] = COST1_Amount + COST2_Amount + rand() % COST3_Amount;
				break;
		}
	}
	return;
}


//传入随机出的数据，返回在当前人物等级下，对应的棋子初始费用
int Store::whichCost(int pointer) {
	//log("%d\n", cardPercent[level - 1][0]);
	if (pointer <= cardPercent[playerStore->level - 1][0])
		return -2;
	else if (pointer <= cardPercent[playerStore->level - 1][1])
		return 0;
	else if (pointer <= cardPercent[playerStore->level - 1][2])
		return 1;
	else if (pointer <= cardPercent[playerStore->level - 1][3])
		return 2;
	return -1;
}


//购买经验。改钱、经验、等级，利润
void Store::buyExp() {
	playerStore->money -= 4;
	playerStore->exp += EXP_FOR_UPGRADE;
	if (playerStore->exp >= levelExp[playerStore->level - 1]) {
		playerStore->exp -= levelExp[playerStore->level - 1];
		playerStore->level++;
		
	}
	renewInterest();
}

//用于在money变更后，更新playerStore中的利润
void Store::renewInterest() {
	int add = playerStore->money / 10;
	if (add >= MAX_INTEREST)
		add = MAX_INTEREST;
	add += INIT_ADD_FOR_TURN;//基础每回合金币
	playerStore->interest = add;
}

//刷新，修改了金钱、利润和卡槽内的id，但没有动显示
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

//未更新金钱标签，
//购买传入编号卡槽的棋子，更新卡槽信息，利润，钱，返回买到的棋子id到chessIdHaveBought
void Store::buyCard(int choice)
{
	int id = playerStore->idInStore[choice];
	if (id == -1 || id == -2)//不能重复购买或者购买捕捉失败的卡牌
		return;
	playerStore->money -= calCostFromId(id);
	if (playerStore->money < 0) {
		createText("You Have No Money");
		playerStore->money += calCostFromId(id);
		chessIdHaveBought = -1;
		return;
	}
	playerStore->idInStore[choice] = -1;
	chessIdHaveBought = id;
	renewInterest();
}


//未更新金钱标签，
//根据传入的棋子id和星级，更新出售后的money数值，利润
void Store::sellCard(int sellCardId, int star)
{
	playerStore->money += calCostFromId(sellCardId);
	if (star != 1)
		playerStore->money--;
	renewInterest();
}

//未更新相关标签
//升级，修改了金钱，经验，等级
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
	Store::buyExp();
}


//判断点击事件并执行
void Store::selectStore(Event* event,Vec2 mousePosition,bool isFull)
{
	//// 获取鼠标事件
	//EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	// 获取鼠标位置
	//Vec2 mousePosition = event->getLocationInView();
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



StoreAttribute* StoreAttribute::create()
{
	StoreAttribute* s = new (std::nothrow) StoreAttribute();
	if (s && s->init()) {
		s->retain();//需要增加retain,这是player的成员变量，不能被随意释放
		s->autorelease();
		return s;
	}
	CC_SAFE_DELETE(s);
	return nullptr;
}


//初始化player所需上商店信息
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



//更新金钱标签
void Store::updateMoneyLabel()
{
	// 构造新的文本内容
	std::string newLabel = "Money:\n  " + std::to_string(playerStore->money);
	moneyLabel->setString(newLabel);

}

//更新经验标签
void Store::updateLevelLabel()
{
	std::string newLabel = "LEVEL " + std::to_string(playerStore->level) + "  EXP " + std::to_string(playerStore->exp);

	// 创建新的文本标签
	levelAndExpLabel->setString(newLabel);

}

//输出金钱不足的提示，并在一段时间后自动移除
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

//noMoneyText的调度器用，使提示逐渐淡出
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

int Store::calCostFromId(int id)
{
	if (id < COST1_Amount)
		return 1;
	id -= COST1_Amount;
	if (id < COST2_Amount)
		return 2;
	id -= COST2_Amount;
	if (id < COST3_Amount)
		return 3;
	return 0;
}

