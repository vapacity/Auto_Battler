#pragma once
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Magikarp :public Chess
{
public:

	static Magikarp* create(const std::string& filename);

	bool init(const std::string& filename);

	virtual void useSkill() override;
};