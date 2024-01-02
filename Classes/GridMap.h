#ifndef GRIDMAP_H
#define GRIDMAP_H

#include "cocos2d.h"
#include "HexCell.h"
#include "Chess.h"
#include <algorithm>
#include "map"

#define NUM_COLUMN 14//棋盘列数
#define NUM_LINE 8//行数

class Vec2Compare {
public:
    //比较两个棋格的前后顺序
    bool operator()(const Vec2& v1, const Vec2& v2) const {
        return (v1.x < v2.x) || (v1.x == v2.x && v1.y < v2.y);
    }
};

class GridMap : public cocos2d::Node {
private:
    HexCell* lastCell = nullptr;//上一个选中的棋格
public:
    int chessAmount=0;//记录棋子总数

    EventListenerMouse* mouseListener;

    std::map<Vec2, HexCell*, Vec2Compare>nodeMap;

    std::map<Vec2, Chess*, Vec2Compare>myChessMap;
public:
    //根据棋手信息更新显示
    void updateForPlayer();
    // 启动或停止 schedule
    void selectSchedule(bool select);

    //创建棋盘
    static GridMap* create(std::map<Vec2, Chess*, Vec2Compare>myChessMap);

    //初始化棋格，行数列数
    virtual bool init(std::map<Vec2, Chess*, Vec2Compare>myChessMap);

    //是否在棋盘范围
    bool isInBoard(Vec2 coor)const;

    //获得游戏中坐标Vec2处对应的格子（方法为遍历查找与鼠标最靠近的格子中心）
    HexCell* mouseInWhichCell(const cocos2d::Vec2& position);

    //选中棋格高亮显示
    void selectGrid(Event* event);

    // 禁用和启用鼠标监听器的方法
    void disableMouseListener();
    void enableMouseListener();

    //寻路算法
    bool FindPath(Vector<HexCell*>& Path, Chess* InActor, HexCell* FromNode, HexCell* ToNode, int StopSteps = 0);

    //
    HexCell* FindBattle(Chess* InActor, HexCell* FromNode);

    //获取一定步数范围内的所有相邻棋格
    Vector<HexCell*> GetNodeNeighbors(HexCell* inNode, int stepRange);

    //添加一个棋子到棋格上
    void addChessToGrid(Chess* chess, HexCell* cell);

    //将一个棋格上的棋子去掉
    void removeChessOfGrid(HexCell* Incell);

    //传入一个Vec2值，返回对应的HexCell*
    HexCell* getCellAtPosition(Vec2 position);
};

#endif // HEXGRID_H
