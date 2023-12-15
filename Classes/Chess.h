#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"

class HexCell;
class Seat;
class ChessFactory;
USING_NS_CC;

#define SET_SCALE 0.15//������ģ�ʹ�С����������
#define PRICE_STAR1_GRADE1 1//1��1�׿��ķ���
#define PRICE_STAR1_GRADE2 2//1��2�׿��ķ���
#define PRICE_STAR1_GRADE3 5//1��3�׿��ķ���

#define PRICE_STAR2_GRADE1 2//2��1�׿��ķ���
#define PRICE_STAR2_GRADE2 5//2��2�׿��ķ���
#define PRICE_STAR2_GRADE3 14//2��3�׿��ķ���

#define PRICE_STAR3_GRADE1 3//3��1�׿��ķ���
#define PRICE_STAR3_GRADE2 8//3��2�׿��ķ���
#define PRICE_STAR3_GRADE3 23//3��3�׿��ķ���
class Chess :public cocos2d::Sprite
{

public://�˴������Ա���
	Sprite* chessExample;

	HexCell* atCell;//�����������������У�����Ϊnullptr��

	Seat* atSeat;//������������սϯλ������У�����Ϊnullptr��

	EventListenerMouse* chessMouseListener;

	Vec2 atGridPosition;//�����������������������
	
	bool isDragging = false;//���϶����ж�

	std::string name;//����

	int id;

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

	//��ʼ������,���ļ�����ʼ��
	static Chess* create(const std::string& filename);
	
	//ɾ������
	void deleteChess();

	//�������id
	int getId();

	// ���������idֵ����һ��
	static Chess* createById(int id);
	
	//�������ӵĳ�ʼ��
	virtual bool init() override;

	//��������������һ���½������Ӽ̳�ǰ�����Բ������µ�ʵ��
	void upgrade();

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
