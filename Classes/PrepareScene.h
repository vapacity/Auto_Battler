// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "StoreLayer.h"
#include "LittleHero.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Sprite* backgroundImg;
    GridMap* gridMap;
    Chess* selectedChess;
    EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;
    StoreLayer* store;
    LittleHero* littleHero;
    LittleHero* littleHeroEnemy;
public:
    // ���������ľ�̬����
    static cocos2d::Scene* createScene();
    
    // ��ʼ�������ķ���
    virtual bool init();

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

    // ʵ�� "static create()" ���������ڴ�������
    CREATE_FUNC(PrepareScene);

};

#endif // __PREPARE_SCENE_H__
