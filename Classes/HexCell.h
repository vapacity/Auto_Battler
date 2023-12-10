#ifndef HEXCELL_H
#define HEXCELL_H

#include "cocos2d.h"
USING_NS_CC;
class HexCell : public cocos2d::Node {
public:
    Sprite* hexSprite;
public:
    static HexCell* create();
    //单个棋格的初始化
    virtual bool init() override;

    //改变该cell的透明度
    void changeOpacity(int Opacity);
};

#endif // HEXCELL_H
