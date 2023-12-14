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

    //���߳�
    float length;
    //�����
    float width;
    //���߶�
    float height;

    Vec2 coordinateInBoard;

    //�����ϵ�����
    Chess* chessInGrid;

    HexCell* RightNode;//�����
    HexCell* RightUpNode;//�������
    HexCell* RightDownNode;//�������
    HexCell* LeftDownNode;//�������
    HexCell* LeftNode;//�����
    HexCell* LeftUpNode;//�������

    //������е����ӡ�
    Vector<Chess*> chessedInThisNode;

    //Ѱ·�ã��ڵ�������ǰ���ڵ����
    HexCell* preNode;
private:

public:


    static HexCell* create();
    //�������ĳ�ʼ��
    virtual bool init() override;

    void turnToSelected();

    void turnToNormal();

    Vector<HexCell*> GetNeighbors();

    //���������滻
    bool CanPass(Chess* InActor) const;

    void EnterNode(Chess* InActor);

    void BookNode(Chess* InActor);

    void CancelBookNode(Chess* InActor);

    void LeaveNode(Chess* InActor);

};

#endif // HEXCELL_H
