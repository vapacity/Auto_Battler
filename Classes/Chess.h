#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"
#include "HealthBar.h"
#include "BlueBar.h"
#include"AudioEngine.h"
class GridMap;
class HexCell;
class Seat;
class ChessFactory;
USING_NS_CC;

#define SET_SCALE 0.15//对棋子模型大小的缩放设置
#define MAX_ID 8//最多卡牌数
#define PRICE_STAR1_GRADE1 1//1星1阶卡的费用
#define PRICE_STAR1_GRADE2 2//1星2阶卡的费用
#define PRICE_STAR1_GRADE3 5//1星3阶卡的费用

#define PRICE_STAR2_GRADE1 2//2星1阶卡的费用
#define PRICE_STAR2_GRADE2 5//2星2阶卡的费用
#define PRICE_STAR2_GRADE3 14//2星3阶卡的费用

#define PRICE_STAR3_GRADE1 3//3星1阶卡的费用
#define PRICE_STAR3_GRADE2 8//3星2阶卡的费用
#define PRICE_STAR3_GRADE3 23//3星3阶卡的费用
#define CHESS_ATK 10
#define CHESS_HEALTH 100
class Chess :public cocos2d::Sprite
{

public://此处放属性变量

	Vec2 atGridPosition = Vec2(-1, -1);//该棋子所处的棋盘相对坐标,是一个与coordinateChess相对应的位置坐标,记得置为-1！

	int atSeatPosition = -1;//该棋子所处的备战席相对坐标，与Seat.number相对应，记得置为-1！

	bool isDragging = false;//被拖动的判断

	std::string name;//名字

	int id;//卡牌id

	int star;//卡牌星级

	int ATK = CHESS_ATK;//攻击力

	int growATK;//成长攻击属性

	int growHP;//成长生命属性

	float attackSpeed ;//攻击速度，范围为0-9

	float moveSpeed = 1.0;//移动速度

	int health = CHESS_HEALTH;//生命值，初始化100

	int maxHP;//生命上限

	int blueBar;//大写的Bar是蓝条上限，小写的bar是当前蓝条值

	int currentBlueBar = 0;//当前蓝条

	bool enable_skill = false;//能否放技能

	int skillCount = 0;//使用技能次数

	int attackRange;//攻击范围

	int price;//出售价格

	int originalCost;//购买时的费用

	bool isMelee;//1的时候表示近战，0的时候表示远程

	int playerNumber;//棋子所属的玩家编号

	enum State { Idle, Moving, Attacking, Dead };

	State currentState = Idle;//保存当前棋子状态

	bool isAnimationPlaying = false;//是否正在播放动画

	HealthBar* healthBar;//血条
	BlueBar* bluebar;//蓝条
public:
	//初始化棋子
	static Chess* create();

	//初始化棋子,用文件名初始化
	static Chess* create(const std::string& filename);

	//删除棋子
	void deleteChess();

	//获得棋子id
	int getId()const;

	//获得棋子星级
	int getStar()const;

	//判断棋子是否在棋格
	bool isInGrid()const;

	//判断棋子是否在备战席上
	bool isAtSeat()const;

	// 根据输入的id值和星级创建一个棋子实例
	static Chess* createByIdAndStar(int id, int star);

	//单个棋子的初始化
	virtual bool init() override;

	//棋子的进化函数
	virtual void upgrade();

	//进化成等级2，在三合一时触发
	virtual void upgradeToSecond(const std::string& filename);

	//进化成等级3，在三合一时触发
	virtual void upgradeToThird(const std::string& filename);

	//将这个棋子反转
	void reverseImg();

	//移动函数（包含其回调函数）
	virtual void moveAction(GridMap* gridMap);

	//攻击函数
	virtual void attackAction(GridMap* gridMap);

	//死亡函数
	virtual void deadAction(GridMap* gridMap);

	//掉血函数
	virtual void getHurt(int ATK);

	//使用技能
	virtual void useSkill();

	//每帧调用以更新状态
	void updateInBattle(float dt, GridMap* gridMap);

	//改变状态的函数
	void changeState(State newState);
	bool isEnemyInAttackRange(GridMap* gridMap, Vector<HexCell*>& enemyChessAround);

	//初始化血条蓝条
	void initHealthBar();
	void initBlueBar();
};


#endif // Chess.h
