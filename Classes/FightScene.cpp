#include "FightScene.h"

FightScene::FightScene()
{
    webSocket_ = new cocos2d::network::WebSocket();
    webSocket_->init(*this, "ws://100.81.177.2:3000"); // �滻Ϊ��ķ�������ַ�Ͷ˿ں�
}

FightScene::~FightScene()
{
    webSocket_->close();
}

void FightScene::sendChessInfoToServer()
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

cocos2d::Scene* FightScene::createScene()
{
    // ����һ���������󣬸ö������Զ��ͷų��Զ��ͷ�
    auto scene = FightScene::create();
    return scene;
}
FiniteTimeAction* createSequenceFromVector(const Vector<FiniteTimeAction*>& actions, int index) {
    if (index >= actions.size() - 1) {
        // ���ֻʣһ��������û�ж�����ֱ�ӷ��ظö����� nullptr
        return index < actions.size() ? actions.at(index) : nullptr;
    }
    else {
        // �ݹ�ش�������
        // ȷ����ǰ������ݹ鷵�صĶ���˳����ȷ
        auto nextAction = createSequenceFromVector(actions, index + 1);
        return Sequence::createWithTwoActions(actions.at(index), nextAction);
    }
}

bool FightScene::init()
{
    // ���ȵ��û����init����
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
    //���ڲ���ͬʱ��������
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
    //�˴���Ҫһ������ط����̵Ĳ�������
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
    //webSocket_->init(*this, "ws://100.81.177.2:3000"); // �滻Ϊ��ķ�������ַ�Ͷ˿ں�
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
    //            //���˵�ʱ�򣬾��������ƶ��������ڹ�������Ҫֱ��ͣ��
    //            this->stopAllActions();
    //        }
    //        // ���������߼�
    //        auto fadeOut = FadeOut::create(0.1f);//�ص�������Ŀ������˺�
    //        runAction(fadeOut);
    //        gridMap->removeChessOfGrid(gridMap->getCellAtPosition(chess->atGridPosition));//���ܷ��ڻص������У���Ϊ����������Ҫֱ������
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
        // ����һ��Label
        auto label = Label::createWithTTF("You Win", "fonts/Marker Felt.ttf", 80); // �����ļ���Ҫ����

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
    }
    else if (cntMy == 0) {
        // ����һ��Label
        auto label = Label::createWithTTF("Enemy Win", "fonts/Marker Felt.ttf", 80); // �����ļ���Ҫ����

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
    }
}

