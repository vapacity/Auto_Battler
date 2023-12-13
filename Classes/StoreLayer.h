#pragma once
#include"cocos2d.h"
#include"Store.h"
using namespace cocos2d;
const int pictureSize = 150;
#define storeHeight 200;

class StoreLayer :public Store,public cocos2d::Sprite{
public:
	int storeAreaHeight = storeHeight;
	int buyCardId = -1;
	int money = 10;
	int level = 1;
	int exp = 0;
	Label* moneyLabel;
	Label* levelAndExpLabel;
	Label* label1;
	Label* label2;
	Label* fadingText;
	std::vector<Sprite*> spriteArray;
	std::vector<Label*>labelArray;
	EventListenerMouse* StoreLayerMouseListener;//��������
	// ���ú��������������ķ���
	void disableMouseListener();
	void enableMouseListener();

	static StoreLayer* create();

	void refresh();//ˢ��

	void updateMoneyLabel();

	void updateLevelLabel();

	virtual bool init();//��ʼ��

	void showStore();

	void buyCard(int choice);//������

	void sellCard(int sellCardId, int star);//��������

	int layerId[5];//���濨��id

	void selectStore(Event* event);

	void upgrade();

	void alterMaxInteresr(int newInterest);//�ı��������

	void alterExpPerUpgrade(int newExpPerUpgrade);//�ı��������

	void alterMoneyPerRefresh(int newMoneyPerRefresh);//�ı�ˢ���̵껨��

	void noMoneyText();

	float elapsedTime;

	void updateText(float dt);
};