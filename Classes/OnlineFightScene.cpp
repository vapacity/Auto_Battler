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

bool OnlineFightScene::init()
{
    // 首先调用基类的init方法
    if (!Scene::init())
    {
        return false;
    }
    //切换音乐
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("battleMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);

    initPlayer();
    initBackground();
    initWeb();
    initGridMap();
    //initPreparationSeats();
    initLittleHero();
    //initStore();
    enableMouseListener();
    gridMap->disableMouseListener();

}

void OnlineFightScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);//获取我方玩家信息
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);//敌方
    enemyPlayer->convertToEnemy();//敌方位置要反转
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
    //初始化两方小小英雄
    myLittleHero = myPlayer->myHero;
    if (myLittleHero->getParent())
        myLittleHero->removeFromParent();
    myLittleHero->isAnimationPlaying = false;
    enemyLittleHero = enemyPlayer->myHero;
    if (enemyLittleHero->getParent())
        enemyLittleHero->removeFromParent();
    enemyLittleHero->setColor(Color3B(180, 180, 180));
    enemyLittleHero->isAnimationPlaying = false;

    //根据编号确定位置
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
    enemyLittleHero->disableMoving();
}

void OnlineFightScene::initStore()
{
    store = Store::create(myPlayer->myStore);
    this->addChild(store, 2);
}

//提取出我方棋盘上的棋子，依次更新状态，判断是否决出胜负
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
            {//有一方死了，结束游戏
                OnlineFightScene::goToGameOverScene();
            }
            else {//没死继续
                OnlineFightScene::goToPrepareScene();
            }
            });

        auto sequence = cocos2d::Sequence::create(delay, callback, nullptr);


        this->runAction(sequence);
        
    }


}


void OnlineFightScene::goToPrepareScene()
{
    if (webSocket_ && webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        webSocket_->close();
    }
    //切换音乐
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("prepareMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);

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
    //停止音乐
    experimental::AudioEngine::stop(globalAudioId);
    // 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(gameOverScene);
}
void OnlineFightScene::initWeb()
{
    webSocket_ = new cocos2d::network::WebSocket();
    webSocket_->init(*this, "ws://192.168.43.182:3000");
}

//棋子信息发送到服务器
void OnlineFightScene::sendChessInfoToServer()
{
    //创建JSON 文档
    rapidjson::Document document;
    document.SetObject();

    // 创建数组，用于存储棋子信息
    rapidjson::Value chessArray(rapidjson::kArrayType);

    // 遍历棋子数组，将信息存储到 JSON 数组中
    for (const auto& Node : myPlayer->myChessMap) {
        rapidjson::Value chessObject(rapidjson::kObjectType);
        auto chess = Node.second;//棋子
        auto location = Node.first;//位置
        //添加id，星级，位置，玩家编号成员
        chessObject.AddMember("id", chess->getId(), document.GetAllocator());
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
    //将消息数据转换为字符串
    std::string message(data.bytes, data.len);
    CCLOG("Received message: %s", message.c_str());

    if (message == "Player1") {
        return;
    }
    if (message == "STARTGAME") {//开始游戏，把玩家的棋子信息发送给服务器
        sendChessInfoToServer();
        return;
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

                // 获取对手棋子信息
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
        // JSON 数据中存在 "type" 键且对应值为字符串 "position_update"，位置更新
        if (document.HasMember("type") && document["type"].IsString() && document["type"] == "position_update") {
            // 确保 JSON 中有 x 和 y 属性
            if (document.HasMember("x") && document.HasMember("y") && document["x"].IsFloat() && document["y"].IsFloat()) {
                // 从 JSON 中读取属性并更新 LittleHero 的位置
                float x = document["x"].GetFloat();
                float y = document["y"].GetFloat();

                // 小小英雄移动
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
    //右键控制小小英雄
    if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {

        myLittleHero->stopAllActions();

        // 创建一个MoveTo动作，移动到点击位置
        // 计算鼠标点击位置相对于当前位置的相对位移
        Vec2 currentPosition = myLittleHero->getPosition();
        Vec2 targetPosition = mouseEvent->getLocationInView();
        Vec2 moveDelta = targetPosition - currentPosition;
        float distance = moveDelta.length();

        // 计算匀速移动的时间（假设速度为300像素/秒）
        float speed = 300.0f;
        float duration = distance / speed;

        // 创建动作，匀速移动到相对位移位置
        auto moveTo = MoveTo::create(duration, targetPosition);
        myLittleHero->runAction(moveTo);

        //创建 JSON 数据表示位置更新
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
