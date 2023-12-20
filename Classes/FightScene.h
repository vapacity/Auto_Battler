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
USING_NS_CC;

class FightScene:public cocos2d::Scene
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
    CREATE_FUNC(FightScene);

};
#endif