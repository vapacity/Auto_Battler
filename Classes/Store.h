#pragma once
#include"cocos2d.h"
#include"StoreLayer.h"

#define MAX_INTEREST 5//�غϽ�����������
#define MONEY_FOR_REFRESH 2//ÿ��ˢ��������
#define EXP_FOR_UPGRADE 4//ÿ�������ľ���
#define INIT_MONEY 100//��ʼǮ
#define INIT_LEVEL 1//��ʼ�ȼ�
#define INIT_EXP 0//��ʼ����
#define INIT_INTEREST 0//��ʼ��Ϣ
#define INIT_ADD_FOR_TURN 4 //ÿ�غ���Ȼ�����Ľ����

//��������ĵȼ������顢��Ǯ���غ������̵�5������id
class StoreAttribute : public cocos2d::Node{
public:
	int money ;
	int level;
	int exp;
	int interest;
	int idInStore[5];//5������
public:
	static StoreAttribute* create();
	virtual bool init();
};

class Store:public cocos2d::Node
{
public:
	int storeAreaHeight = STORE_HEIGHT;


	StoreAttribute* playerStore;//�洢��ǰ��player����


	//����
	Label* moneyLabel;//��ʾ��Ǯ��
	Label* levelAndExpLabel;//��ʾ����͵ȼ�

	Label* labelRefresh;//��ʾˢ�µı�ǩ
	Label* labelUpgrade;//��ʾ���µı�ǩ

	//��ʾ�ı�
	Label* fadingText;
	float elapsedTime;

	StoreLayer* storeLayers[5];//5������

	int chessIdHaveBought;//�򵽵�����id�����º�Ҫ��-1����-1ʱ������

public:
	static Store* create(StoreAttribute* st);

	virtual bool init(StoreAttribute* st);//��ʼ��

	void updateMoneyLabel();//���½�Ǯ��ǩ

	void updateLevelLabel();//���¾����ǩ


	//���������Ϣ�����̵���ʾ
	void updateForPlayer();

	//Ҫ�ģ�һ��������5����ͬ����
	//ˢ���̵꣬����5��playerStore->storeLayers�е�id
	void refreshStore();

	//��������������ݣ������ڵ�ǰ����ȼ��£���Ӧ�����ӳ�ʼ����
	int whichCost(int pointer);


	//�����顣��Ǯ�����顢�ȼ�
    //Ҫ�ģ��ѽ�Ǯ��Ϊstore�ĳ�Ա
	void buyExp();


	//ˢ�£��޸��˽�Ǯ�Ϳ����ڵ�id����û�ж���ʾ
	void refresh();

	//�������޸��˽�Ǯ�����飬�ȼ�����ر�ǩ
	void upgrade();


	//���ݴ����Ǯ��������Ϣ�ȵ�ǰ�غϵĽ�Ǯ��������ֱ�ӸĶ���Ǯ
	//Ҫ�ģ���Ϣ�ļ��㷽����
	void renewInterest();


	//�������ſ��۵����ӣ����¿�����Ϣ�����½�Ǯ��ǩ���޸�chessIdHaveBoughtΪ�򵽵�����id
	void buyCard(int choice);


	//���ݴ��������id���Ǽ������³��ۺ��money��ֵ��ֻ����money
	void sellCard(int sellCardId, int star);


	//�����Ǯ�������ʾ������һ��ʱ����Զ��Ƴ�
	void noMoneyText();


	//noMoneyText�ĵ������ã�ʹ��ʾ�𽥵���
	void updateText(float dt);


	//�жϵ���¼���ִ��
	void selectStore(Event* event,Vec2 mousePosition,bool isFull);


	//�����ı�������ʾ

};