#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"
#include "tool.h"
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
	Sprite* chessExample;

	//HexCell* atCell;//该棋子所处棋格（如果有，否则为nullptr）

	//Seat* atSeat;//该棋子所处备战席位（如果有，否则为nullptr）

	EventListenerMouse* chessMouseListener;

	Vec2 atGridPosition = Vec2(-1,-1);//该棋子所处的棋盘相对坐标,是一个与coordinateChess相对应的位置坐标,记得置为-1！
	
	int atSeatPosition=-1;//该棋子所处的备战席相对坐标，与Seat.number相对应，记得置为-1！
	
	bool isDragging = false;//被拖动的判断

	std::string name;//名字

	int id;//卡牌id

	int star;//卡牌星级

	int ATK=CHESS_ATK;//攻击力

	int attackSpeed=9;//攻击速度，范围为0-9

	int moveSpeed=1;//移动速度

	int health=CHESS_HEALTH;//生命值

	int blueBar;//蓝条

	int attackRange=1;//攻击范围

	int price;//价格

	bool isMelee;//1的时候表示近战，0的时候表示远程

	int playerNumber;//棋子所属的玩家编号

	bool stopMoveFlag;//棋子停止移动标志

	Vector<FiniteTimeAction*> actions;//棋子移动的行动序列

	int attackTrigTimes=0;
public:
	//初始化棋子
	static Chess* create();

	//初始化棋子,用文件名初始化
	static Chess* create(const std::string& filename);
	
	//删除棋子
	void deleteChess();

	//获得棋子id
	int getId();

	//获得棋子星级
	int getStar();

	//判断棋子是否在棋格
	bool isInGrid();

	//判断棋子是否在备战席上
	bool isAtSeat();

	// 根据输入的id值创建一个棋子实例
	static Chess* createById(int id);

	// 根据输入的id值创建一个棋子实例
	static Chess* createByIdAndStar(int id,int star);
	
	//单个棋子的初始化
	virtual bool init() override;

	//棋子的进化函数
	virtual void upgrade();

	//进化成等级2，在三合一时触发
	virtual void upgradeToSecond(const std::string& filename);

	//进化成等级3，在三合一时触发
	void upgradeToThird(const std::string& filename);

	//攻击函数,返回造成的伤害
	virtual int attack(Chess* attackedChess);

	//移动函数
	MoveTo* moveTo(Vec2 position);

	//掉血函数
	virtual void getHurt(int ATK);

	//使用技能
	virtual void useSkill();

	//出售函数
	virtual void getSold();


};


#endif // Chess.h
