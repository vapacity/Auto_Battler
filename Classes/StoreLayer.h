#pragma once
#include"cocos2d.h"
#include"Store.h"
using namespace cocos2d;

#define STORE_HEIGHT 200;

//控制卡槽的显示信息
class StoreLayer :public cocos2d::Node{
public:

	int layerId;//当前卡槽的棋子id

	Sprite* layerImage;//卡槽所显示的图像

	Label* costLabel;//显示当前棋子费用的标签


public:
	//根据传入的id更新
	void refreshWithId(int id);

	static StoreLayer* create(int id);

	//获取可点击范围
	Rect getBoundingBox() const override;

	virtual bool init(int id);//初始化

	static int calCostFromId(int id);//从Id计算费用
};