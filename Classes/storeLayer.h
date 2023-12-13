#pragma once
#include"cocos2d.h"
#include"store.h"
using namespace cocos2d;


class storeLayer :public store,public cocos2d::Sprite{
public:
	int money = 0;
	int level = 1;
	int exp = 0;
	Label* moneyLabel;
	Label* levelAndExpLabel;
	Label* label1;
	Label* label2;
	std::vector<Sprite*> spriteArray;
	EventListenerMouse* storeLayerMouseListener;//��������
	// ���ú��������������ķ���
	void disableMouseListener();
	void enableMouseListener();

	static storeLayer* create();

	void refresh();//ˢ��

	void updateMoneyLabel();

	void updateLevelLabel();

	virtual bool init();//��ʼ��

	void showStore();

	void buyCard(int choice);//������

	int layerId[5];//���濨��id

	void selectStore(Event* event);

	void upgrade();
};