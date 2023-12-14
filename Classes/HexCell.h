#ifndef HEXCELL_H
#define HEXCELL_H

#include "cocos2d.h"
#include "Chess.h"
#define GRID_LENGTH 
USING_NS_CC;


class HexCell : public cocos2d::Node {
public:
    Sprite* hexSprite;

    bool isSelected;

    //棋格边长
    float length;
    //棋格宽度
    float width;
    //棋格高度
    float height;

    Vec2 coordinateInBoard;

    //棋盘上的棋子
    Chess* chessInGrid;

    HexCell* RightNode;//右棋格
    HexCell* RightUpNode;//右上棋格
    HexCell* RightDownNode;//右下棋格
    HexCell* LeftDownNode;//左下棋格
    HexCell* LeftNode;//左棋格
    HexCell* LeftUpNode;//左上棋格

    //该棋格中的棋子。
    Vector<Chess*> chessedInThisNode;

    //寻路用，在到达该棋格前所在的棋格
    HexCell* preNode;
private:

public:


    static HexCell* create();
    //单个棋格的初始化
    virtual bool init() override;

    void turnToSelected();

    void turnToNormal();

    Vector<HexCell*> GetNeighbors();

    //棋子类型替换
    bool CanPass(Chess* InActor) const;

    void EnterNode(Chess* InActor);

    void BookNode(Chess* InActor);

    void CancelBookNode(Chess* InActor);

    void LeaveNode(Chess* InActor);

};

#endif // HEXCELL_H
