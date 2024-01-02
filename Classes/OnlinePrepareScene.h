

#ifndef __ONLINE_PREPARE_SCENE_H__
#define __ONLINE_PREPARE_SCENE_H__

#include "cocos2d.h"
#include "GridMap.h"
#include "PlayerManager.h"
#include "Chess.h"
#include "ChessFactory.h"
#include "PreparationSeats.h"
#include "Store.h"
#include "LittleHero.h"
#include "OnlineFightScene.h"
USING_NS_CC;
class OnlinePrepareScene: public cocos2d::Scene
{
public:
    Player* myPlayer;
    Player* enemyPlayer;
    Sprite* backgroundImg;
    GridMap* gridMap;
    Chess* selectedChess;
    EventListenerMouse* prepareSceneMouseListener;
    PreparationSeats* preSeats;
    Store* store;
    LittleHero* littleHero;
    LittleHero* littleHeroEnemy;

    // ����ʱ���
    DrawNode* countdownLine;
    Label* countdownLabel;
    float remainingTime;
public:
    float elapsedTime = 0.0f;
    Label* fadingText;
    //��ӡ��ʾ
    void createText(const std::string& textContent);
    void updateText(float dt);

    // ���������ľ�̬����
    static cocos2d::Scene* createScene();

    // ��ʼ�������ķ���
    virtual bool init();

    //���˰�ť
    void initBack();

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

    //����ʱ�������
    void initPrepareLabel();

    void putChessOnGrids();

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
    CREATE_FUNC(OnlinePrepareScene);

    void menuPlayCallback(Ref* pSender);

    //����ʱ
    void updateCountdownLabel(float dt);


};

#endif // __PREPARE_SCENE_H__
