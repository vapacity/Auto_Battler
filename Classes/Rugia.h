#pragma once
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Rugia :public Chess
{
public:

	static Rugia* create(const std::string& filename);

	bool init(const std::string& filename);

	void breateFire();
};