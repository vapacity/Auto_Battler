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
#include "AudioManager.h"
#include "PrepareScene.h"
#include "GameOverScene.h"
USING_NS_CC;

class FightScene :public cocos2d::Scene
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

   //���������ϵ�����
    void createChessOnGrids();


    //��ս��������ÿ֡����
    void update(float dt);

    //�ж��������
    void updateWin(float dt);

    //�ص�׼������
    void goToPrepareScene();

    //��Ϸ��������
    void goToGameOverScene();
    CREATE_FUNC(FightScene);

};
#endif