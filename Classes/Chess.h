#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"
#include "tool.h"
class HexCell;
class Seat;
class ChessFactory;
USING_NS_CC;

#define SET_SCALE 0.15//������ģ�ʹ�С����������
#define MAX_ID 8//��࿨����
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

	//HexCell* atCell;//�����������������У�����Ϊnullptr��

	//Seat* atSeat;//������������սϯλ������У�����Ϊnullptr��

	EventListenerMouse* chessMouseListener;

	Vec2 atGridPosition = Vec2(-1,-1);//�����������������������,��һ����coordinateChess���Ӧ��λ������,�ǵ���Ϊ-1��
	
	int atSeatPosition=-1;//�����������ı�սϯ������꣬��Seat.number���Ӧ���ǵ���Ϊ-1��
	
	bool isDragging = false;//���϶����ж�

	std::string name;//����

	int id;//����id

	int star;//�����Ǽ�

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

	//��������Ǽ�
	int getStar();

	//�ж������Ƿ������
	bool isInGrid();

	//�ж������Ƿ��ڱ�սϯ��
	bool isAtSeat();

	// ���������idֵ����һ��
	static Chess* createById(int id);
	
	//�������ӵĳ�ʼ��
	virtual bool init() override;

	virtual void upgrade();

	//�����ɵȼ�2��������һʱ����
	virtual void upgradeToSecond(const std::string& filename);

	//�����ɵȼ�3��������һʱ����
	void upgradeToThird(const std::string& filename);


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
