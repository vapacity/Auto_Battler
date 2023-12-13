#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"
class HexCell;
class Seat;
USING_NS_CC;
class Chess :public cocos2d::Sprite
{

public://�˴������Ա���
	Sprite* chessExample;

	HexCell* initialCell;

	Seat* initialSeat;

	EventListenerMouse* chessMouseListener;

	Vec2 initialPosition;//��ʼλ��
	
	bool isDragging = false;//���϶����ж�

	std::string name;//����

	int ATK;//������

	int attackSpeed;//�����ٶ�

	int moveSpeed;//�ƶ��ٶ�

	int health;//����ֵ

	int blueBar;//����

	int attackRange;//������Χ

	int price;//�۸�

public:
	//��ʼ������
	static Chess* create();

	//��ʼ������,Vec2��ʾ��������λ��
	static Chess* create(const std::string& filename);
	
	// ���������idֵ����һ��
	static Chess* createById(int id);
	
	//�������ӵĳ�ʼ��
	virtual bool init() override;



	//��������
	virtual void attack();

	//�ƶ�����
	void moveTo();

	//��Ѫ����
	virtual void getHurt();

	//ʹ�ü���
	virtual void useSkill();

	//���ۺ���
	virtual void getSold();


};


#endif // Chess.h
