#include "OnlineFightScene.h"
#include "FightScene.h"
#define enemyPosition Vec2(1050,650)
#define myPosition Vec2(40,265)
cocos2d::Scene* OnlineFightScene::createScene()
{ 
    // ����һ���������󣬸ö������Զ��ͷų��Զ��ͷ�
    auto scene = OnlineFightScene::create();
    return scene;
}

bool OnlineFightScene::init()
{
    // ���ȵ��û����init����
    if (!Scene::init())
    {
        return false;
    }
    //�л�����
    experimental::AudioEngine::stop(globalAudioId);
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("battleMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);

    initPlayer();
    initBackground();
    initWeb();
    initGridMap();
    initPreparationSeats();
    initLittleHero();
    initStore();
    enableMouseListener();
    gridMap->disableMouseListener();

}

void OnlineFightScene::initPlayer()
{
    myPlayer = PlayerManager::getInstance()->getPlayer(0);//��ȡ�ҷ������Ϣ
    enemyPlayer = PlayerManager::getInstance()->getPlayer(1);//�з�
    enemyPlayer->convertToEnemy();//�з�λ��Ҫ��ת
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
    //��ʼ������ССӢ��
    myLittleHero = myPlayer->myHero;
    if (myLittleHero->getParent())
        myLittleHero->removeFromParent();
    myLittleHero->isAnimationPlaying = false;
    enemyLittleHero = enemyPlayer->myHero;
    if (enemyLittleHero->getParent())
        enemyLittleHero->removeFromParent();
    enemyLittleHero->setColor(Color3B(180, 180, 180));
    enemyLittleHero->isAnimationPlaying = false;

    //���ݱ��ȷ��λ��
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

//��ȡ���ҷ������ϵ����ӣ����θ���״̬���ж��Ƿ����ʤ��
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
        // ����һ��Label
        std::string str = cntEnemy == 0 ? "You Win" : "Enemy Win";
        if (cntEnemy == 0)
            myLittleHero->attack(enemyLittleHero);
        else
            enemyLittleHero->attack(myLittleHero);
        auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 80); // �����ļ���Ҫ����

        // ����Label����ɫ����ѡ��
        label->setColor(Color3B::WHITE);

        // ��ȡ�����ĳߴ����������
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        Vec2 centerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // ����Label��λ��
        label->setPosition(centerPosition);

        // ��Label��ӵ���ǰ����
        this->addChild(label, 2); // �ڶ���������z-order�����Ը�����Ҫ����
        auto delay = cocos2d::DelayTime::create(2);

        auto callback = cocos2d::CallFunc::create([this]() {
            if (myLittleHero->percentage <= 0 || enemyLittleHero->percentage <= 0)
            {//��һ�����ˣ�������Ϸ
                OnlineFightScene::goToGameOverScene();
            }
            else {//û������
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
    //�л�����
    globalAudioId = cocos2d::experimental::AudioEngine::play2d("prepareMusic.mp3", true);
    experimental::AudioEngine::setVolume(globalAudioId, UserDefault::getInstance()->getFloatForKey("backGroundMusicVolumn", 50) / 100.0f);

    auto prepareScene = OnlinePrepareScene::create();
    cocos2d::Director::getInstance()->replaceScene(prepareScene);
}

void OnlineFightScene::goToGameOverScene()
{
    // �����µĳ���
    if (webSocket_ && webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        webSocket_->close();
    }
    auto gameOverScene = GameOverScene::createScene();
    //ֹͣ����
    experimental::AudioEngine::stop(globalAudioId);
    // �л����³���
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

    // �������飬���ڴ洢������Ϣ
    rapidjson::Value chessArray(rapidjson::kArrayType);

    // �����������飬����Ϣ�洢�� JSON ������
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

    // �� JSON ������ӵ� JSON �ĵ���
    document.AddMember("chessArray", chessArray, document.GetAllocator());

    // �� JSON �ĵ�ת��Ϊ�ַ���
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // �� JSON �ַ������͵�������
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
    // ��������� JSON ���ݣ���������״̬��
    rapidjson::Document document;
    document.Parse(message.c_str());
    if (!document.HasParseError() && document.IsObject()) {
        // ����Ƿ���� chessArray ��
        if (document.HasMember("chessArray") && document["chessArray"].IsArray()) {
            const rapidjson::Value& chessArray = document["chessArray"];
            for (rapidjson::SizeType i = 0; i < chessArray.Size(); i++) {
                const rapidjson::Value& chessObject = chessArray[i];

                // ��ȡ������Ϣ
                int id = chessObject["id"].GetInt();
                int star = chessObject["star"].GetInt();
                float x = chessObject["x"].GetFloat();
                float y = chessObject["y"].GetFloat();
                int enemyplayerNumber = chessObject["playerNumber"].GetInt();
                auto chess = Chess::createByIdAndStar(id, star);
                chess->playerNumber = enemyplayerNumber;
                //Ϊ���ӽǱ�������0��player�����ӽ�
                gridMap->addChessToGrid(chess, gridMap->getCellAtPosition(Vec2(x, y)));
                chess->maxHP = chess->health;
                chess->initHealthBar();
                this->addChild(chess);
            }
            gridMap->updateForPlayer();
            this->schedule([this](float dt) {this->update(dt); }, "update_key");
        }
        if (document.HasMember("type") && document["type"].IsString() && document["type"] == "position_update") {
            // ȷ�� JSON ���� x �� y ����
            if (document.HasMember("x") && document.HasMember("y") && document["x"].IsFloat() && document["y"].IsFloat()) {
                // �� JSON �ж�ȡ���Բ����� LittleHero ��λ��
                float x = document["x"].GetFloat();
                float y = document["y"].GetFloat();
                // ���� LittleHero �� setPosition ����
                enemyLittleHero->stopAllActions();
                float speed = 500.0f;
                Vec2 currentposition = enemyLittleHero->getPosition();
                // ���������λ������ڵ�ǰλ�õ����λ��
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
        // ����һ��MoveTo�������ƶ������λ��
        Vec2 currentPosition = myLittleHero->getPosition();

        // ���������λ������ڵ�ǰλ�õ����λ��
        Vec2 targetPosition = mouseEvent->getLocationInView();
        Vec2 moveDelta = targetPosition - currentPosition;

        float distance = moveDelta.length();

        // ���������ƶ���ʱ�䣨�����ٶ�Ϊ300����/�룩
        float speed = 300.0f;
        float duration = distance / speed;

        // ����MoveBy�����������ƶ������λ��λ��
        auto moveTo = MoveTo::create(duration, targetPosition);

        myLittleHero->runAction(moveTo);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

        doc.AddMember("type", "position_update", allocator);
        doc.AddMember("x", targetPosition.x, allocator);
        doc.AddMember("y", targetPosition.y, allocator);

        // �� JSON תΪ�ַ���
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::string message = buffer.GetString();

        // ������Ϣ��������
        if (webSocket_->getReadyState() == cocos2d::network::WebSocket::State::OPEN) {
            webSocket_->send(message);
        }
    }
}
