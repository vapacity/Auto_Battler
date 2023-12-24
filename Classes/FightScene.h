#ifndef __FIGHT_SCENE_H__
#define __FIGHT_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "PlayerManager.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "Store.h"
#include "LittleHero.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/WebSocket.h"
USING_NS_CC;

class FightScene :public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate
{
public:
    Player* myPlayer = PlayerManager::getInstance()->getPlayer(0);
    Player* enemyPlayer = PlayerManager::getInstance()->getPlayer(0);

    Sprite* backgroundImg;//����ͼƬ
    GridMap* gridMap;//����
    //Chess* selectedChess;
    //EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;//��սϯ
    Store* store;//�̵�
    LittleHero* myLittleHero;//�ҷ�ССӢ��
    LittleHero* enemyLittleHero;//�з�ССӢ�ۣ�����о�����Ҫ

    Vector<FiniteTimeAction*> actions;
    cocos2d::network::WebSocket* webSocket_;
    int test = 0;
public:
    // ���������ľ�̬����
    FightScene();
    ~FightScene();
    void sendChessInfoToServer();
    static cocos2d::Scene* createScene();

    // ��ʼ�������ķ���
    virtual bool init() override;

    //�������
    void initPlayer();

    //��ӱ���ͼƬ
    void initBackground();

    // �������
    void initGridMap();

    //������սϯ
    void initPreparationSeats();

    //����ССӢ��
    void initLittleHero();

    //�����̵�
    void initStore();

    //������������
    void initChessExp();

    //�����ƶ�����
    void moveChess(Chess* chessToMove, bool& stopMoveFlag);

    //�����ж��Ƿ��е��˽����˹�����Χ
    bool judgeAttack(Vector<HexCell*> movePath);

    //һ������������֮���˳�ѭ��
    bool judgeAllDead();

    //�������ϵ��������ӱ�������ʼ���У�ֱ���е��˽����˹�����Χ
    void findEnemyAndMove();

    //�������ϵ����ӽ��б������Ѿ�������ƶ����ж��Լ���Χ�Ƿ��е��ˣ������򴥷�attack
    void locatdEnemyAndAttack(Chess* chess);

    //��ս��������ÿ֡����
    void initWeb();
    void onOpen(cocos2d::network::WebSocket* ws);
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    void onClose(cocos2d::network::WebSocket* ws);
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    void update(float dt);
    void updateDead(float dt);
    void updateWin(float dt);
    CREATE_FUNC(FightScene);

};
#endif


