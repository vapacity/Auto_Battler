#ifndef HEXGRID_H
#define HEXGRID_H

#include "cocos2d.h"
#include "HexCell.h"

USING_NS_CC;
class HexGrid : public cocos2d::Node {
public:
    std::vector<HexCell*> GridMap;
    float Limitx;//x����Զ���ӵ�x����
    float Limity;//y����Զ���ӵ�y����
public:
    static HexGrid* create(int Inline,int Incol);
    
    //��ʼ�������������
    virtual bool initWithSize(int Inline,int Incol);

    //�����Ϸ������Vec2����Ӧ�ĸ��ӣ�����Ϊ�����������������ĸ������ģ�
    HexCell* getCellAt(const cocos2d::Vec2& position);

    //������������ϵ�����
    static void swapChessOnGrids(HexCell* cella, HexCell* cellb);
};

#endif // HEXGRID_H
