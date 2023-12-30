#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"
#include "HealthBar.h"
#include "BlueBar.h"
class GridMap;
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

	Vec2 atGridPosition = Vec2(-1, -1);//�����������������������,��һ����coordinateChess���Ӧ��λ������,�ǵ���Ϊ-1��

	int atSeatPosition = -1;//�����������ı�սϯ������꣬��Seat.number���Ӧ���ǵ���Ϊ-1��

	bool isDragging = false;//���϶����ж�

	std::string name;//����

	int id;//����id

	int star;//�����Ǽ�

	int ATK = CHESS_ATK;//������

	int growATK;//�ɳ���������

	int growHP;//�ɳ���������

	float attackSpeed ;//�����ٶȣ���ΧΪ0-9

	float moveSpeed = 1.0;//�ƶ��ٶ�

	int health = CHESS_HEALTH;//����ֵ

	int maxHP;

	int blueBar;//��д��Bar����������

	int currentBlueBar = 0;//��ǰ����

	bool enable_skill = false;//�ܷ�ż���

	int skillCount = 0;//ʹ�ü��ܴ���

	int attackRange;//������Χ

	int price;//���ۼ۸�

	int originalCost;//����ʱ�ķ���

	bool isMelee;//1��ʱ���ʾ��ս��0��ʱ���ʾԶ��

	int playerNumber;//������������ұ��

	enum State { Idle, Moving, Attacking, Dead };

	State currentState = Idle;//���浱ǰ����״̬

	bool isAnimationPlaying = false;//�Ƿ����ڲ��Ŷ���

	HealthBar* healthBar;
	BlueBar* bluebar;
public:
	//��ʼ������
	static Chess* create();

	//��ʼ������,���ļ�����ʼ��
	static Chess* create(const std::string& filename);

	//ɾ������
	void deleteChess();

	//�������id
	int getId()const;

	//��������Ǽ�
	int getStar()const;

	//�ж������Ƿ������
	bool isInGrid()const;

	//�ж������Ƿ��ڱ�սϯ��
	bool isAtSeat()const;

	// ���������idֵ���Ǽ�����һ������ʵ��
	static Chess* createByIdAndStar(int id, int star);

	//�������ӵĳ�ʼ��
	virtual bool init() override;

	//���ӵĽ�������
	virtual void upgrade();

	//�����ɵȼ�2��������һʱ����
	virtual void upgradeToSecond(const std::string& filename);

	//�����ɵȼ�3��������һʱ����
	virtual void upgradeToThird(const std::string& filename);

	//��������ӷ�ת
	void reverseImg();

	//�ƶ�������������ص�������
	virtual void moveAction(GridMap* gridMap);

	//��������
	virtual void attackAction(GridMap* gridMap);

	//��������
	virtual void deadAction(GridMap* gridMap);

	//��Ѫ����
	virtual void getHurt(int ATK);

	//ʹ�ü���
	virtual void useSkill();

	//ÿ֡�����Ը���״̬
	void updateInBattle(float dt, GridMap* gridMap);

	//�ı�״̬�ĺ���
	void changeState(State newState);
	bool isEnemyInAttackRange(GridMap* gridMap, Vector<HexCell*>& enemyChessAround);

	//��ʼ��Ѫ������
	void initHealthBar();
	void initBlueBar();
};


#endif // Chess.h
