#pragma once
#ifndef PREPARATIONSEATS_H
#define PREPARATIONSEATS_H
#include "cocos2d.h"
#include<Seat.h>
USING_NS_CC;

#define SEATS_NUM 8
#define STARTX 200
#define STARTY 160
const float seatGap = 10.0f;

#define TEST 0//�ĳ�1����ͨ����������仯��սϯ��״̬

class PreparationSeats : public cocos2d::Node {
public:
	int seatsNum;//��սϯ���������

	Vector<Seat*> seatsArray;
	
	Chess* chessWithMouse;//�ѱ����ѡ�У�������ƶ������ӡ�

	Seat* latestSeat;//�����Ŀ�λλ��
public:
	static PreparationSeats* create();

	//������,���������Ŀ�λλ��
	void addChessToSeat(Chess* chess,Seat* seat);

	//��������,���������Ŀ�λλ��
	void removeChessOfSeat(Seat* seat);

	//��װ��ġ����ж��Ǵӱ�սϯ�����ӻ��Ƿ�����
	void addOrRemove(Chess* chess, Seat* seat);

	//���������Ŀ�λ
	void renewLatestSeat();

	//�жϱ�սϯ�Ƿ�����
	bool isFull();

	void selectSeat(Event* event);

	//�����Ϸ������Vec2����Ӧ�ĸ��ӣ�����Ϊ�����������������ĸ������ģ�
	Seat* mouseInWhichSeat(const cocos2d::Vec2& position);

	virtual bool init() override;

	void testClickDown(Event* event);

	void testClickUp(Event* event);
};


#endif