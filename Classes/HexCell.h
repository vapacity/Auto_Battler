#ifndef HEXCELL_H
#define HEXCELL_H

#include "cocos2d.h"
#include "Chess.h"
USING_NS_CC;
class HexCell : public cocos2d::Node {
public:
    Sprite* hexSprite;
    Chess* chess;//��ʾ�������ϵ�����
public:
    static HexCell* create();

    //�������ĳ�ʼ��
    virtual bool init() override;

    //�ı��cell��͸����
    void changeOpacity(int Opacity);

    //��������ϵ�����
    void setChess(Chess* Inchess);
};

#endif // HEXCELL_H
