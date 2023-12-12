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
    Chess* selectedChess;//用于表示在拖拽过程中被选中的棋子
    std::vector<Chess*> chessSet;

public:
    // 创建场景的静态方法
    static cocos2d::Scene* createScene();
    
    // 初始化场景的方法
    virtual bool init();

    // 创建背景图片
    void initBackground();

    void initLittleHero();
    // 创建棋格
    void inithexGrid();

    //创建棋子样例
    void initChessExp();
    void initStoreLayer();
    //在onMouseMove函数中实现Grids透明度变化
    void moveOnGrids(Vec2 mousePosition);
    void moveOnChess(Vec2 mousePosition);
    // 实现 "static create()" 方法，用于创建对象
    CREATE_FUNC(PrepareScene);

    //以下是监听鼠标信息的函数
    void onMouseDown(Event* event);
    void onMouseMove(Event* event);
    void onMouseUp(Event* event);
};

#endif // __PREPARE_SCENE_H__
