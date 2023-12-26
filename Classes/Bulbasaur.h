#pragma once
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Bulbasaur :public Chess
{
public:
	//create一个妙蛙种子
	static Bulbasaur* create(const std::string& filename);

	//重写init方法
	bool init(const std::string& filename);

	virtual void useSkill() override;
};