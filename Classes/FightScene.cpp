#include "FightScene.h"

FightScene::FightScene()
{
    webSocket_ = new cocos2d::network::WebSocket();
    webSocket_->init(*this, "ws://100.81.177.2:3000"); // 替换为你的服务器地址和端口号
}

FightScene::~FightScene()
{
    webSocket_->close();
}

void FightScene::sendChessInfoToServer()
{
    rapidjson::Document document;
    document.SetObject();

    // 创建数组，用于存储棋子信息
    rapidjson::Value chessArray(rapidjson::kArrayType);

    // 遍历棋子数组，将信息存储到 JSON 数组中
    for (const auto& Node : myPlayer->myChessMap) {
        rapidjson::Value chessObject(rapidjson::kObjectType);
        auto chess = Node.second;
        auto location = Node.first;
        chessObject.AddMember("id", chess->getId(), document.GetAllocator());
        //chessObject.AddMember("playerNumber", chess->playerNumber, document.GetAllocator());
        chessObject.AddMember("star", chess->getStar(), document.GetAllocator());
        chessObject.AddMember("x", location.x, document.GetAllocator());
        chessObject.AddMember("y", location.y, document.GetAllocator());
        chessObject.AddMember("playerNumber", myPlayer->playerNumber, document.GetAllocator());
        chessArray.PushBack(chessObject, document.GetAllocator());
    }

    // 将 JSON 数组添加到 JSON 文档中
    document.AddMember("chessArray", chessArray, document.GetAllocator());

    // 将 JSON 文档转换为字符串
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // 将 JSON 字符串发送到服务器
    std::string jsonString = buffer.GetString();
    webSocket_->send(jsonString);
}

cocos2d::Scene* FightScene::createScene()
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = FightScene::create();
    return scene;
}
FiniteTimeAction* createSequenceFromVector(const Vector<FiniteTimeAction*>& actions, int index) {
    if (index >= actions.size() - 1) {
        // 如果只剩一个动作或没有动作，直接返回该动作或 nullptr
        return index < actions.size() ? actions.at(index) : nullptr;
    }
    else {
        // 递归地创建序列
        // 确保当前动作与递归返回的动作顺序正确
        auto nextAction = createSequenceFromVector(actions, index + 1);
        return Sequence::createWithTwoActions(actions.at(index), nextAction);
    }
}

bool FightScene::init()
{
    // 首先调用基类的init方法
    if (!Scene::init())
    {
        return false;
    }
    initPlayer();
    initBackground();
    initGridMap();
    initPreparationSeats();
    initLittleHero();
    initStore();
    //moveChess(gridMap->myChessMap[Vec2(1, 0)], gridMap->myChessMap[Vec2(1, 0)]->stopMoveFlag);
    //initChessExp();
    //findEnemyAndMove();
    initWeb();
    sendChessInfoToServer();
    gridMap->disableMouseListener();
    //is->schedule([this](float dt) {this->update(dt); }, "update_key");
}

void FightScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
    enemyPlayer->convertToEnemy();
}

void FightScene::initBackground()
{
    backgroundImg = Sprite::create("battle-background2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backgroundImg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundImg->setScaleX(visibleSize.width / backgroundImg->getContentSize().width);
    backgroundImg->setScaleY(visibleSize.height / backgroundImg->getContentSize().height);
    this->addChild(backgroundImg, -1);
}
void FightScene::initChessExp()
{
    //正在测试同时出现三个
  /*  auto Yevee = ChessFactory::createChessById(0);
    if (Yevee) {
        Yevee->setScale(0.15);

        gridMap->addChessToGrid(Yevee, gridMap->getCellAtPosition(Vec2(5, 5)));
        myPlayer->addChess(Yevee);
        Yevee->playerNumber = 1;
        this->addChild(Yevee, 1);
    }*/

    auto charmander = ChessFactory::createChessById(31);
    if (charmander) {
        charmander->setScale(0.15);
        gridMap->addChessToGrid(charmander, gridMap->getCellAtPosition(Vec2(4, 4)));
        myPlayer->addChess(charmander);
        charmander->reverseImg();
        charmander->playerNumber = 1;

        this->addChild(charmander, 1);
    }
    auto charmander2 = ChessFactory::createChessById(32);
    if (charmander2) {
        charmander2->setScale(0.15);
        gridMap->addChessToGrid(charmander2, gridMap->getCellAtPosition(Vec2(10, 7)));
        myPlayer->addChess(charmander2);
        charmander2->reverseImg();
        charmander2->playerNumber = 1;
        this->addChild(charmander2, 1);
    }
    auto charmander3 = ChessFactory::createChessById(33);
    if (charmander3) {
        charmander3->setScale(0.15);
        gridMap->addChessToGrid(charmander3, gridMap->getCellAtPosition(Vec2(10, 5)));
        myPlayer->addChess(charmander3);
        charmander3->playerNumber = 1;
        charmander3->reverseImg();
        this->addChild(charmander3, 1);
    }

}
void FightScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    //此处需要一个导入地方棋盘的操作！！
   /* for (auto& pair : enemyPlayer->transformedMap)
    {
        gridMap->addChessToGrid(pair.second, gridMap->getCellAtPosition(pair.first));
    }*/
    this->addChild(gridMap, 0);
    //initChessExp();
    for (auto iter : gridMap->myChessMap)
    {
        iter.second->removeFromParent();
        this->addChild(iter.second, 1);
    }
    gridMap->selectSchedule(0);
}

void FightScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    this->addChild(preSeats);
}

void FightScene::initLittleHero()
{
    myLittleHero = myPlayer->myHero;

    //this->addChild(myLittleHero);
    //enemyLittleHero = enemyPlayer->myHero;
    //this->addChild(enemyLittleHero);
}

void FightScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void FightScene::initWeb()
{
    //webSocket_ = new cocos2d::network::WebSocket();
    //webSocket_->init(*this, "ws://100.81.177.2:3000"); // 替换为你的服务器地址和端口号
}

void FightScene::onOpen(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket connected");
}

void FightScene::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
    CCLOG("Received message: %s", data.bytes);
    std::string message(data.bytes, data.len);
    CCLOG("Received message: %s", message.c_str());
    // 在这里解析 JSON 数据，更新棋子状态等
    rapidjson::Document document;
    document.Parse(message.c_str());
    if (!document.HasParseError() && document.IsObject()) {
        // 检查是否存在 chessArray 键
        if (document.HasMember("chessArray") && document["chessArray"].IsArray()) {
            const rapidjson::Value& chessArray = document["chessArray"];
            for (rapidjson::SizeType i = 0; i < chessArray.Size(); i++) {
                const rapidjson::Value& chessObject = chessArray[i];

                // 获取棋子信息
                int id = chessObject["id"].GetInt();
                int star = chessObject["star"].GetInt();
                float x = chessObject["x"].GetFloat();
                float y = chessObject["y"].GetFloat();
                int enemyplayerNumber = chessObject["playerNumber"].GetInt();
                auto chess = Chess::createByIdAndStar(id, star);
                chess->playerNumber = enemyplayerNumber;
                //为了视角保持在以0号player的主视角
                gridMap->addChessToGrid(chess, gridMap->getCellAtPosition(Vec2(NUM_COLUMN - x - 1, NUM_LINE - y - 1)));
                chess->maxHP = chess->health;
                chess->initHealthBar();


            }
        }
    }
}

void FightScene::onClose(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket closed");
}

void FightScene::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    CCLOG("WebSocket error: %d", static_cast<int>(error));
}


void FightScene::update(float dt)
{
    Vector<Chess*> chesses;
    for (auto& chess : gridMap->myChessMap)
    {
        chesses.pushBack(chess.second);
    }

    for (auto& chess : chesses)
    {
        chess->updateInBattle(dt, gridMap);
    }
    //for (auto& chess : chesses)
    //{
    //    if (chess->health <= 0)
    //    {
    //        if (chess->isAnimationPlaying) {
    //            //死了的时候，就算正在移动或者正在攻击都需要直接停下
    //            this->stopAllActions();
    //        }
    //        // 处理死亡逻辑
    //        auto fadeOut = FadeOut::create(0.1f);//回调函数对目标产生伤害
    //        runAction(fadeOut);
    //        gridMap->removeChessOfGrid(gridMap->getCellAtPosition(chess->atGridPosition));//不能放在回调函数中，因为其它棋子需要直接搜索
    //    }
    //}
    updateWin(dt);
}

void FightScene::updateWin(float dt)
{
    int cntMy = 0;
    int cntEnemy = 0;
    for (auto& iter : gridMap->myChessMap)
    {
        if (iter.second->playerNumber == myPlayer->playerNumber)
            cntMy++;
        else
            cntEnemy++;
    }
    if (cntEnemy == 0) {
        // 创建一个Label
        auto label = Label::createWithTTF("You Win", "fonts/Marker Felt.ttf", 80); // 字体文件需要存在

        // 设置Label的颜色（可选）
        label->setColor(Color3B::WHITE);

        // 获取场景的尺寸和中心坐标
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // 设置Label的位置
        label->setPosition(centerPosition);

        // 将Label添加到当前场景
        this->addChild(label, 2); // 第二个参数是z-order，可以根据需要调整
    }
    else if (cntMy == 0) {
        // 创建一个Label
        auto label = Label::createWithTTF("Enemy Win", "fonts/Marker Felt.ttf", 80); // 字体文件需要存在

        // 设置Label的颜色（可选）
        label->setColor(Color3B::WHITE);

        // 获取场景的尺寸和中心坐标
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // 设置Label的位置
        label->setPosition(centerPosition);

        // 将Label添加到当前场景
        this->addChild(label, 2); // 第二个参数是z-order，可以根据需要调整
    }
}

