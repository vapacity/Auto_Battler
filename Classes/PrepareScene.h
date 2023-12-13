// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "HexGrid.h"
#include "Chess.h"
#include "LittleHero.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    //02
    Sprite* backgroundImg;
    HexGrid* hexGrid;
    //03
    LittleHero* littleHero;
    //04
    Chess* selectedChess;//���ڱ�ʾ����ק�����б�ѡ�е�����
    std::vector<Chess*> chessSet;

public:
    // ���������ľ�̬����
    static cocos2d::Scene* createScene();
    
    // ��ʼ�������ķ���
    virtual bool init();

    // ��������ͼƬ
    void initBackground();

    void initLittleHero();
    // �������
    void inithexGrid();

    //������������
    void initChessExp();
    void initStoreLayer();
    //��onMouseMove������ʵ��Grids͸���ȱ仯
    void moveOnGrids(Vec2 mousePosition);
    void moveOnChess(Vec2 mousePosition);
    // ʵ�� "static create()" ���������ڴ�������
    CREATE_FUNC(PrepareScene);

    //�����Ǽ��������Ϣ�ĺ���
    void onMouseDown(Event* event);
    void onMouseMove(Event* event);
    void onMouseUp(Event* event);
};

#endif // __PREPARE_SCENE_H__
