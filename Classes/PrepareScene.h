// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "storeLayer.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Sprite* backgroundImg;
    GridMap* gridMap;
    Chess* selectedChess;
    EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;
    storeLayer* store;
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

    //������������
    void initChessExp();

    //�����̵�
    void initStore();

    //�����Ǽ��������Ϣ�ĺ���
    //������������
    void enableMouseListener();

    //������������
    void disableMouseListener();

  
    void prepareSceneOnMouseDown(Event* event);
    void prepareSceneOnMouseMove(Event* event);
    void prepareSceneOnMouseUp(Event* event);

    // ʵ�� "static create()" ���������ڴ�������
    CREATE_FUNC(PrepareScene);

};

#endif // __PREPARE_SCENE_H__
