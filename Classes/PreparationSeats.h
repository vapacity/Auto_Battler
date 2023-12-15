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

#define TEST 0//�ĳ�1����ͨ����������仯��սϯ��״̬

class PreparationSeats : public cocos2d::Node {
public:
	Chess** mySeats;

	int seatsNum=0;//��սϯ�ı��������������

	Vector<Seat*> seatsArray;
	


	Seat* latestSeat;//�����Ŀ�λλ��
public:
	//����������Ϣ������ʾ
	void updateForPlayer();

	static PreparationSeats* create(Chess* playerSeats[SEATS_NUM]);

	//������,���������Ŀ�λλ��
	void addChessToSeat(Chess* chess,Seat* seat);

	//��������,���������Ŀ�λλ��
	void removeChessOfSeat(Seat* seat);


	//���������Ŀ�λ
	void renewLatestSeat();

	//�жϱ�սϯ�Ƿ�����
	bool isFull();

	void selectSeat(Event* event);

	//�����Ϸ������Vec2����Ӧ�ĸ��ӣ�����Ϊ�����������������ĸ������ģ�
	Seat* mouseInWhichSeat(const cocos2d::Vec2& position);

	virtual bool init(Chess* playerSeats[SEATS_NUM]) ;

};


#endif
