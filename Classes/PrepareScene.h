// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "Store.h"
#include "LittleHero.h"
#include "Player.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Player* myPlayer;

    Sprite* backgroundImg;
    GridMap* gridMap;
    Chess* selectedChess;
    EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;
    Store* store;
    LittleHero* littleHero;
    LittleHero* littleHeroEnemy;
public:
    // ���������ľ�̬����
    cocos2d::Scene* createScene(Player* myPlayer);
    
    static PrepareScene* create(Player* myPlayer);

    // ��ʼ�������ķ���
    virtual bool init(Player* myPlayer);

    //��ʼ���������
    void initPlayer(Player* player);

    //��ӱ���ͼƬ
    void initBackground();

    // �������
    void initGridMap();

    //������սϯ
    void initPreparationSeats();

    //����ССӢ��
    void initLittleHero();

    //������������
    void initChessExp();

    //�����̵�
    void initStore();

    //�����Ǽ��������Ϣ�ĺ���
    //������������
    void enableMouseListener();

    //������������
    void disableMouseListener();

    //����������
    void prepareSceneOnMouseDown(Event* event);
    void prepareSceneOnMouseMove(Event* event);
    void prepareSceneOnMouseUp(Event* event);

    //����קchess���prepareScene�����������
    void chessOnMouseDown(Vec2 mousePosition);
    void chessOnMouseMove(Vec2 mousePosition);
    void chessOnMouseUp(Vec2 mousePosition);



};

#endif // __PREPARE_SCENE_H__
