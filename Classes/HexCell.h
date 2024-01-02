#ifndef HEXCELL_H
#define HEXCELL_H

#include "cocos2d.h"
#include "Chess.h"
USING_NS_CC;

class HexCell : public cocos2d::Node {
public:
    Sprite* hexSprite;

    bool isSelected;//��ѡ��

    //���߳�
    float length;
    //�����
    float width;
    //���߶�
    float height;

    Vec2 coordinateInBoard;//���������������

    //�����ϵ�����
    Chess* chessInGrid;

    HexCell* RightNode;//�����
    HexCell* RightUpNode;//�������
    HexCell* RightDownNode;//�������
    HexCell* LeftDownNode;//�������
    HexCell* LeftNode;//�����
    HexCell* LeftUpNode;//�������

    //������е����ӡ�
    //���������滻
    Vector<Chess*> chessedInThisNode;

    //Ѱ·�ã��ڵ�������ǰ���ڵ����
    HexCell* preNode;

    //������Ƿ����ҷ����
    bool isMine=false;

    //������Ƿ�Ԥ��Ϊ�ƶ�Ŀ����
    bool isBooked = false;
private:

public:


    static HexCell* create();
    //�������ĳ�ʼ��
    virtual bool init() override;

    void turnToSelected();//ѡ��

    void turnToNormal();//δѡ��

    void turnToSeen();//·��
    Vector<HexCell*> GetNeighbors();//��ȡ���д��ڵ��������

    //�����Ƿ����ͨ�����
    bool CanPass(Chess* InActor) const;



};

#endif // HEXCELL_H
