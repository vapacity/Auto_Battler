#pragma once
#include"cocos2d.h"
#include"Store.h"
using namespace cocos2d;

#define STORE_HEIGHT 200;

//���ƿ��۵���ʾ��Ϣ
class StoreLayer :public cocos2d::Node{
public:

	int layerId;//��ǰ���۵�����id

	Sprite* layerImage;//��������ʾ��ͼ��

	Label* costLabel;//��ʾ��ǰ���ӷ��õı�ǩ


public:
	//���ݴ����id����
	void refreshWithId(int id);

	static StoreLayer* create(int id);

	//��ȡ�ɵ����Χ
	Rect getBoundingBox() const override;

	virtual bool init(int id);//��ʼ��

	static int calCostFromId(int id);//��Id�������
};