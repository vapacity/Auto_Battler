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
#define CHESS_ATK 10
#define CHESS_HEALTH 100
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

	int ATK=CHESS_ATK;//������

	int attackSpeed=9;//�����ٶȣ���ΧΪ0-9

	int moveSpeed=1;//�ƶ��ٶ�

	int health=CHESS_HEALTH;//����ֵ

	int blueBar;//����

	int attackRange=1;//������Χ

	int price;//�۸�

	bool isMelee;//1��ʱ���ʾ��ս��0��ʱ���ʾԶ��

	int playerNumber;//������������ұ��

	bool stopMoveFlag;//����ֹͣ�ƶ���־

	Vector<FiniteTimeAction*> actions;//�����ƶ����ж�����

	int attackTrigTimes=0;
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

	// ���������idֵ����һ������ʵ��
	static Chess* createById(int id);

	// ���������idֵ����һ������ʵ��
	static Chess* createByIdAndStar(int id,int star);
	
	//�������ӵĳ�ʼ��
	virtual bool init() override;

	//���ӵĽ�������
	virtual void upgrade();

	//�����ɵȼ�2��������һʱ����
	virtual void upgradeToSecond(const std::string& filename);

	//�����ɵȼ�3��������һʱ����
	void upgradeToThird(const std::string& filename);

	//��������,������ɵ��˺�
	virtual int attack(Chess* attackedChess);

	//�ƶ�����
	MoveTo* moveTo(Vec2 position);

	//��Ѫ����
	virtual void getHurt(int ATK);

	//ʹ�ü���
	virtual void useSkill();

	//���ۺ���
	virtual void getSold();


};


#endif // Chess.h
