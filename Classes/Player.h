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
	//Ҫ�ܸ���store����ʾ
	StoreAttribute* playerStore;//���ﾭ�顢��Ǯ���ȼ������̵���


	//��û����ʾ��սϯ������
	//�±��ʾ�ڼ�����սϯ��ֵ��ʾ�ø�������
	Chess* mySeats[SEATS_NUM];


	//������������
	std::map<Vec2, Chess*, Vec2Compare>myChessMap;





	LittleHero* myHero;
public:
	static Player* create();

	virtual bool init();
};


#endif
