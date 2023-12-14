#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"
class HexCell;
class Seat;
USING_NS_CC;
class Chess :public cocos2d::Sprite
{

public://此处放属性变量
	Sprite* chessExample;

	HexCell* atCell;//该棋子所处棋格（如果有，否则为nullptr）

	Seat* atSeat;//该棋子所处备战席位（如果有，否则为nullptr）

	EventListenerMouse* chessMouseListener;
	
	bool isDragging = false;//被拖动的判断

	std::string name;//名字

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


	// 根据输入的id值创建一个
	static Chess* createById(int id);
	
	//单个棋子的初始化
	virtual bool init() override;



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
