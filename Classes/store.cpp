#include"Store.h"
//#include"Card.h"


int cardPercent[7][5] = { {100,0,0,0,0},{75,100,0,0,0},{50,80,100,0,0},{40,80,100,0,0},{30,50,70,100,0},{25,40,70,90,100},{15,30,50,75,100} };//���Ӹ���
int levelExp[6] = { 4,8,14,20,40,80 };//�������辭��
void store::init()//��ʼ��
{
	refreshStore();
	return;
}

void store::refreshStore()//ˢ���̵�
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; i++) {//���ݵȼ���������̵�
		int costPointer = rand() % 100;
		int idPointer = rand() % 3;
		int id = idPointer + 3 * whichCost(costPointer);
		cardId[i] = id;
		//log("%d", id);
	}

	return;
}

int store::whichCost(int pointer) {
	//log("%d\n", cardPercent[level - 1][0]);
	if (pointer <= cardPercent[level - 1][0])
		return 0;
	else if (pointer <= cardPercent[level - 1][1])
		return 1;
	else if (pointer <= cardPercent[level - 1][2])
		return 2;
	else if (pointer <= cardPercent[level - 1][3])
		return 3;
	else if (pointer <= cardPercent[level - 1][4])
		return 4;
}

void store::getStoreId(int chessId[]) {//��ȡˢ���̵������ID
	refreshStore();
	for (int i = 0; i < 5; i++)
		chessId[i] = cardId[i];
}

void store::buyExp(int& money) {//������
	money -= 4;
	exp += 4;
	if (exp >= levelExp[level - 1]) {
		exp -= levelExp[level - 1];
		level++;
		
	}
}

void store::getInterest(int& money) {//�������
	int add = money / 10;
	if (add >= maxInterest)
		add = maxInterest;
	add += 4;//����ÿ�غϽ��
	money += add;
}

int store::getLevel() {
	return level;
}

int store::getExp() {
	return exp;
}