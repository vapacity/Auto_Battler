#pragma once
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Bulbasaur :public Chess
{
public:
	//createһ����������
	static Bulbasaur* create(const std::string& filename);

	//��дinit����
	bool init(const std::string& filename);

	virtual void useSkill() override;
};