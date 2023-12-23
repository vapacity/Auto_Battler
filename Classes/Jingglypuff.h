
#pragma once
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Jingglypuff :public Chess
{
public:
	static Jingglypuff* create(const std::string& filename);

	bool init(const std::string& filename);

	virtual void useSkill();
};