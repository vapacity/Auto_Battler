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
    
    //��ʼ�������������
    virtual bool init();

    std::map<Vec2, HexCell*, Vec2Compare>nodeMap;

    bool isInBoard(Vec2 coor);

    //�����Ϸ������Vec2����Ӧ�ĸ��ӣ�����Ϊ�����������������ĸ������ģ�
    HexCell* mouseInWhichCell(const cocos2d::Vec2& position);

    //void onMouseDown(Event* event);

    void selectGrid(Event* event);

    // ���ú��������������ķ���
    void disableMouseListener();
    void enableMouseListener();

    //Ѱ·�㷨
    bool FindPath(Vector<HexCell*>& Path, Chess* InActor, HexCell* FromNode, HexCell* ToNode, int StopSteps = 0);

    Vector<HexCell*> GetNodeNeighbors(HexCell* inNode, int stepRange);

    //���һ�����ӵ������
    void addChessToGrid(Chess* chess, HexCell* cell);

    //������������ϵ�����
    static void swapChessOnGrids(HexCell* cella, HexCell* cellb);
};

#endif // HEXGRID_H
