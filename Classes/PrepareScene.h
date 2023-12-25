// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "PlayerManager.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "Store.h"
#include "LittleHero.h"
#include "FightScene.h"
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
    //����˿����޲������ʾ������һ��ʱ����Զ��Ƴ�
    void noPopulationText();
    float elapsedTime = 0.0f;
    Label* fadingText;
    //noPopulationText�ĵ������ã�ʹ��ʾ�𽥵���
    void updateText(float dt);

    // ���������ľ�̬����
    static cocos2d::Scene* createScene();

    // ��ʼ�������ķ���
    virtual bool init();
    //��ʼ����ɫ
    void initPlayer();

    //��ʼ��ai
    void initEnemyAi();


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

    //������������ӷ��õ������ϣ�ʵ����
    void putChessOnGrids();
    //������������ӷ��õ���սϯ��
    void putChessOnSeats();

    //�����Ǽ��������Ϣ�ĺ���
    //������������
    void enableMouseListener();

    //������������
    void disableMouseListener();

    //�˲���Ϊ׼�������µ�ר�ú���
    //����������
    void prepareSceneOnMouseDown(Event* event);
    void prepareSceneOnMouseMove(Event* event);
    void prepareSceneOnMouseUp(Event* event);

    //����קchess���prepareScene�����������
    void chessOnMouseDown(Vec2 mousePosition);
    void chessOnMouseMove(Vec2 mousePosition);
    void chessOnMouseUp(Vec2 mousePosition);

    //�������һ���ϳ�
    void checkAndMerge(Chess* chess);
    Chess* upgradeChess(int Id, int star);

    //����ս������
    void goToFightScene(float dt);
    CREATE_FUNC(PrepareScene);
};

#endif // __PREPARE_SCENE_H__
