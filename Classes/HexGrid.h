#ifndef HEXGRID_H
#define HEXGRID_H

#include "cocos2d.h"
#include "HexCell.h"

USING_NS_CC;
class HexGrid : public cocos2d::Node {
public:
    std::vector<HexCell*> GridMap;
    float Limitx;//x轴最远格子的x坐标
    float Limity;//y轴最远格子的y坐标
public:
    static HexGrid* create(int Inline,int Incol);
    
    //初始化棋格，行数列数
    virtual bool initWithSize(int Inline,int Incol);

    //获得游戏中坐标Vec2处对应的格子（方法为遍历查找与鼠标最靠近的格子中心）
    HexCell* getCellAt(const cocos2d::Vec2& position);

    //交换两个棋格上的棋子
    static void swapChessOnGrids(HexCell* cella, HexCell* cellb);
};

#endif // HEXGRID_H
