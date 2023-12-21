// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "HexGrid.h"
#include "LittleHero.h"
#include "network/SocketIO.h"
USING_NS_CC;
class PrepareScene : public cocos2d::Scene
{
public:
    Sprite* backgroundImg;
    HexGrid* hexGrid;
public:
    // ���������ľ�̬����
    static cocos2d::Scene* createScene();
    

    // ��ʼ�������ķ���
    virtual bool init();
    // ��������ͼƬ
    void initBackground();
    // �������
    void inithexGrid();
    // ʵ�� "static create()" ���������ڴ�������
    CREATE_FUNC(PrepareScene);
    void onMouseDown(cocos2d::Event* event);
    void onMouseMove(Event* event);
    void initClock();
    void switchToNextScene(float dt);
private:
    int countdownSeconds = 10;
    LittleHero* littleHero;
    LittleHero* enemy;
    std::chrono::high_resolution_clock::time_point lastRightClickTime;
    const double doubleClickThreshold = 500;
    float lastAttackTime = 0;
};

#endif // __PREPARE_SCENE_H__
