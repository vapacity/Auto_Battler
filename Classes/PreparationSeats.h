#pragma once
#ifndef PREPARATIONSEATS_H
#define PREPARATIONSEATS_H
#include "cocos2d.h"
#include "Chess.h"
#include "Seat.h"
USING_NS_CC;

#define SEATS_NUM 8
#define SEAT_STARTX 200
#define SEAT_STARTY 230
const float seatGap = 13.0f;

#define TEST 0//改成1，可通过左键单击变化备战席格状态

class PreparationSeats : public cocos2d::Node {
public:
	int seatsNum=0;//备战席的被填满的棋格数量

	Vector<Seat*> seatsArray;
	
	//Chess* chessWithMouse;//已被鼠标选中，随鼠标移动的棋子。

	Seat* latestSeat;//最左侧的空位位置
public:
	static PreparationSeats* create();

	//放棋子,更新最左侧的空位位置
	void addChessToSeat(Chess* chess,Seat* seat);

	//拿走棋子,更新最左侧的空位位置
	void removeChessOfSeat(Seat* seat);

	//封装后的。有判断是从备战席拿棋子还是放棋子
	void addOrRemove(Chess* chess, Seat* seat);

	//更新最左侧的空位
	void renewLatestSeat();

	//判断备战席是否已满
	bool isFull();

	void selectSeat(Event* event);

	//获得游戏中坐标Vec2处对应的格子（方法为遍历查找与鼠标最靠近的格子中心）
	Seat* mouseInWhichSeat(const cocos2d::Vec2& position);

	virtual bool init() override;

	void testClickDown(Event* event);

	void testClickUp(Event* event);
};


#endif
