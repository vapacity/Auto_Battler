#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"

class HexCell;
class Seat;
class ChessFactory;
USING_NS_CC;

#define SET_SCALE 0.2//对棋子模型大小的缩放设置
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

	int id;

	int ATK;//攻击力

	int attackSpeed;//攻击速度

	int moveSpeed;//移动速度

	int health;//生命值

	int blueBar;//蓝条

	int attackRange;//攻击范围

	int price;//价格


public:
	//初始化棋子
	static Chess* create();

	//初始化棋子,用文件名初始化
	static Chess* create(const std::string& filename);
	
	//删除棋子
	void deleteChess();

	//获得棋子id
	int getId();

	//判断棋子是否在棋格
	bool isInGrid();

	//判断棋子是否在备战席上
	bool isAtSeat();

	// 根据输入的id值创建一个
	static Chess* createById(int id);
	
	//单个棋子的初始化
	virtual bool init() override;

	//进化函数，三合一后新建的棋子继承前者属性并生成新的实例
	Chess* upgrade();

	//攻击函数
	virtual void attack();

	//移动函数
	void moveTo();

	//掉血函数
	virtual void getHurt();

	//使用技能
	virtual void useSkill();

	//出售函数
	virtual void getSold();


};


#endif // Chess.h
