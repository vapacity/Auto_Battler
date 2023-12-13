#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "cocos2d.h"
#include "HexCell.h"
#include "Chess.h"
#include <algorithm>
#include "map"

#define NUM_COLUMN 14
#define NUM_LINE 8

class Vec2Compare {
public:
    bool operator()(const Vec2& v1, const Vec2& v2) const {
        return (v1.x < v2.x) || (v1.x == v2.x && v1.y < v2.y);
    }
};

class GridMap : public cocos2d::Node {
public:

    EventListenerMouse* mouseListener;

    //int num;
    //HexCell* a;
    //HexCell* b;
public:
    static GridMap* create();
    
    //初始化棋格，行数列数
    virtual bool init();

    std::map<Vec2, HexCell*, Vec2Compare>nodeMap;

    bool isInBoard(Vec2 coor);

    //获得游戏中坐标Vec2处对应的格子（方法为遍历查找与鼠标最靠近的格子中心）
    HexCell* mouseInWhichCell(const cocos2d::Vec2& position);

    //void onMouseDown(Event* event);

    void selectGrid(Event* event);

    // 禁用和启用鼠标监听器的方法
    void disableMouseListener();
    void enableMouseListener();

    //寻路算法
    bool FindPath(Vector<HexCell*>& Path, Chess* InActor, HexCell* FromNode, HexCell* ToNode, int StopSteps = 0);

    Vector<HexCell*> GetNodeNeighbors(HexCell* inNode, int stepRange);

    //添加一个棋子到棋格上
    void addChessToGrid(Chess* chess, HexCell* cell);

    //交换两个棋格上的棋子
    static void swapChessOnGrids(HexCell* cella, HexCell* cellb);
};

#endif // HEXGRID_H
