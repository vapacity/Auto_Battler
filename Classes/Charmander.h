#ifndef CHARMANDER_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Charmander :public Chess
{
public:
	//create一个小火龙
	static Charmander* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateFire();
};
#endif
