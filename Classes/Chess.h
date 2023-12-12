#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"

USING_NS_CC;
class Chess :public cocos2d::Sprite
{

public://此处放属性变量
	Sprite* chessExample;


	Vec2 initialPosition;//起始位置
	
	bool isDragging = false;//被拖动的判断

	char name[10];//名字

	int ATK;//攻击力

	int attackSpeed;//攻击速度

	int moveSpeed;//移动速度

	int health;//生命值

	int blueBar;//蓝条

	int attackRange;//攻击范围

	int price;//价格

public:
	static Chess* create(const std::string& filename);//初始化棋子,Vec2表示创建所在位置
	
	virtual bool init() override;//单个棋子的初始化

	virtual void attack();//攻击函数

	void grabAndMove();//拖动棋子并放置到对应格子上

	void moveTo();//移动函数

	virtual void getHurt();//掉血函数

	virtual void useSkill();//使用技能

	virtual void getSold();//出售函数


};


#endif // Chess.h
