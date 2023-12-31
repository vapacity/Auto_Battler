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

    //��������
    void createChessOnGrids();

    //��ս��������ÿ֡����
    void update(float dt);

    void enableMouseListener();

    //�ж��������
    void updateWin(float dt);

    //�ص�׼������
    void goToPrepareScene();

    //��Ϸ��������
    void goToGameOverScene();

    //��ʼ��WebSocket����
    void initWeb();

    //����������Ϣ��������
    void sendChessInfoToServer();

    //����WebSocket���Ӵ�ʱ���¼�
    void onOpen(cocos2d::network::WebSocket* ws);

    //������յ�WebSocket��Ϣʱ���¼�
    void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    
    //����WebSocket���ӹر�ʱ���¼�
    void onClose(cocos2d::network::WebSocket* ws);
    
    //����WebSocket����ʱ���¼�
    void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    
    //����ս��������������¼�
    void fightSceneOnMouseDown(Event* event);
    
    CREATE_FUNC(OnlineFightScene);
private:
    
    cocos2d::network::WebSocket* webSocket_;//�洢WebSocket���ӵ�ָ��
   
    EventListenerMouse* prepareSceneMouseListener;//�洢����¼���������ָ��
};
#endif