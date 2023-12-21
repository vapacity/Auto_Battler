#ifndef HEXCELL_H
#define HEXCELL_H

#include "cocos2d.h"
USING_NS_CC;
class HexCell : public cocos2d::Node {
public:
    Sprite* hexSprite;
public:
    static HexCell* create();
    //�������ĳ�ʼ��
    virtual bool init() override;

    //�ı��cell��͸����
    void changeOpacity(int Opacity);
};

#endif // HEXCELL_H
