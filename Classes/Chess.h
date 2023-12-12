#ifndef CHESS_H
#define CHESS_H

#include "cocos2d.h"

USING_NS_CC;
class Chess :public cocos2d::Sprite
{

public://�˴������Ա���
	Sprite* chessExample;


	Vec2 initialPosition;//��ʼλ��
	
	bool isDragging = false;//���϶����ж�

	char name[10];//����

	int ATK;//������

	int attackSpeed;//�����ٶ�

	int moveSpeed;//�ƶ��ٶ�

	int health;//����ֵ

	int blueBar;//����

	int attackRange;//������Χ

	int price;//�۸�

public:
	static Chess* create(const std::string& filename);//��ʼ������,Vec2��ʾ��������λ��
	
	virtual bool init() override;//�������ӵĳ�ʼ��

	virtual void attack();//��������

	void grabAndMove();//�϶����Ӳ����õ���Ӧ������

	void moveTo();//�ƶ�����

	virtual void getHurt();//��Ѫ����

	virtual void useSkill();//ʹ�ü���

	virtual void getSold();//���ۺ���


};


#endif // Chess.h
