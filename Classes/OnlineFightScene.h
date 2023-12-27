#ifndef __ONLINE_FIGHT_SCENE_H__
#define __ONLINE_FIGHT_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "PlayerManager.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "Store.h"
#include "LittleHero.h"
#include "AudioManager.h"
#include "PrepareScene.h"
#include "GameOverScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/WebSocket.h"
#include "OnlinePrepareScene.h"

USING_NS_CC;

class OnlineFightScene :public cocos2d::Scene, public cocos2d::network::WebSocket::Delegate
{
public:
    Player* myPlayer;
    Player* enemyPlayer;

    Sprite* backgroundImg;//����ͼƬ
    GridMap* gridMap;//����
    //Chess* selectedChess;
    //EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;//��սϯ
    Store* store;//�̵�
    LittleHero* myLittleHero;//�ҷ�ССӢ��
    LittleHero* enemyLittleHero;//�з�ССӢ�ۣ�����о�����Ҫ

    Vector<FiniteTimeAction*> actions;
public:
    // ���������ľ�̬����
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
    void createChessOnGrids();

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
    void update(float dt);

    void menuPlayCallback(Ref* pSender);
    void updateDead(float dt);
    void updateWin(float dt);
    void goToPrepareScene();
    void goToGameOverScene();
    void initWeb();
    void sendChessInfoToServer();
    void onOpen(cocos2d::network::WebSocket* ws);
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    void onClose(cocos2d::network::WebSocket* ws);
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    //void update(float dt);
    CREATE_FUNC(OnlineFightScene);
private:
    cocos2d::network::WebSocket* webSocket_;
};
#endif