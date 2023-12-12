#ifndef HEXCELL_H
#define HEXCELL_H

#include "cocos2d.h"
#include "Chess.h"
USING_NS_CC;
class HexCell : public cocos2d::Node {
public:
    Sprite* hexSprite;
    Chess* chess;//表示这个棋格上的棋子
public:
    static HexCell* create();

    //单个棋格的初始化
    virtual bool init() override;

    //改变该cell的透明度
    void changeOpacity(int Opacity);

    //设置棋格上的棋子
    void setChess(Chess* Inchess);
};

#endif // HEXCELL_H
