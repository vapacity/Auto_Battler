#pragma once
#ifndef PREPARATIONSEATS_H
#define PREPARATIONSEATS_H
#include "cocos2d.h"
#include "Chess.h"
#include "Seat.h"
USING_NS_CC;

#define SEATS_NUM 8
//首个备战位坐标
#define SEAT_STARTX 210
#define SEAT_STARTY 220
const float seatGap = 13.0f;//备战席间距

#define TEST 0//改成1，可通过左键单击变化备战席格状态

class PreparationSeats : public cocos2d::Node {
public:
	Chess** mySeats;//我方备战席上的棋子

	int seatsNum=0;//备战席的被填满的棋格数量

	Vector<Seat*> seatsArray;//8个备战席位
	
	Seat* latestSeat;//最左侧的空位位置
public:
	//根据棋手信息更新显示
	void updateForPlayer();

	static PreparationSeats* create(Chess* playerSeats[SEATS_NUM]);

	//放棋子,更新最左侧的空位位置
	void addChessToSeat(Chess* chess,Seat* seat);

	//拿走棋子,更新最左侧的空位位置
	void removeChessOfSeat(Seat* seat);

	//更新最左侧的空位
	void renewLatestSeat();

	//判断备战席是否已满
	bool isFull();
	
	//选中
	void selectSeat(Event* event);

	//获得游戏中坐标Vec2处对应的格子（方法为遍历查找与鼠标最靠近的格子中心）
	Seat* mouseInWhichSeat(const cocos2d::Vec2& position);

	virtual bool init(Chess* playerSeats[SEATS_NUM]) ;

	//获得指定位置的Seat*
	Seat* getSeatAtPosition(int position);

};


#endif
