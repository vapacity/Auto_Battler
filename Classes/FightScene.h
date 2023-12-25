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
#include "PrepareScene.h"
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

    //������������
    void initChessExp();

    //�������ϴ����ҷ��ͶԷ������ӣ����ǵ���ʵ�������Ǵ����µģ�
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

    void updateDead(float dt);
    void updateWin(float dt);
    void goToPrepareScene();
    CREATE_FUNC(FightScene);

};
#endif