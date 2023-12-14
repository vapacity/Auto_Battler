#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "PreparationSeats.h"
#include "GridMap.h"
#include"Store.h"
#include "LittleHero.h"

class Player :public cocos2d::Node {
public:
	//要能根据store来显示
	StoreAttribute* playerStore;//人物经验、金钱、等级都在商店里


	//还没有显示备战席上棋子
	//下标表示第几个备战席格，值表示该格上棋子
	Chess* mySeats[SEATS_NUM];


	//包含整个棋盘
	std::map<Vec2, Chess*, Vec2Compare>myChessMap;





	LittleHero* myHero;
public:
	static Player* create();

	virtual bool init();
};


#endif
