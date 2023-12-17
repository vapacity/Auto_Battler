//小火龙 1阶
#ifndef CHARMANDER_H
#include"cocos2d.h"
#include"Chess.h"

USING_NS_CC;

class Charmander1 :public Chess
{
public:
	//create一个小火龙
	static Charmander1* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateFire();
};

class Charmander2 :public Chess
{
public:
	//create一个小火龙
	static Charmander2* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateFire();
};

class Charmander3 :public Chess
{
public:
	//create一个小火龙
	static Charmander3* create(const std::string& filename);

	//重写init方法
	virtual bool init() override;

	//特有函数。。待更新
	void breateFire();
};
#endif
