#pragma once


#include"cocos2d.h"

using namespace cocos2d;

class store
{
public:
	int maxInterest = 5;

	int cardId[5];

	int level = 1;

	int exp = 0;

	void init();//��ʼ��

	void refreshStore();//ˢ���̵�

	int whichCost(int pointer);

	void getStoreId(int chessId[]);

	void buyExp(int& money);//������ֵ

	void getInterest(int& money);//�������

	int getLevel();

	int getExp();
};