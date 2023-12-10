// PrepareScene.h

#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "HexGrid.h"
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

    void onMouseMove(Event* event);
};

#endif // __PREPARE_SCENE_H__
