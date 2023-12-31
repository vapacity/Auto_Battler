#pragma once
#ifndef SEAT_H
#define SEAT_H
#include "cocos2d.h"
#include"HexCell.h"
#include"Chess.h"
USING_NS_CC;

#define SEATS_NUM 8
#define SEAT_SCALE 0.45
#define STARTX 200
#define STARTY 180


class Seat :public cocos2d::Node {
public:
	Sprite* seatImage;//存放备战席棋格的图片

	Chess* chessInSeat=nullptr;//棋格上的棋子

	float width;

	int number;//第几个棋格


public:
	static Seat* create();

	virtual bool init() override;

	void turnToSelected();//选中

	void turnToNormal();

};

#endif
