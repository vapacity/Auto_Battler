#ifndef HEXCELL_H
#define HEXCELL_H

#include "cocos2d.h"
#include "Chess.h"
USING_NS_CC;

class HexCell : public cocos2d::Node {
public:
    Sprite* hexSprite;

    bool isSelected;//被选中

    //棋格边长
    float length;
    //棋格宽度
    float width;
    //棋格高度
    float height;

    Vec2 coordinateInBoard;//棋格的棋盘相对坐标

    //棋盘上的棋子
    Chess* chessInGrid;

    HexCell* RightNode;//右棋格
    HexCell* RightUpNode;//右上棋格
    HexCell* RightDownNode;//右下棋格
    HexCell* LeftDownNode;//左下棋格
    HexCell* LeftNode;//左棋格
    HexCell* LeftUpNode;//左上棋格

    //该棋格中的棋子。
    //棋子类型替换
    Vector<Chess*> chessedInThisNode;

    //寻路用，在到达该棋格前所在的棋格
    HexCell* preNode;

    //该棋格是否是我方棋格
    bool isMine=false;

    //该棋格是否被预定为移动目标了
    bool isBooked = false;
private:

public:


    static HexCell* create();
    //单个棋格的初始化
    virtual bool init() override;

    void turnToSelected();//选中

    void turnToNormal();//未选中

    void turnToSeen();//路过
    Vector<HexCell*> GetNeighbors();//获取所有存在的相邻棋格

    //棋子是否可以通行棋格
    bool CanPass(Chess* InActor) const;



};

#endif // HEXCELL_H
