#pragma once
#ifndef SEAT_H
#define SEAT_H
#include "cocos2d.h"
#include"HexCell.h"
USING_NS_CC;

#define SEATS_NUM 8
#define SEAT_SCALE 0.5
#define STARTX 200
#define STARTY 180


class Seat :public cocos2d::Node {
public:
	Sprite* seatImage;//存放备战席棋格的图片

	Chess* chessInSeat;//棋格上的棋子

	float width;


public:
	static Seat* create();

	virtual bool init() override;

	void turnToSelected();

	void turnToNormal();

};

#endif
