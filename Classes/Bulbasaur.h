//妙蛙种子 1阶
#ifndef BULBASAUR_H

#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Bulbasaur :public Chess
{
public:
	//create一个
	static Bulbasaur* create(const std::string& filename);

	//重写init方法
	bool init(const std::string& filename);

	//特有函数。。待更新
	void breateFire();
};
#endif