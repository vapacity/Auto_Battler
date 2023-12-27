#include "OnlineFightScene.h"
#include "FightScene.h"
#define enemyPosition Vec2(1050,650)
#define myPosition Vec2(40,265)
cocos2d::Scene* OnlineFightScene::createScene()
{
    // 创建一个场景对象，该对象将由自动释放池自动释放
    auto scene = OnlineFightScene::create();
    return scene;
}

//FiniteTimeAction* createSequenceFromVector(const Vector<FiniteTimeAction*>& actions, int index) {
//    if (index >= actions.size() - 1) {
//         如果只剩一个动作或没有动作，直接返回该动作或 nullptr
//        return index < actions.size() ? actions.at(index) : nullptr;
//    }
//    else {
//         递归地创建序列
//         确保当前动作与递归返回的动作顺序正确
//        auto nextAction = createSequenceFromVector(actions, index + 1);
//        return Sequence::createWithTwoActions(actions.at(index), nextAction);
//    }
//}

bool OnlineFightScene::init()
{
    // 首先调用基类的init方法
    if (!Scene::init())
    {
        return false;
    }
    initPlayer();
    initBackground();
    initWeb();
    initGridMap();
    initPreparationSeats();
    initLittleHero();
    initStore();
    enableMouseListener();
    //moveChess(gridMap->myChessMap[Vec2(1, 0)], gridMap->myChessMap[Vec2(1, 0)]->stopMoveFlag);
    //initChessExp();
    //findEnemyAndMove();
    gridMap->disableMouseListener();
  //  this->schedule([this](float dt) {this->update(dt); }, "update_key");

}

void OnlineFightScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);
    enemyPlayer->convertToEnemy();
}

void OnlineFightScene::initBackground()
{
    backgroundImg = Sprite::create("battle-background2.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backgroundImg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    backgroundImg->setScaleX(visibleSize.width / backgroundImg->getContentSize().width);
    backgroundImg->setScaleY(visibleSize.height / backgroundImg->getContentSize().height);
    this->addChild(backgroundImg, -1);
}
void OnlineFightScene::initChessExp()
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

    /*auto charmander = ChessFactory::createChessById(31);
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
    }*/
    //auto charmander3 = ChessFactory::createChessById(31);
    //if (charmander3) {
    //    charmander3->initHealthBar();
    //    charmander3->initBlueBar();
    //    charmander3->maxHP = charmander3->health;
    //    gridMap->addChessToGrid(charmander3, gridMap->getCellAtPosition(Vec2(10, 5)));
    //    //myPlayer->addChess(charmander3);
    //    charmander3->playerNumber = 1;
    //    charmander3->reverseImg();
    //    this->addChild(charmander3, 1);
    //}

}
void OnlineFightScene::createChessOnGrids()
{
    for (auto a : myPlayer->myChessMap) {
        int newChessId = a.second->id;
        int newChessStar = a.second->star;
        Chess* newChess = Chess::createByIdAndStar(newChessId, newChessStar);
        gridMap->nodeMap.at(a.first)->chessInGrid = newChess;
        gridMap->addChessToGrid(newChess, gridMap->getCellAtPosition(a.first));
        newChess->playerNumber = myPlayer->playerNumber;
        this->addChild(newChess, 2);
    }
 /*   for (auto a : enemyPlayer->transformedMap) {
        int newChessId = a.second->id;
        int newChessStar = a.second->star;
        Chess* newChess = Chess::createByIdAndStar(newChessId, newChessStar);
        newChess->reverseImg();
        newChess->playerNumber = 1 - myPlayer->playerNumber;
        gridMap->nodeMap.at(a.first)->chessInGrid = newChess;
        gridMap->addChessToGrid(newChess, gridMap->getCellAtPosition(a.first));
        this->addChild(newChess, 2);
    }*/
}
void OnlineFightScene::initGridMap()
{
    gridMap = GridMap::create(myPlayer->myChessMap);
    createChessOnGrids();
    this->addChild(gridMap, 0);
    gridMap->selectSchedule(0);
}

void OnlineFightScene::initPreparationSeats()
{
    preSeats = PreparationSeats::create(myPlayer->mySeats);
    this->addChild(preSeats);
}

void OnlineFightScene::initLittleHero()
{
    myLittleHero = myPlayer->myHero;
    if (myLittleHero->getParent())
        myLittleHero->removeFromParent();
    myLittleHero->isAnimationPlaying = false;
    enemyLittleHero = enemyPlayer->myHero;
    if (enemyLittleHero->getParent())
        enemyLittleHero->removeFromParent();
    enemyLittleHero->setColor(Color3B(180, 180, 180));
    enemyLittleHero->isAnimationPlaying = false;
    //littleHero = LittleHero::create("kalakala-littlehero-left.png", 0);
    if (myPlayer->playerNumber == 0) {
        myLittleHero->setPosition(myPosition);
        enemyLittleHero->setPosition(enemyPosition);
    }
    else {
        myLittleHero->setPosition(enemyPosition);
        enemyLittleHero->setPosition(myPosition);
    }
    this->addChild(myLittleHero);
    this->addChild(enemyLittleHero);
}

void OnlineFightScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

void OnlineFightScene::update(float dt)
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
    updateWin(dt);
}

void OnlineFightScene::enableMouseListener()
{
    prepareSceneMouseListener = EventListenerMouse::create();
    prepareSceneMouseListener->onMouseDown = CC_CALLBACK_1(OnlineFightScene::fightSceneOnMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(prepareSceneMouseListener, this);
}

void OnlineFightScene::updateWin(float dt)
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
    if (cntEnemy == 0 || cntMy == 0) {
        // 创建一个Label
        std::string str = cntEnemy == 0 ? "You Win" : "Enemy Win";
        if (cntEnemy == 0)
            myLittleHero->attack(enemyLittleHero);
        else
            enemyLittleHero->attack(myLittleHero);
        auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 80); // 字体文件需要存在

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
        auto delay = cocos2d::DelayTime::create(2);

        auto callback = cocos2d::CallFunc::create([this]() {
            if (myLittleHero->percentage <= 0 || enemyLittleHero->percentage <= 0)
            {
                OnlineFightScene::goToGameOverScene();
            }
            else {
                OnlineFightScene::goToPrepareScene();
            }
            });

        auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);


        this->runAction(sequence);
        //Vector<MenuItem*> MenuItems_fight;
        ////回退
        //auto backItem = MenuItemImage::create(
        //    "backnormal.png",
        //    "backselected.png",
        //    CC_CALLBACK_1(FightScene::menuPlayCallback, this));

        //if (!(backItem == nullptr ||
        //    backItem->getContentSize().width <= 0 ||
        //    backItem->getContentSize().height <= 0))
        //{//退出菜单项有效，接下来会计算退出菜单项的位置
        //    float x = origin.x + visibleSize.width / 2;
        //    float y = origin.y + visibleSize.height / 7 * 3 - backItem->getContentSize().height * 20 / 13;
        //    backItem->setPosition(Vec2(x, y));
        //}
        //MenuItems_fight.pushBack(backItem);
        //auto menu = Menu::createWithArray(MenuItems_fight);//创建菜单
        //menu->setPosition(Vec2::ZERO);//将菜单的位置设置为(0, 0)，即左下角
        //this->addChild(menu, 2);//将菜单添加到当前的图层中，层级参数为1，表示将菜单放置在图层的最上方
    }


}

void OnlineFightScene::menuPlayCallback(Ref* pSender) {
    if (isAudioEnabled)
    {// 启用音效
        AudioManager::playEffect();
    }
    //把原数据删除再离开场景
    PlayerManager::getInstance()->getPlayer(0)->deletePast();
    PlayerManager::getInstance()->getPlayer(1)->deletePast();

    Director::getInstance()->popScene(); // 切换到playscene场景
}

void OnlineFightScene::goToPrepareScene()
{
    if (webSocket_ && webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        webSocket_->close();
    }
    auto prepareScene = OnlinePrepareScene::create();
    cocos2d::Director::getInstance()->replaceScene(prepareScene);
}

void OnlineFightScene::goToGameOverScene()
{
    // 创建新的场景
    if (webSocket_ && webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        webSocket_->close();
    }
    auto gameOverScene = GameOverScene::createScene();

    // 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(gameOverScene);
}
void OnlineFightScene::initWeb()
{
    webSocket_ = new cocos2d::network::WebSocket();
    webSocket_->init(*this, "ws://192.168.43.182:3000");
}
void OnlineFightScene::sendChessInfoToServer()
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
void OnlineFightScene::onOpen(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket connected");
}
void OnlineFightScene::onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data)
{
    //CCLOG("Received message: %s", data.bytes);
    std::string message(data.bytes, data.len);
    //std::string cleanMessage(message);
    CCLOG("Received message: %s", message.c_str());
    if (message == "Player1") {
        return;
    }
    if (message == "STARTGAME") {
        sendChessInfoToServer();
        return;
        //CCLOG("1");
    }
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
                gridMap->addChessToGrid(chess, gridMap->getCellAtPosition(Vec2(x, y)));
                chess->maxHP = chess->health;
                chess->initHealthBar();
                this->addChild(chess);
            }
            gridMap->updateForPlayer();
            this->schedule([this](float dt) {this->update(dt); }, "update_key");
        }
        if (document.HasMember("type") && document["type"].IsString() && document["type"] == "position_update") {
            // 确保 JSON 中有 x 和 y 属性
            if (document.HasMember("x") && document.HasMember("y") && document["x"].IsFloat() && document["y"].IsFloat()) {
                // 从 JSON 中读取属性并更新 LittleHero 的位置
                float x = document["x"].GetFloat();
                float y = document["y"].GetFloat();
                // 假设 LittleHero 有 setPosition 方法
                enemyLittleHero->stopAllActions();
                float speed = 500.0f;
                Vec2 currentposition = enemyLittleHero->getPosition();
                // 计算鼠标点击位置相对于当前位置的相对位移
                Vec2 targetposition = Vec2(x, y);
                Vec2 movedelta = targetposition - currentposition;
                float distance = movedelta.length();
                float duration = distance / speed;
                auto moveto = MoveTo::create(duration, targetposition);
                enemyLittleHero->runAction(moveto);
            }
        }
    }
}

void OnlineFightScene::onClose(cocos2d::network::WebSocket* ws)
{
    CCLOG("WebSocket closed");
}

void OnlineFightScene::onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error)
{
    CCLOG("WebSocket error: %d", static_cast<int>(error));
}

void OnlineFightScene::fightSceneOnMouseDown(Event* event)
{
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {

        myLittleHero->stopAllActions();
        // 创建一个MoveTo动作，移动到点击位置
        Vec2 currentPosition = myLittleHero->getPosition();

        // 计算鼠标点击位置相对于当前位置的相对位移
        Vec2 targetPosition = mouseEvent->getLocationInView();
        Vec2 moveDelta = targetPosition - currentPosition;

        float distance = moveDelta.length();

        // 计算匀速移动的时间（假设速度为300像素/秒）
        float speed = 300.0f;
        float duration = distance / speed;

        // 创建MoveBy动作，匀速移动到相对位移位置
        auto moveTo = MoveTo::create(duration, targetPosition);

        myLittleHero->runAction(moveTo);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

        doc.AddMember("type", "position_update", allocator);
        doc.AddMember("x", targetPosition.x, allocator);
        doc.AddMember("y", targetPosition.y, allocator);

        // 将 JSON 转为字符串
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::string message = buffer.GetString();

        // 发送消息给服务器
        if (webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN) {
            webSocket_->send(message);
        }
    }
}
